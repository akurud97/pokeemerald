#include "global.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "field_camera.h"
#include "field_effect.h"
#include "field_player_avatar.h"
#include "fieldmap.h"
#include "item.h"
#include "money.h"
#include "random.h"
#include "random_resource.h"
#include "script.h"
#include "sprite.h"
#include "constants/field_effects.h"
#include "constants/items.h"
#include "constants/maps.h"
#include "constants/metatile_labels.h"

#define ROUTE4_SAND_PILE_COUNT 5

extern const u32 gFieldEffectObjectPic_AshPuff[];

static void SpriteCB_Route4SandPuff(struct Sprite *sprite);

struct ForagingPouchSalvageEntry
{
    enum Item itemId;
    u16 price;
};

static const struct ForagingPouchSalvageEntry sForagingPouchSalvageEntries[] =
{
    {ITEM_BEACH_GLASS,    100},
    {ITEM_DRIFTWOOD,      200},
    {ITEM_LOST_EARRING,   300},
    {ITEM_COLDWATER_AGATE, 500},
    {ITEM_ANTIQUE_BOTTLE, 1500},
};

// The Route 113 puff uses only indices 3-5. This palette maps those indices
// onto the light, middle, and dark sand colors used by Slateport palette 5.
static const u16 sRoute4SandPuffPalette[] = INCGFX_U16("graphics/field_effects/palettes/sand_puff.pal", ".gbapal");

static const struct SpritePalette sRoute4SandPuffSpritePalette =
{
    .data = sRoute4SandPuffPalette,
    .tag = FLDEFF_PAL_TAG_SAND_PUFF,
};

static const struct SpriteFrameImage sRoute4SandPuffImages[] =
{
    overworld_frame(gFieldEffectObjectPic_AshPuff, 2, 2, 0),
    overworld_frame(gFieldEffectObjectPic_AshPuff, 2, 2, 1),
    overworld_frame(gFieldEffectObjectPic_AshPuff, 2, 2, 2),
    overworld_frame(gFieldEffectObjectPic_AshPuff, 2, 2, 3),
    overworld_frame(gFieldEffectObjectPic_AshPuff, 2, 2, 4),
};

static const union AnimCmd sRoute4SandPuffAnim[] =
{
    ANIMCMD_FRAME(0, 6),
    ANIMCMD_FRAME(1, 6),
    ANIMCMD_FRAME(2, 6),
    ANIMCMD_FRAME(3, 6),
    ANIMCMD_FRAME(4, 6),
    ANIMCMD_END,
};

static const union AnimCmd *const sRoute4SandPuffAnimTable[] =
{
    sRoute4SandPuffAnim,
};

static const struct OamData sRoute4SandPuffOam =
{
    .shape = SPRITE_SHAPE(16x16),
    .size = SPRITE_SIZE(16x16),
    .priority = 2,
};

static const struct SpriteTemplate sRoute4SandPuffSpriteTemplate =
{
    .tileTag = TAG_NONE,
    .paletteTag = FLDEFF_PAL_TAG_SAND_PUFF,
    .oam = &sRoute4SandPuffOam,
    .anims = sRoute4SandPuffAnimTable,
    .images = sRoute4SandPuffImages,
    .callback = SpriteCB_Route4SandPuff,
};

enum Route4SandPileOutcome
{
    ROUTE4_SAND_PILE_EMPTY,
    ROUTE4_SAND_PILE_ITEM,
    ROUTE4_SAND_PILE_WIGLETT_LEVEL_6,
    ROUTE4_SAND_PILE_WIGLETT_LEVEL_7,
};

struct SandPilePosition
{
    s16 x;
    s16 y;
};

static EWRAM_DATA struct SandPilePosition sInteractedSandPile = {0};

static bool32 IsRoute4(void)
{
    return (gSaveBlock1Ptr->location.mapGroup == MAP_GROUP(MAP_HYADES_ROUTE4)
         && gSaveBlock1Ptr->location.mapNum == MAP_NUM(MAP_HYADES_ROUTE4));
}

static bool32 IsReservedSandPilePosition(s16 x, s16 y)
{
    const struct MapEvents *events = gMapHeader.events;
    u32 i;

    if (x == gSaveBlock1Ptr->pos.x && y == gSaveBlock1Ptr->pos.y)
        return TRUE;

    if (events == NULL)
        return FALSE;

    for (i = 0; i < events->objectEventCount; i++)
    {
        const struct ObjectEventTemplate *object = &events->objectEvents[i];

        // Keep active piles out of each object's authored movement area.
        if (x >= object->x - object->movementRangeX
         && x <= object->x + object->movementRangeX
         && y >= object->y - object->movementRangeY
         && y <= object->y + object->movementRangeY)
            return TRUE;
    }

    for (i = 0; i < events->warpCount; i++)
    {
        if (x == events->warps[i].x && y == events->warps[i].y)
            return TRUE;
    }

    for (i = 0; i < events->coordEventCount; i++)
    {
        if (x == events->coordEvents[i].x && y == events->coordEvents[i].y)
            return TRUE;
    }

    for (i = 0; i < events->bgEventCount; i++)
    {
        if (x == events->bgEvents[i].x && y == events->bgEvents[i].y)
            return TRUE;
    }

    return FALSE;
}

