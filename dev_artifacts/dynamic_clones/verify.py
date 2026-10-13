"""Audit map capacity and exercise the production connection loader with host GCC."""
import json
from pathlib import Path
import subprocess
import tempfile

ROOT = Path(__file__).resolve().parents[2]
layouts = {v['id']: v for v in json.loads((ROOT / 'data/layouts/layouts.json').read_text())['layouts']}
maps = {}
by_name = {}
for path in (ROOT / 'data/maps').glob('*/map.json'):
    data = json.loads(path.read_text())
    maps[data['id']] = data
    by_name[data['name']] = data

def objects(data):
    if data.get('shared_events_map'):
        return objects(by_name[data['shared_events_map']])
    return data.get('object_events', [])

totals = []
for data in maps.values():
    layout = layouts[data['layout']]
    seen = set()
    for conn in data.get('connections') or []:
        if conn['direction'] not in ('up', 'down', 'left', 'right'):
            continue
        target = maps[conn['map']]
        target_layout = layouts[target['layout']]
        for i, obj in enumerate(objects(target)):
            if obj.get('type', 'object') != 'object':
                continue
            x, y = int(obj['x']), int(obj['y'])
            if conn['direction'] == 'up':
                x += conn['offset']; y -= target_layout['height']
            elif conn['direction'] == 'down':
                x += conn['offset']; y += layout['height']
            elif conn['direction'] == 'left':
                x -= target_layout['width']; y += conn['offset']
            else:
                x += layout['width']; y += conn['offset']
            if -9 <= x <= layout['width'] + 9 and -9 <= y <= layout['height'] + 9:
                seen.add((conn['map'], i))
    totals.append((len(objects(data)) + len(seen), data['name'], len(objects(data)), len(seen)))
print('Map capacity (base + generated clones):')
for total, name, base, clones in sorted(totals, reverse=True)[:12]:
    print(f'  {name}: {base} + {clones} = {total}')
over = [v for v in totals if v[0] > 64]
print(f'{len(maps)} maps audited; {len(over)} exceed 64 templates.')
assert not over, over

def function(text, name):
    start = text.index(name)
    start = text.rfind('\n', 0, start) + 1
    brace = text.index('{', start)
    depth = 1
    end = brace + 1
    while depth:
        depth += (text[end] == '{') - (text[end] == '}')
        end += 1
    return text[start:end]

