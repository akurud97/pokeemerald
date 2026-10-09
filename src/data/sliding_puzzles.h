static const u32 sKabutoPuzzle_Gfx[]     = INCBIN_U32("graphics/sliding_puzzle/puzzles/kabuto/tiles.4bpp.lz");
static const u32 sOmanytePuzzle_Gfx[]    = INCBIN_U32("graphics/sliding_puzzle/puzzles/omanyte/tiles.4bpp.lz");
static const u32 sAerodactylPuzzle_Gfx[] = INCBIN_U32("graphics/sliding_puzzle/puzzles/aerodactyl/tiles.4bpp.lz");
static const u32 sHoOhPuzzle_Gfx[]       = INCBIN_U32("graphics/sliding_puzzle/puzzles/ho_oh/tiles.4bpp.lz");
static const u32 sFlyingBirdPuzzle_Gfx[] = INCBIN_U32("graphics/sliding_puzzle/puzzles/flying_bird/tiles.4bpp.lz");
static const u32 sForestBirdPuzzle_Gfx[] = INCBIN_U32("graphics/sliding_puzzle/puzzles/forest_bird/tiles.4bpp.lz");
static const u32 sDuckBoatPuzzle_Gfx[]   = INCBIN_U32("graphics/sliding_puzzle/puzzles/duck_boat/tiles.4bpp.lz");

static const u16 sKabutoPuzzle_Pal[]     = INCBIN_U16("graphics/sliding_puzzle/puzzles/kabuto/tiles.gbapal");
static const u16 sOmanytePuzzle_Pal[]    = INCBIN_U16("graphics/sliding_puzzle/puzzles/omanyte/tiles.gbapal");
static const u16 sAerodactylPuzzle_Pal[] = INCBIN_U16("graphics/sliding_puzzle/puzzles/aerodactyl/tiles.gbapal");
static const u16 sHoOhPuzzle_Pal[]       = INCBIN_U16("graphics/sliding_puzzle/puzzles/ho_oh/tiles.gbapal");
static const u16 sFlyingBirdPuzzle_Pal[] = INCBIN_U16("graphics/sliding_puzzle/puzzles/flying_bird/tiles.gbapal");
static const u16 sForestBirdPuzzle_Pal[] = INCBIN_U16("graphics/sliding_puzzle/puzzles/forest_bird/tiles.gbapal");
static const u16 sDuckBoatPuzzle_Pal[]   = INCBIN_U16("graphics/sliding_puzzle/puzzles/duck_boat/tiles.gbapal");

static const struct CompressedSpriteSheet sSpriteSheet_Tiles[SLIDING_PUZZLE_COUNT] =
{
    [SLIDING_PUZZLE_KABUTO]     = {sKabutoPuzzle_Gfx,     0x400 * 16, GFXTAG_TILES},
    [SLIDING_PUZZLE_OMANYTE]    = {sOmanytePuzzle_Gfx,    0x400 * 16, GFXTAG_TILES},
    [SLIDING_PUZZLE_AERODACTYL] = {sAerodactylPuzzle_Gfx, 0x400 * 16, GFXTAG_TILES},
    [SLIDING_PUZZLE_HO_OH]      = {sHoOhPuzzle_Gfx,       0x400 * 16, GFXTAG_TILES},
    [SLIDING_PUZZLE_FLYING_BIRD] = {sFlyingBirdPuzzle_Gfx, 0x400 * 16, GFXTAG_TILES},
    [SLIDING_PUZZLE_FOREST_BIRD] = {sForestBirdPuzzle_Gfx, 0x400 * 16, GFXTAG_TILES},
    [SLIDING_PUZZLE_DUCK_BOAT]   = {sDuckBoatPuzzle_Gfx,   0x400 * 16, GFXTAG_TILES},
    [SLIDING_PUZZLE_SOLVED]     = {},
};

static const struct SpritePalette sSpritePalette_Tiles[SLIDING_PUZZLE_COUNT] =
{
    [SLIDING_PUZZLE_KABUTO]      = {sKabutoPuzzle_Pal,     GFXTAG_TILES},
    [SLIDING_PUZZLE_OMANYTE]     = {sOmanytePuzzle_Pal,    GFXTAG_TILES},
    [SLIDING_PUZZLE_AERODACTYL]  = {sAerodactylPuzzle_Pal, GFXTAG_TILES},
    [SLIDING_PUZZLE_HO_OH]       = {sHoOhPuzzle_Pal,       GFXTAG_TILES},
    [SLIDING_PUZZLE_FLYING_BIRD] = {sFlyingBirdPuzzle_Pal, GFXTAG_TILES},
    [SLIDING_PUZZLE_FOREST_BIRD] = {sForestBirdPuzzle_Pal, GFXTAG_TILES},
    [SLIDING_PUZZLE_DUCK_BOAT]   = {sDuckBoatPuzzle_Pal,   GFXTAG_TILES},
    [SLIDING_PUZZLE_SOLVED]      = {},
};