u16 InitRoute4SandPiles(void)
{
    struct SandPilePosition selected[ROUTE4_SAND_PILE_COUNT];
    const struct MapLayout *layout;
    u32 candidateCount = 0;
    s32 x;
    s32 y;

    if (!IsRoute4())
        return FALSE;

    layout = gMapHeader.mapLayout;

    for (y = 0; y < layout->height; y++)
    {
        for (x = 0; x < layout->width; x++)
        {
            u32 mapIndex = x + y * layout->width;
            u32 replacementIndex;

            // Read the immutable map layout so save-view data and previously
            // consumed piles cannot change the set of valid candidates.
            if (UNPACK_METATILE(layout->map[mapIndex]) != METATILE_Slateport_Route4Sand)
                continue;

            // Normalize every authored candidate before choosing the new five.
            MapGridSetMetatileIdAt(x + MAP_OFFSET, y + MAP_OFFSET, METATILE_Slateport_Route4Sand);

            if (IsReservedSandPilePosition(x, y))
                continue;

            candidateCount++;
            if (candidateCount <= ROUTE4_SAND_PILE_COUNT)
            {
                selected[candidateCount - 1].x = x;
                selected[candidateCount - 1].y = y;
                continue;
            }

            // Reservoir sampling chooses five unique positions uniformly
            // without storing all of Route 4's candidate coordinates.
            replacementIndex = RandomUniform(RNG_NONE, 0, candidateCount - 1);
            if (replacementIndex < ROUTE4_SAND_PILE_COUNT)
            {
                selected[replacementIndex].x = x;
                selected[replacementIndex].y = y;
            }
        }
    }

    for (x = 0; x < ROUTE4_SAND_PILE_COUNT && x < candidateCount; x++)
    {
        MapGridSetMetatileIdAt(selected[x].x + MAP_OFFSET,
                              selected[x].y + MAP_OFFSET,
                              METATILE_Slateport_Route4SandPile | MAPGRID_IMPASSABLE);
    }

    return candidateCount >= ROUTE4_SAND_PILE_COUNT;
}

u16 ChooseRoute4SandPileOutcome(void)
{
    u32 roll;

    if (!IsRoute4())
        return ROUTE4_SAND_PILE_EMPTY;

    GetXYCoordsOneStepInFrontOfPlayer(&sInteractedSandPile.x, &sInteractedSandPile.y);
    roll = RandomUniform(RNG_NONE, 0, 99);

    if (roll < 19)
    {
        gSpecialVar_0x8004 = ITEM_BEACH_GLASS;
        return ROUTE4_SAND_PILE_ITEM;
    }
    if (roll < 34)
    {
        gSpecialVar_0x8004 = ITEM_DRIFTWOOD;
        return ROUTE4_SAND_PILE_ITEM;
    }
    if (roll < 44)
    {
        gSpecialVar_0x8004 = ITEM_LOST_EARRING;
        return ROUTE4_SAND_PILE_ITEM;
    }
    if (roll < 49)
    {
        gSpecialVar_0x8004 = ITEM_COLDWATER_AGATE;
        return ROUTE4_SAND_PILE_ITEM;
    }
    if (roll < 50)
    {
        gSpecialVar_0x8004 = ITEM_ANTIQUE_BOTTLE;
        return ROUTE4_SAND_PILE_ITEM;
    }
    if (roll < 85)
    {
        if (RandomUniform(RNG_NONE, 6, 7) == 6)
            return ROUTE4_SAND_PILE_WIGLETT_LEVEL_6;
        else
            return ROUTE4_SAND_PILE_WIGLETT_LEVEL_7;
    }

    return ROUTE4_SAND_PILE_EMPTY;
}

u16 RemoveRoute4SandPile(void)
{
    s16 x;
    s16 y;
    u32 paletteNum;
    u32 spriteId;

    if (IsRoute4()
     && MapGridGetMetatileIdAt(sInteractedSandPile.x, sInteractedSandPile.y) == METATILE_Slateport_Route4SandPile)
    {
        x = sInteractedSandPile.x;
        y = sInteractedSandPile.y;
        SetSpritePosToOffsetMapCoords(&x, &y, 8, 8);

        paletteNum = LoadSpritePalette(&sRoute4SandPuffSpritePalette);
        if (paletteNum == 0xFF)
            return FALSE;

        spriteId = CreateSpriteAtEndUnchecked(&sRoute4SandPuffSpriteTemplate, x, y, 0);
        if (spriteId == MAX_SPRITES)
        {
            FreeSpritePaletteByTag(FLDEFF_PAL_TAG_SAND_PUFF);
            return FALSE;
        }

        MapGridSetMetatileIdAt(sInteractedSandPile.x,
                              sInteractedSandPile.y,
                              METATILE_Slateport_Route4Sand);
        DrawWholeMapView();

        gSprites[spriteId].coordOffsetEnabled = TRUE;
        return TRUE;
    }

    return FALSE;
}

static void SpriteCB_Route4SandPuff(struct Sprite *sprite)
{
    if (sprite->animEnded)
    {
        u8 paletteNum = sprite->oam.paletteNum;

        DestroySprite(sprite);
        FieldEffectFreePaletteIfUnused(paletteNum);
        ScriptContext_Enable();
    }
}

u16 CalculateForagingPouchSalvageValue(void)
{
    u32 total = 0;

    for (u32 i = 0; i < ARRAY_COUNT(sForagingPouchSalvageEntries); i++)
    {
        const struct ForagingPouchSalvageEntry *entry = &sForagingPouchSalvageEntries[i];

        total += GetForagingPouchItemCount(entry->itemId) * entry->price;
    }

    gSpecialVar_0x8004 = min(total, MAX_MONEY);
    return total != 0;
}

u16 SellForagingPouchItems(void)
{
    if (CalculateForagingPouchSalvageValue() == FALSE)
        return FALSE;

    AddMoney(&gSaveBlock1Ptr->money, gSpecialVar_0x8004);
    ClearForagingPouch();
    return TRUE;
}
