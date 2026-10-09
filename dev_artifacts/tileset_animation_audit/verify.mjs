import assert from 'node:assert/strict';
import fs from 'node:fs';
import path from 'node:path';
import vm from 'node:vm';
import { fileURLToPath } from 'node:url';
import * as settings from '../../porymap_scripts/tileset_animation/settings.js';
import { tilesetsData } from '../../porymap_scripts/tileset_animation/animations_pokeemerald.js';
import { tilesetCopies } from '../../porymap_scripts/tileset_animation/project_tileset_copies.js';

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), '../..');
const plugin = path.join(root, 'porymap_scripts/tileset_animation');
const sourcePlugin = '/Users/andrewbecker/Porymap-Animation';
const original = await import(path.join(sourcePlugin, 'animations_pokeemerald.js'));

// All vanilla definitions/settings remain intact. Only the Emerald registry changes.
for (const [name, definition] of Object.entries(original.tilesetsData))
    assert.deepEqual(tilesetsData[name], definition, name);
for (const name of ['animation.js', 'settings.js', 'animations_pokeruby.js', 'animations_pokefirered.js'])
    assert.deepEqual(fs.readFileSync(path.join(plugin, name)), fs.readFileSync(path.join(sourcePlugin, name)), name);

// Execute the actual plugin's loader/validation, with Porymap's constants mocked.
const errors = [];
const context = vm.createContext({
    ...settings,
    constants: {base_game_version: 'pokeemerald'},
    utility: {log() {}, warn() {}, error(message) {errors.push(message);}},
    projectRoot: root,
});
const code = fs.readFileSync(path.join(plugin, 'animation.js'), 'utf8')
    .replace(/import\s*\{[\s\S]*?\}\s*from\s*"\.\/settings.js"/, '')
    .replace(/export function /g, 'function ');
vm.runInContext(code + '\nroot = projectRoot + "/"; maxPrimaryTile = 512; maxSecondaryTile = 1024; buildTilesetsData(); globalThis.loaded = tilesetsData;', context);
assert.deepEqual(errors, []);
const loaded = JSON.parse(JSON.stringify(context.loaded));
assert(loaded.gTileset_General, 'Primary animations must remain available');

let frameCount = 0;
for (const entry of tilesetCopies) {
    if (!original.tilesetsData[entry.source]) {
        assert.equal(loaded[entry.copy], undefined, `${entry.copy}: no secondary animation callback`);
        continue;
    }
    const expected = structuredClone(original.tilesetsData[entry.source]);
    expected.folder = entry.folder;
    if (entry.animationStarts) {
        for (const start of Object.keys(expected.tileAnimations))
            if (!entry.animationStarts.includes(Number(start))) delete expected.tileAnimations[start];
    }
    assert.deepEqual(tilesetsData[entry.copy], expected, entry.copy);
    assert.notEqual(tilesetsData[entry.copy].tileAnimations, tilesetsData[entry.source].tileAnimations);
    const animation = loaded[entry.copy].tileAnimations;
    const sourceIds = entry.animationStarts
        ? entry.animationStarts.flatMap(start => Array.from({length: expected.tileAnimations[start].numTiles}, (_, i) => String(start + i)))
        : Object.keys(loaded[entry.source].tileAnimations);
    assert.deepEqual(Object.keys(animation), sourceIds, entry.copy + ': animated tile range');
    const paths = new Set();
    for (const [id, tile] of Object.entries(animation)) {
        assert(+id >= 512 && +id < 1024);
        assert(tile.interval > 0 && tile.filepaths.length > 1);
        for (const file of tile.filepaths) {
            paths.add(file);
            if (!tile.externalFolder)
                assert(file.startsWith(path.join(root, 'data/tilesets/secondary', entry.folder) + '/'));
            const png = fs.readFileSync(file);
            assert.equal(png.toString('hex', 0, 8), '89504e470d0a1a0a', file);
            const width = png.readUInt32BE(16), height = png.readUInt32BE(20);
            assert.equal(width, tile.imageWidth, file);
            assert(width % 8 === 0 && height % 8 === 0 && width * height >= tile.numTiles * 64, file);
        }
    }
    frameCount += paths.size;
    console.log(`${entry.copy}: ${sourceIds.length} animated tiles, ${paths.size} frame files OK`);
}

// The two flag metatiles must still reference all six tiles handled by the loader.
const flagMetatiles = fs.readFileSync(path.join(root, 'data/tilesets/secondary/tiaki/metatiles.bin'));
const originalMetatiles = fs.readFileSync(path.join(root, 'data/tilesets/secondary/dewford/metatiles.bin'));
const used = new Set();
for (const id of [0x349, 0x34A]) {
    const offset = (id - 0x200) * 16;
    assert.deepEqual(flagMetatiles.subarray(offset, offset + 16), originalMetatiles.subarray(offset, offset + 16));
    for (let i = 0; i < 8; i++) {
        const tile = flagMetatiles.readUInt16LE(offset + i * 2) & 0x3ff;
        if (tile >= 0x2AA && tile <= 0x2AF) {
            used.add(tile);
            assert(loaded.gTileset_Tiaki.tileAnimations[tile], `Flag tile ${tile} not loaded`);
        }
    }
}
assert.deepEqual([...used].sort(), [0x2AA, 0x2AB, 0x2AC, 0x2AD, 0x2AE, 0x2AF]);
// Never re-enable Rustboro's water range on Castula's imported buildings.
assert.deepEqual(Object.keys(loaded.gTileset_Castula.tileAnimations), ['960', '961', '962', '963']);
for (let tile = 640; tile < 672; tile++) assert.equal(loaded.gTileset_Castula.tileAnimations[tile], undefined);
const castulaMetatiles = fs.readFileSync(path.join(root, 'data/tilesets/secondary/castula/metatiles.bin'));
const fountainTiles = new Set();
for (const mid of [0x339, 0x341]) {
    for (let i = 0; i < 8; i++) {
        const tid = castulaMetatiles.readUInt16LE((mid - 512) * 16 + i * 2) & 0x3ff;
        if (tid >= 960 && tid < 964) fountainTiles.add(tid);
    }
}
assert.deepEqual([...fountainTiles].sort(), [960, 961, 962, 963]);
assert(fs.readFileSync(path.join(root, 'porymap.user.cfg'), 'utf8').includes(`custom_scripts=${plugin}/animation.js:1`));
console.log(`PASS: actual editor loader, flag metatiles, all prior registrations and ${frameCount} frame paths`);