overworld = (ROOT / 'src/overworld.c').read_text()
movement = (ROOT / 'src/event_object_movement.c').read_text()
fieldmap = (ROOT / 'include/global.fieldmap.h').read_text()
template = fieldmap[fieldmap.index('struct __attribute__((packed, aligned(4))) ObjectEventTemplate'):fieldmap.index('struct WarpEvent')]
shim = r'''
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
typedef uint8_t u8; typedef uint16_t u16; typedef uint32_t u32;
typedef int16_t s16; typedef int32_t s32; typedef int bool32;
#define TRUE 1
#define FALSE 0
#define OBJECT_EVENT_TEMPLATES_COUNT 64
#define MAP_OFFSET 7
#define LOCALID_NONE 0
#define OBJ_EVENT_ID_CAMERA 127
#define OBJ_KIND_NORMAL 0
#define OBJ_KIND_CLONE 255
#define CONNECTION_NORTH 1
#define CONNECTION_SOUTH 2
#define CONNECTION_WEST 3
#define CONNECTION_EAST 4
'''
shim += template
shim += r'''
struct MapLayout { s32 width, height; };
struct MapEvents { u8 objectEventCount; const struct ObjectEventTemplate *objectEvents; };
struct MapConnection { u8 direction; s32 offset; u8 mapNum, mapGroup; };
struct MapConnections { u32 count; const struct MapConnection *connections; };
struct MapHeader { const struct MapLayout *mapLayout; const struct MapEvents *events; const struct MapConnections *connections; };
struct SaveBlock { struct ObjectEventTemplate objectEventTemplates[64]; u32 guard; } save;
struct SaveBlock *gSaveBlock1Ptr = &save;
struct MapHeader gMapHeader, target;
const struct MapHeader *GetMapHeaderFromConnection(const struct MapConnection *c) { return &target; }
const struct MapHeader *Overworld_GetMapHeaderByGroupAndId(u16 group, u16 num) { return &target; }
const struct ObjectEventTemplate *FindObjectEventTemplateByLocalId(u8 id, const struct ObjectEventTemplate *a, u8 count) {
    for (u32 i=0;i<count;i++) if (a[i].localId == id) return &a[i];
    return NULL;
}
'''
shim += function(overworld, 'static void LoadConnectionObjectEventTemplates(')
shim += function(overworld, 'u8 GetLoadedObjectEventTemplateCount(')
shim += function(movement, 'static const struct ObjectEventTemplate *GetCloneSourceTemplate(')
shim += r'''
int main(void) {
    struct MapLayout layout = {20, 20};
    struct ObjectEventTemplate base[64] = {{.localId=2,.x=5,.y=6}};
    struct ObjectEventTemplate neighbor[3] = {
        {.localId=17,.x=0,.y=0,.movementType=9,.flagId=42,.trainerRange_berryTreeId=123},
        {.localId=18,.x=19,.y=19},
        {.localId=19,.x=0,.y=0,.kind=OBJ_KIND_CLONE},
    };
    struct MapEvents baseEvents = {1,base}, targetEvents = {3,neighbor};
    struct MapConnection conns[2] = {{CONNECTION_EAST,3,4,5},{CONNECTION_EAST,3,4,5}};
    struct MapConnections connections = {2,conns};
    gMapHeader = (struct MapHeader){&layout,&baseEvents,&connections};
    target = (struct MapHeader){&layout,&targetEvents,NULL};
    save.objectEventTemplates[0] = base[0]; save.guard = 0x12345678;
    LoadConnectionObjectEventTemplates();
    assert(GetLoadedObjectEventTemplateCount() == 2); // duplicate/clone/far object excluded
    struct ObjectEventTemplate *clone = &save.objectEventTemplates[1];
    assert(clone->x==20 && clone->y==3 && clone->localId!=2);
    assert(clone->flagId==42 && clone->targetLocalId==17);
    const struct ObjectEventTemplate *source = GetCloneSourceTemplate(clone);
    assert(source == &neighbor[0] && source->movementType==9 && source->trainerRange_berryTreeId==123);
    assert(save.objectEventTemplates[0].x == 5); // preserve saved current-map position
    connections.count=1;
    conns[0].direction=CONNECTION_WEST;
    LoadConnectionObjectEventTemplates();
    assert(GetLoadedObjectEventTemplateCount()==2 && clone->x==-1 && clone->y==22);
    conns[0].direction=CONNECTION_NORTH; conns[0].offset=-2;
    LoadConnectionObjectEventTemplates();
    assert(GetLoadedObjectEventTemplateCount()==2 && clone->x==17 && clone->y==-1);
    conns[0].direction=CONNECTION_SOUTH;
    LoadConnectionObjectEventTemplates();
    assert(GetLoadedObjectEventTemplateCount()==2 && clone->x==-2 && clone->y==20);
    conns[0].direction=5; // dive: no visible-map clone
    LoadConnectionObjectEventTemplates(); assert(GetLoadedObjectEventTemplateCount()==1);
    conns[0].direction=CONNECTION_EAST;
    baseEvents.objectEventCount=63;
    LoadConnectionObjectEventTemplates(); assert(GetLoadedObjectEventTemplateCount()==64);
    baseEvents.objectEventCount=64;
    LoadConnectionObjectEventTemplates(); assert(GetLoadedObjectEventTemplateCount()==64);
    assert(save.guard==0x12345678); // capacity guard remains intact
    baseEvents.objectEventCount=1; gMapHeader.connections=NULL;
    LoadConnectionObjectEventTemplates(); assert(GetLoadedObjectEventTemplateCount()==1);
    puts("Production C checks passed: four directions, offsets, sparse IDs, clone source, duplicate exclusion, save preservation, capacity, dive, no connections.");
}
'''
with tempfile.TemporaryDirectory() as temp:
    path = Path(temp) / 'clones.c'
    path.write_text(shim)
    exe = Path(temp) / 'clones'
    subprocess.run(['gcc', '-std=gnu11', '-Wall', '-Werror', '-Wno-unused-parameter', str(path), '-o', str(exe)], check=True)
    subprocess.run([str(exe)], check=True)