static const u8 sPuzzleLayouts[SLIDING_PUZZLE_COUNT][NUM_SLIDING_PUZZLE_ROWS][NUM_SLIDING_PUZZLE_COLS] =
{
    [SLIDING_PUZZLE_KABUTO] =
    {
        { 6, 1,__, 3, 4,__},
        {__, 5,__, 7, 8,11},
        {__,__,10,__,12,__},
        { 2,13,14,15,16, 9},
    },
    [SLIDING_PUZZLE_OMANYTE] =
    {
        { 9,__, 2, 3, 4,11},
        {__, 5, 6,12,__,14},
        { 8,__,__,__,__,13},
        { 1, 7,__,15,16,10},
    },
    [SLIDING_PUZZLE_AERODACTYL] =
    {
        {14,__,__, 3, 4,__},
        {__,__,10, 7, 8,16},
        { 2, 9,__,11,12, 5},
        { 1,13,__,15,__, 6},
    },
    [SLIDING_PUZZLE_HO_OH] =
    {
        {15,__,14, 3, 4, 1},
        {13,__, 6, 7,__,10},
        { 2,__,__,__,12, 9},
        { 8,__, 5,__,16,11},
    },
    [SLIDING_PUZZLE_FLYING_BIRD] =
    {
        {16,__,__, 3,__, 2},
        {__, 5, 6, 7, 8,13},
        { 4, 9,10,11,12,__},
        {__,__,14,15,__, 1},
    },
    [SLIDING_PUZZLE_FOREST_BIRD] =
    {
        {15, 1, 2, 3, 4,__},
        {11, 5,__,__, 8,10},
        { 7, 9,__,__,12, 6},
        {__,13,14,__,16,__},
    },
    [SLIDING_PUZZLE_DUCK_BOAT] =
    {
        {12, 1,__, 3, 4,__},
        { 9,__, 6, 7, 8, 2},
        {15,__,10,11,__,__},
        {__,13,14,__,16, 5},
    },
    [SLIDING_PUZZLE_SOLVED] =
    {
        {__, 1, 2, 3, 4,__},
        {__, 5, 6, 7, 8,__},
        {__, 9,10,11,12,__},
        {__,13,14,15,16,__},
    },
};

static const u8 sTileOrientations[SLIDING_PUZZLE_COUNT][NUM_SLIDING_PUZZLE_ROWS][NUM_SLIDING_PUZZLE_COLS] =
{
    [SLIDING_PUZZLE_KABUTO] =
    {
        {ORIENTATION_90,  IMMOVABLE_TILE,  ORIENTATION_0,   IMMOVABLE_TILE, IMMOVABLE_TILE, ORIENTATION_0},
        {ORIENTATION_0,   IMMOVABLE_TILE,  ORIENTATION_0,   IMMOVABLE_TILE, IMMOVABLE_TILE, ORIENTATION_180},
        {ORIENTATION_0,   ORIENTATION_0,   IMMOVABLE_TILE,  ORIENTATION_0,  IMMOVABLE_TILE, ORIENTATION_0},
        {ORIENTATION_270, IMMOVABLE_TILE,  IMMOVABLE_TILE,  IMMOVABLE_TILE, IMMOVABLE_TILE, ORIENTATION_90},
    },
    [SLIDING_PUZZLE_OMANYTE] =
    {
        {ORIENTATION_0,   ORIENTATION_0,   IMMOVABLE_TILE,  IMMOVABLE_TILE, IMMOVABLE_TILE, ORIENTATION_90},
        {ORIENTATION_0,   IMMOVABLE_TILE,  IMMOVABLE_TILE,  ORIENTATION_90, ORIENTATION_0,  ORIENTATION_180},
        {ORIENTATION_0,   ORIENTATION_0,   ORIENTATION_0,   ORIENTATION_0,  ORIENTATION_0,  ORIENTATION_270},
        {ORIENTATION_270, ORIENTATION_180, ORIENTATION_0,   IMMOVABLE_TILE, IMMOVABLE_TILE, ORIENTATION_0},
    },
    [SLIDING_PUZZLE_AERODACTYL] =
    {
        {ORIENTATION_180, ORIENTATION_0,   ORIENTATION_0,   IMMOVABLE_TILE, IMMOVABLE_TILE, ORIENTATION_0},
        {ORIENTATION_0,   ORIENTATION_0,   ORIENTATION_270, IMMOVABLE_TILE, IMMOVABLE_TILE, ORIENTATION_270},
        {ORIENTATION_270, IMMOVABLE_TILE,  ORIENTATION_0,   IMMOVABLE_TILE, IMMOVABLE_TILE, ORIENTATION_90},
        {ORIENTATION_180, IMMOVABLE_TILE,  ORIENTATION_0,   IMMOVABLE_TILE, ORIENTATION_0,  ORIENTATION_180},
    },
    [SLIDING_PUZZLE_HO_OH] =
    {
        {ORIENTATION_180, ORIENTATION_180, ORIENTATION_90,  IMMOVABLE_TILE, IMMOVABLE_TILE, ORIENTATION_270},
        {ORIENTATION_180, ORIENTATION_0,   IMMOVABLE_TILE,  IMMOVABLE_TILE, ORIENTATION_0,  ORIENTATION_270},
        {ORIENTATION_270, ORIENTATION_0,   ORIENTATION_0,   ORIENTATION_0,  IMMOVABLE_TILE, ORIENTATION_0},
        {ORIENTATION_90,  ORIENTATION_0,   ORIENTATION_180, ORIENTATION_0,  IMMOVABLE_TILE, ORIENTATION_270},
    },
    [SLIDING_PUZZLE_FLYING_BIRD] =
    {
        {ORIENTATION_180, ORIENTATION_0,   ORIENTATION_0,  IMMOVABLE_TILE, ORIENTATION_0,   ORIENTATION_180},
        {ORIENTATION_0,   IMMOVABLE_TILE,  IMMOVABLE_TILE, IMMOVABLE_TILE, IMMOVABLE_TILE,  ORIENTATION_270},
        {ORIENTATION_90,  IMMOVABLE_TILE,  IMMOVABLE_TILE, IMMOVABLE_TILE, IMMOVABLE_TILE,  ORIENTATION_0},
        {ORIENTATION_0,   ORIENTATION_0,   IMMOVABLE_TILE, IMMOVABLE_TILE, ORIENTATION_0,   ORIENTATION_0},
    },
    [SLIDING_PUZZLE_FOREST_BIRD] =
    {
        {ORIENTATION_180, IMMOVABLE_TILE,  IMMOVABLE_TILE, IMMOVABLE_TILE, IMMOVABLE_TILE, ORIENTATION_0},
        {ORIENTATION_90,  IMMOVABLE_TILE,  ORIENTATION_0,  ORIENTATION_0,  IMMOVABLE_TILE, ORIENTATION_180},
        {ORIENTATION_270, IMMOVABLE_TILE,  ORIENTATION_0,  ORIENTATION_0,  IMMOVABLE_TILE, ORIENTATION_0},
        {ORIENTATION_0,   IMMOVABLE_TILE,  IMMOVABLE_TILE, ORIENTATION_0,  IMMOVABLE_TILE, ORIENTATION_0},
    },
    [SLIDING_PUZZLE_DUCK_BOAT] =
    {
        {ORIENTATION_270, IMMOVABLE_TILE, ORIENTATION_0,  IMMOVABLE_TILE, IMMOVABLE_TILE, ORIENTATION_0},
        {ORIENTATION_180, ORIENTATION_0,  IMMOVABLE_TILE, IMMOVABLE_TILE, IMMOVABLE_TILE, ORIENTATION_180},
        {ORIENTATION_90,  ORIENTATION_0,  IMMOVABLE_TILE, IMMOVABLE_TILE, ORIENTATION_0,  ORIENTATION_0},
        {ORIENTATION_0,   IMMOVABLE_TILE, IMMOVABLE_TILE, ORIENTATION_0,  IMMOVABLE_TILE, ORIENTATION_0},
    },
    [SLIDING_PUZZLE_SOLVED] =
    {
        {ORIENTATION_0,   ORIENTATION_0,   ORIENTATION_0,   ORIENTATION_0,  ORIENTATION_0,  ORIENTATION_0},
        {ORIENTATION_0,   ORIENTATION_0,   ORIENTATION_0,   ORIENTATION_0,  ORIENTATION_0,  ORIENTATION_0},
        {ORIENTATION_0,   ORIENTATION_0,   ORIENTATION_0,   ORIENTATION_0,  ORIENTATION_0,  ORIENTATION_0},
        {ORIENTATION_0,   ORIENTATION_0,   ORIENTATION_0,   ORIENTATION_0,  ORIENTATION_0,  ORIENTATION_0},
    },
};
