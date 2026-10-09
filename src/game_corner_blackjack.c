#include "game_corner_blackjack.h"
#include "global.h"
#include "malloc.h"
#include "bg.h"
#include "decompress.h"
#include "event_data.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "field_message_box.h"
#include "international_string_util.h"
#include "m4a.h"
#include "main.h"
#include "menu.h"
#include "menu_helpers.h"
#include "overworld.h"
#include "palette.h"
#include "palette_util.h"
#include "random.h"
#include "script.h"
#include "sound.h"
#include "sprite.h"
#include "strings.h"
#include "task.h"
#include "text.h"
#include "text_window.h"
#include "tv.h"
#include "window.h"
#include "constants/flags.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/vars.h"
#include "scanline_effect.h"
#include "pokemon_storage_system.h"
#include "string_util.h"
#include "field_specials.h"

enum
{
    BJ_STATE_INIT,
    BJ_STATE_PLAYER_TURN,
    BJ_STATE_DEALER_REVEAL,
    BJ_STATE_DEALER_DRAW,
    BJ_STATE_SHOW_RESULT,
    BJ_STATE_WAIT_FOR_RESULT_INPUT,
    BJ_STATE_START_EXIT,
    BJ_STATE_EXIT,
};

enum {
    SPR_PLAYER_DIG_1,
    SPR_PLAYER_DIG_10,
};

enum {
    SPR_DEALER_DIG_1,
    SPR_DEALER_DIG_10,
};
enum
{
    OPTION_HIT_STAND,
    OPTION_NONE,
};

enum {
    CARD_HEARTS_2,
    CARD_HEARTS_3,
    CARD_HEARTS_4,
    CARD_HEARTS_5,
    CARD_HEARTS_6,
    CARD_HEARTS_7,
    CARD_HEARTS_8,
    CARD_HEARTS_9,
    CARD_HEARTS_10,
    CARD_HEARTS_JACK,
    CARD_HEARTS_QUEEN,
    CARD_HEARTS_KING,
    CARD_HEARTS_ACE,
    CARD_CLUBS_2,
    CARD_CLUBS_3,
    CARD_CLUBS_4,
    CARD_CLUBS_5,
    CARD_CLUBS_6,
    CARD_CLUBS_7,
    CARD_CLUBS_8,
    CARD_CLUBS_9,
    CARD_CLUBS_10,
    CARD_CLUBS_JACK,
    CARD_CLUBS_QUEEN,
    CARD_CLUBS_KING,
    CARD_CLUBS_ACE,
    CARD_DIAMONDS_2,
    CARD_DIAMONDS_3,
    CARD_DIAMONDS_4,
    CARD_DIAMONDS_5,
    CARD_DIAMONDS_6,
    CARD_DIAMONDS_7,
    CARD_DIAMONDS_8,
    CARD_DIAMONDS_9,
    CARD_DIAMONDS_10,
    CARD_DIAMONDS_JACK,
    CARD_DIAMONDS_QUEEN,
    CARD_DIAMONDS_KING,
    CARD_DIAMONDS_ACE,
    CARD_SPADES_2,
    CARD_SPADES_3,
    CARD_SPADES_4,
    CARD_SPADES_5,
    CARD_SPADES_6,
    CARD_SPADES_7,
    CARD_SPADES_8,
    CARD_SPADES_9,
    CARD_SPADES_10,
    CARD_SPADES_JACK,
    CARD_SPADES_QUEEN,
    CARD_SPADES_KING,
    CARD_SPADES_ACE,
    CARD_COUNT,
};

#define SPR_PLAYER_DIGITS SPR_PLAYER_DIG_1
#define SPR_DEALER_DIGITS SPR_DEALER_DIG_1

#define MAX_SPRITES_PLAYER 2
#define MAX_SPRITES_DEALER 2

#define ACTION_DELAY_FRAMES 30

#define MAX_PLAYER_CARDS 9
#define MAX_DEALER_CARDS 9

#define CARD_SCORE_2     2
#define CARD_SCORE_3     3
#define CARD_SCORE_4     4
#define CARD_SCORE_5     5
#define CARD_SCORE_6     6
#define CARD_SCORE_7     7
#define CARD_SCORE_8     8
#define CARD_SCORE_9     9
#define CARD_SCORE_10    10
#define CARD_SCORE_FACE  10
#define CARD_SCORE_ACE   0

#define CARD_SCORE_ACE_EXPANDED  11
#define CARD_SCORE_ACE_SHRUNK    1
#define CARD_SCORE_BLACK_JACK    21

struct BlackJack {
    u8 state;
    u8 numPlayerCards;
    u8 numDealerCards;
    u8 cursorSpriteId;
    u8 PlayerSpriteIds[MAX_SPRITES_PLAYER];
    u8 DealerSpriteIds[MAX_SPRITES_DEALER];
    u8 option1SpriteId;
    u8 option2SpriteId;
    // Player card IDs and numbers (to store their sprites and values)
    u8 playerCardIds[MAX_PLAYER_CARDS];
    u8 playerCardNumbers[MAX_PLAYER_CARDS];

    // Dealer card IDs and numbers
    u8 dealerCardIds[MAX_DEALER_CARDS];
    u8 dealerCardNumbers[MAX_DEALER_CARDS];
    //                        Facedown Sprite ID
    u8 DealerFaceDownId;
    u8 LogoId;
    u8 result;
    u8 optionMode;
    u8 delayTimer;
    bool8 playerHasNatural;
    u8 dealerScore;
    u8 playerScore;
    void *bgTilemapBuffer;
};

static EWRAM_DATA struct BlackJack *sBlackJack = NULL;
static EWRAM_INIT u8 sTextWindowId = 1;

static void FadeToBJScreen(u8 taskId);
static void Task_ResumeAfterBlackjackAllocFailure(u8 taskId);
static void InitBJScreen(void);
static void BJVBlankCallback(void);
static void CreateCursorSprite(void);
static void CreateOptions(void);
static void AdjustCards(void);
static void CreateFacedown(void);
static void ShuffleCards(void);
static void UpdateCards(void);
static void UpdateCardVisibility(void);
static void SetCardSprite(u8 cardNum, u8 cardIndex, bool8 isPlayerCard);
static void MoveCursor(s8 direction);
static void StartExitBJ(void);
static void ExitBJ(void);
static void BJMain(u8 taskId);
static void BeginDealerTurn(void);
static void SetResult(u8 result);
static u8 CalculateHandScore(const u8 *cards, u8 count);

static const u8 sText_YouLose[] = _("You lose!");
static const u8 sText_YouWin[] = _("You win!");
static const u8 sText_Draw[] = _("It's a draw!");
static const u8 sText_BlackJack[] = _("BLACKJACK!\nYou win!");
static const u8 sText_ChooseAction[] = _("Choose HIT or STAND.");
static const u8 sHelpBarHitStandText[] = _("{DPAD_UPDOWN}PICK  {A_BUTTON}SELECT  {B_BUTTON}QUIT");
static const u8 sHelpBarContinueText[] = _("{A_BUTTON}CONTINUE");

static const u32 sBJBackgroundGfx[] = INCGFX_U32("graphics/blackjack/background_tiles.png", ".4bpp.smol");
static const u8 sBJBackgroundTilemap[] = INCBIN_U8("graphics/blackjack/background_tiles.bin.smolTM");
static const u16 sBJBackgroundPalette[] = INCGFX_U16("graphics/blackjack/background.pal", ".gbapal");

static const u32 gPlayer_Gfx[] = INCGFX_U32("graphics/blackjack/digits_player.png", ".4bpp.smol");
static const u32 gDealer_Gfx[] = INCGFX_U32("graphics/blackjack/digits_dealer.png", ".4bpp.smol");
static const u16 sPlayer_Pal[] = INCGFX_U16("graphics/blackjack/digits_player.pal", ".gbapal");
static const u16 sDealer_Pal[] = INCGFX_U16("graphics/blackjack/digits_dealer.pal", ".gbapal");

static const u32 gOption_1_Gfx[] = INCGFX_U32("graphics/blackjack/option_1.png", ".4bpp.smol");
static const u32 gOption_2_Gfx[] = INCGFX_U32("graphics/blackjack/option_2.png", ".4bpp.smol");

static const u32 gCards_2_Hearts_Gfx[] = INCGFX_U32("graphics/blackjack/cards/hearts/cards_hearts_2.png", ".4bpp.smol");
static const u32 gCards_3_Hearts_Gfx[] = INCGFX_U32("graphics/blackjack/cards/hearts/cards_hearts_3.png", ".4bpp.smol");
static const u32 gCards_4_Hearts_Gfx[] = INCGFX_U32("graphics/blackjack/cards/hearts/cards_hearts_4.png", ".4bpp.smol");
static const u32 gCards_5_Hearts_Gfx[] = INCGFX_U32("graphics/blackjack/cards/hearts/cards_hearts_5.png", ".4bpp.smol");
static const u32 gCards_6_Hearts_Gfx[] = INCGFX_U32("graphics/blackjack/cards/hearts/cards_hearts_6.png", ".4bpp.smol");
static const u32 gCards_7_Hearts_Gfx[] = INCGFX_U32("graphics/blackjack/cards/hearts/cards_hearts_7.png", ".4bpp.smol");
static const u32 gCards_8_Hearts_Gfx[] = INCGFX_U32("graphics/blackjack/cards/hearts/cards_hearts_8.png", ".4bpp.smol");
static const u32 gCards_9_Hearts_Gfx[] = INCGFX_U32("graphics/blackjack/cards/hearts/cards_hearts_9.png", ".4bpp.smol");
static const u32 gCards_10_Hearts_Gfx[] = INCGFX_U32("graphics/blackjack/cards/hearts/cards_hearts_10.png", ".4bpp.smol");
static const u32 gCards_J_Hearts_Gfx[] = INCGFX_U32("graphics/blackjack/cards/hearts/cards_hearts_j.png", ".4bpp.smol");
static const u32 gCards_Q_Hearts_Gfx[] = INCGFX_U32("graphics/blackjack/cards/hearts/cards_hearts_q.png", ".4bpp.smol");
static const u32 gCards_K_Hearts_Gfx[] = INCGFX_U32("graphics/blackjack/cards/hearts/cards_hearts_k.png", ".4bpp.smol");
static const u32 gCards_A_Hearts_Gfx[] = INCGFX_U32("graphics/blackjack/cards/hearts/cards_hearts_a.png", ".4bpp.smol");

static const u32 gCards_2_Diamonds_Gfx[] = INCGFX_U32("graphics/blackjack/cards/diamonds/cards_diamonds_2.png", ".4bpp.smol");
static const u32 gCards_3_Diamonds_Gfx[] = INCGFX_U32("graphics/blackjack/cards/diamonds/cards_diamonds_3.png", ".4bpp.smol");
static const u32 gCards_4_Diamonds_Gfx[] = INCGFX_U32("graphics/blackjack/cards/diamonds/cards_diamonds_4.png", ".4bpp.smol");
static const u32 gCards_5_Diamonds_Gfx[] = INCGFX_U32("graphics/blackjack/cards/diamonds/cards_diamonds_5.png", ".4bpp.smol");
static const u32 gCards_6_Diamonds_Gfx[] = INCGFX_U32("graphics/blackjack/cards/diamonds/cards_diamonds_6.png", ".4bpp.smol");
static const u32 gCards_7_Diamonds_Gfx[] = INCGFX_U32("graphics/blackjack/cards/diamonds/cards_diamonds_7.png", ".4bpp.smol");
static const u32 gCards_8_Diamonds_Gfx[] = INCGFX_U32("graphics/blackjack/cards/diamonds/cards_diamonds_8.png", ".4bpp.smol");
static const u32 gCards_9_Diamonds_Gfx[] = INCGFX_U32("graphics/blackjack/cards/diamonds/cards_diamonds_9.png", ".4bpp.smol");
static const u32 gCards_10_Diamonds_Gfx[] = INCGFX_U32("graphics/blackjack/cards/diamonds/cards_diamonds_10.png", ".4bpp.smol");
static const u32 gCards_J_Diamonds_Gfx[] = INCGFX_U32("graphics/blackjack/cards/diamonds/cards_diamonds_j.png", ".4bpp.smol");
static const u32 gCards_Q_Diamonds_Gfx[] = INCGFX_U32("graphics/blackjack/cards/diamonds/cards_diamonds_q.png", ".4bpp.smol");
static const u32 gCards_K_Diamonds_Gfx[] = INCGFX_U32("graphics/blackjack/cards/diamonds/cards_diamonds_k.png", ".4bpp.smol");
static const u32 gCards_A_Diamonds_Gfx[] = INCGFX_U32("graphics/blackjack/cards/diamonds/cards_diamonds_a.png", ".4bpp.smol");

static const u32 gCards_2_Clubs_Gfx[] = INCGFX_U32("graphics/blackjack/cards/clubs/cards_clubs_2.png", ".4bpp.smol");
static const u32 gCards_3_Clubs_Gfx[] = INCGFX_U32("graphics/blackjack/cards/clubs/cards_clubs_3.png", ".4bpp.smol");
static const u32 gCards_4_Clubs_Gfx[] = INCGFX_U32("graphics/blackjack/cards/clubs/cards_clubs_4.png", ".4bpp.smol");
static const u32 gCards_5_Clubs_Gfx[] = INCGFX_U32("graphics/blackjack/cards/clubs/cards_clubs_5.png", ".4bpp.smol");
static const u32 gCards_6_Clubs_Gfx[] = INCGFX_U32("graphics/blackjack/cards/clubs/cards_clubs_6.png", ".4bpp.smol");
static const u32 gCards_7_Clubs_Gfx[] = INCGFX_U32("graphics/blackjack/cards/clubs/cards_clubs_7.png", ".4bpp.smol");
static const u32 gCards_8_Clubs_Gfx[] = INCGFX_U32("graphics/blackjack/cards/clubs/cards_clubs_8.png", ".4bpp.smol");
static const u32 gCards_9_Clubs_Gfx[] = INCGFX_U32("graphics/blackjack/cards/clubs/cards_clubs_9.png", ".4bpp.smol");
static const u32 gCards_10_Clubs_Gfx[] = INCGFX_U32("graphics/blackjack/cards/clubs/cards_clubs_10.png", ".4bpp.smol");
static const u32 gCards_J_Clubs_Gfx[] = INCGFX_U32("graphics/blackjack/cards/clubs/cards_clubs_j.png", ".4bpp.smol");
static const u32 gCards_Q_Clubs_Gfx[] = INCGFX_U32("graphics/blackjack/cards/clubs/cards_clubs_q.png", ".4bpp.smol");
static const u32 gCards_K_Clubs_Gfx[] = INCGFX_U32("graphics/blackjack/cards/clubs/cards_clubs_k.png", ".4bpp.smol");
static const u32 gCards_A_Clubs_Gfx[] = INCGFX_U32("graphics/blackjack/cards/clubs/cards_clubs_a.png", ".4bpp.smol");

static const u32 gCards_2_Spades_Gfx[] = INCGFX_U32("graphics/blackjack/cards/spades/cards_spades_2.png", ".4bpp.smol");
static const u32 gCards_3_Spades_Gfx[] = INCGFX_U32("graphics/blackjack/cards/spades/cards_spades_3.png", ".4bpp.smol");
static const u32 gCards_4_Spades_Gfx[] = INCGFX_U32("graphics/blackjack/cards/spades/cards_spades_4.png", ".4bpp.smol");
static const u32 gCards_5_Spades_Gfx[] = INCGFX_U32("graphics/blackjack/cards/spades/cards_spades_5.png", ".4bpp.smol");
static const u32 gCards_6_Spades_Gfx[] = INCGFX_U32("graphics/blackjack/cards/spades/cards_spades_6.png", ".4bpp.smol");
static const u32 gCards_7_Spades_Gfx[] = INCGFX_U32("graphics/blackjack/cards/spades/cards_spades_7.png", ".4bpp.smol");
static const u32 gCards_8_Spades_Gfx[] = INCGFX_U32("graphics/blackjack/cards/spades/cards_spades_8.png", ".4bpp.smol");
static const u32 gCards_9_Spades_Gfx[] = INCGFX_U32("graphics/blackjack/cards/spades/cards_spades_9.png", ".4bpp.smol");
static const u32 gCards_10_Spades_Gfx[] = INCGFX_U32("graphics/blackjack/cards/spades/cards_spades_10.png", ".4bpp.smol");
static const u32 gCards_J_Spades_Gfx[] = INCGFX_U32("graphics/blackjack/cards/spades/cards_spades_j.png", ".4bpp.smol");
static const u32 gCards_Q_Spades_Gfx[] = INCGFX_U32("graphics/blackjack/cards/spades/cards_spades_q.png", ".4bpp.smol");
static const u32 gCards_K_Spades_Gfx[] = INCGFX_U32("graphics/blackjack/cards/spades/cards_spades_k.png", ".4bpp.smol");
static const u32 gCards_A_Spades_Gfx[] = INCGFX_U32("graphics/blackjack/cards/spades/cards_spades_a.png", ".4bpp.smol");

static const u32 gFaceDown_Gfx[] = INCGFX_U32("graphics/blackjack/facedown.png", ".4bpp.smol");
static const u16 sCards_Pal[] = INCGFX_U16("graphics/blackjack/cards.pal", ".gbapal");

static const u32 sCursor_Gfx[] = INCGFX_U32("graphics/blackjack/cursor.png", ".4bpp.smol");
static const u16 sCursorTiles_Pal[] = INCGFX_U16("graphics/blackjack/cursor.pal", ".gbapal");

static const u32 sPopup_Gfx[] = INCGFX_U32("graphics/blackjack/popup.png", ".4bpp.smol");

static void ShowHelpBar(const u8 *str);
static void SetPlayerDigits(u16);
static void SetDealerDigits(u16);
static void CreatePlayerSprites();
static void CreateDealerSprites();
static void CreatePopUpSprite();

#define BJ_BG_BASE 1
#define BJ_WIN_MENU 2

struct PlayingCard {
    u8 points;
    const struct CompressedSpriteSheet sheet;
    const struct SpriteTemplate template;
};

struct CardPosition {
    s16 x;
    s16 y;
    u8 priority;
};

static const struct CardPosition cardPositions[18] = {
    // Player cards (x, y, priority)
    {144, 120, 9}, {112, 120, 8}, {80, 120, 7}, {48, 120, 6}, {16, 120, 5},
    {64, 120, 4}, {48, 120, 3}, {32, 120, 2}, {16, 120, 1},
    
    // Dealer cards (x, y, priority)
    {16, 56, 9}, {48, 56, 8}, {80, 56, 7}, {112, 56, 6}, {144, 56, 5},
    {96, 56, 4}, {112, 56, 3}, {128, 56, 2}, {144, 56, 1}
};

static const struct BgTemplate sBJBgTemplates[] = {
    {
       .bg = BJ_BG_BASE,
       .charBaseIndex = 2,
       .mapBaseIndex = 31,
       .screenSize = 0,
       .paletteMode = 0,
       .priority = 3,
       .baseTile = 0
   },
   {
        .bg = BJ_WIN_MENU,
        .charBaseIndex = 0,
        .mapBaseIndex = 0x17,
        .screenSize = 0,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    }
};

static const struct WindowTemplate sBJWinTemplates[] = {
    {
        .bg = BJ_BG_BASE,
        .tilemapLeft = 0,
        .tilemapTop = 0,
        .width = 30,
        .height = 2,
        .paletteNum = 11,
        .baseBlock = 0x73,
    },
    {
        .bg = BJ_WIN_MENU,
        .tilemapLeft = 3,
        .tilemapTop = 15,
        .width = 14,
        .height = 4,
        .paletteNum = 0xF,
        .baseBlock = 0x194,        
    },
    DUMMY_WIN_TEMPLATE,
};

#define PALTAG_INTERFACEPLAYER 2
#define PALTAG_INTERFACEDEALER 3
#define PALTAG_CURSOR 4
#define PALTAG_OPTION1 5
#define PALTAG_OPTION2 6
#define PALTAG_CARDS_HEARTS 8
#define PALTAG_FACEDOWN 9
#define PALTAG_CARDS_CLUBS 10
#define PALTAG_CARDS_DIAMONDS 11
#define PALTAG_CARDS_SPADES 12
#define PALTAG_POPUP 13

#define GFXTAG_PLAYER_DIGIT 2
#define GFXTAG_DEALER_DIGIT 3
#define GFXTAG_CURSOR 4
#define GFXTAG_OPTION1 5
#define GFXTAG_OPTION2 6
#define GFXTAG_FACEDOWN 8

#define GFXTAG_CARDS_HEARTS_2 9
#define GFXTAG_CARDS_HEARTS_3 10
#define GFXTAG_CARDS_HEARTS_4 11
#define GFXTAG_CARDS_HEARTS_5 12
#define GFXTAG_CARDS_HEARTS_6 13
#define GFXTAG_CARDS_HEARTS_7 14
#define GFXTAG_CARDS_HEARTS_8 15
#define GFXTAG_CARDS_HEARTS_9 16
#define GFXTAG_CARDS_HEARTS_10 17
#define GFXTAG_CARDS_HEARTS_J 18
#define GFXTAG_CARDS_HEARTS_Q 19
#define GFXTAG_CARDS_HEARTS_K 20
#define GFXTAG_CARDS_HEARTS_A 21

#define GFXTAG_CARDS_DIAMONDS_2 22
#define GFXTAG_CARDS_DIAMONDS_3 23
#define GFXTAG_CARDS_DIAMONDS_4 24
#define GFXTAG_CARDS_DIAMONDS_5 25
#define GFXTAG_CARDS_DIAMONDS_6 26
#define GFXTAG_CARDS_DIAMONDS_7 27
#define GFXTAG_CARDS_DIAMONDS_8 28
#define GFXTAG_CARDS_DIAMONDS_9 29
#define GFXTAG_CARDS_DIAMONDS_10 30
#define GFXTAG_CARDS_DIAMONDS_J 31
#define GFXTAG_CARDS_DIAMONDS_Q 32
#define GFXTAG_CARDS_DIAMONDS_K 33
#define GFXTAG_CARDS_DIAMONDS_A 34

#define GFXTAG_CARDS_CLUBS_2 35
#define GFXTAG_CARDS_CLUBS_3 36
#define GFXTAG_CARDS_CLUBS_4 37
#define GFXTAG_CARDS_CLUBS_5 38
#define GFXTAG_CARDS_CLUBS_6 39
#define GFXTAG_CARDS_CLUBS_7 40
#define GFXTAG_CARDS_CLUBS_8 41
#define GFXTAG_CARDS_CLUBS_9 42
#define GFXTAG_CARDS_CLUBS_10 43
#define GFXTAG_CARDS_CLUBS_J 44
#define GFXTAG_CARDS_CLUBS_Q 45
#define GFXTAG_CARDS_CLUBS_K 46
#define GFXTAG_CARDS_CLUBS_A 47

#define GFXTAG_CARDS_SPADES_2 48
#define GFXTAG_CARDS_SPADES_3 49
#define GFXTAG_CARDS_SPADES_4 50
#define GFXTAG_CARDS_SPADES_5 51
#define GFXTAG_CARDS_SPADES_6 52
#define GFXTAG_CARDS_SPADES_7 53
#define GFXTAG_CARDS_SPADES_8 54
#define GFXTAG_CARDS_SPADES_9 55
#define GFXTAG_CARDS_SPADES_10 56
#define GFXTAG_CARDS_SPADES_J 57
#define GFXTAG_CARDS_SPADES_Q 58
#define GFXTAG_CARDS_SPADES_K 59
#define GFXTAG_CARDS_SPADES_A 60

#define GFXTAG_POPUP 61

#define STD_WINDOW_PALETTE_NUM 14
#define STD_WINDOW_PALETTE_SIZE PLTT_SIZEOF(10)

static const struct SpritePalette sSpritePalettes[] =
{
    { .data = sPlayer_Pal,        .tag = PALTAG_INTERFACEPLAYER },
    { .data = sDealer_Pal,        .tag = PALTAG_INTERFACEDEALER },
    { .data = sCursorTiles_Pal, .tag = PALTAG_CURSOR },
    { .data = sCursorTiles_Pal, .tag = PALTAG_OPTION1 },
    { .data = sCursorTiles_Pal, .tag = PALTAG_OPTION2 },
    { .data = sCards_Pal,        .tag = PALTAG_CARDS_HEARTS },
    { .data = sCards_Pal,        .tag = PALTAG_FACEDOWN },
    { .data = sCards_Pal,        .tag = PALTAG_CARDS_CLUBS },
    { .data = sCards_Pal,        .tag = PALTAG_CARDS_DIAMONDS },
    { .data = sCards_Pal,        .tag = PALTAG_CARDS_SPADES },
    { .data = sCursorTiles_Pal, .tag = PALTAG_POPUP },
    {}
};

static const struct CompressedSpriteSheet sSpriteSheet_Cursor =
{
    .data = sCursor_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CURSOR,
};

static const struct CompressedSpriteSheet sSpriteSheet_Popup =
{
    .data = sPopup_Gfx,
    .size = 0x800,
    .tag = GFXTAG_POPUP,
};

static const struct CompressedSpriteSheet sSpriteSheet_Option1 =
{
    .data = gOption_1_Gfx,
    .size = 0x100,
    .tag = GFXTAG_OPTION1,
};

static const struct CompressedSpriteSheet sSpriteSheet_Option2 =
{
    .data = gOption_2_Gfx,
    .size = 0x100,
    .tag = GFXTAG_OPTION2,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Hearts_2 =
{
    .data = gCards_2_Hearts_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_HEARTS_2,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Hearts_3 =
{
    .data = gCards_3_Hearts_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_HEARTS_3,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Hearts_4 =
{
    .data = gCards_4_Hearts_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_HEARTS_4,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Hearts_5 =
{
    .data = gCards_5_Hearts_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_HEARTS_5,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Hearts_6 =
{
    .data = gCards_6_Hearts_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_HEARTS_6,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Hearts_7 =
{
    .data = gCards_7_Hearts_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_HEARTS_7,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Hearts_8 =
{
    .data = gCards_8_Hearts_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_HEARTS_8,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Hearts_9 =
{
    .data = gCards_9_Hearts_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_HEARTS_9,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Hearts_10 =
{
    .data = gCards_10_Hearts_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_HEARTS_10,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Hearts_J =
{
    .data = gCards_J_Hearts_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_HEARTS_J,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Hearts_Q =
{
    .data = gCards_Q_Hearts_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_HEARTS_Q,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Hearts_K =
{
    .data = gCards_K_Hearts_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_HEARTS_K,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Hearts_A =
{
    .data = gCards_A_Hearts_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_HEARTS_A,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Clubs_2 =
{
    .data = gCards_2_Clubs_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_CLUBS_2,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Clubs_3 =
{
    .data = gCards_3_Clubs_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_CLUBS_3,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Clubs_4 =
{
    .data = gCards_4_Clubs_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_CLUBS_4,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Clubs_5 =
{
    .data = gCards_5_Clubs_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_CLUBS_5,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Clubs_6 =
{
    .data = gCards_6_Clubs_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_CLUBS_6,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Clubs_7 =
{
    .data = gCards_7_Clubs_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_CLUBS_7,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Clubs_8 =
{
    .data = gCards_8_Clubs_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_CLUBS_8,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Clubs_9 =
{
    .data = gCards_9_Clubs_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_CLUBS_9,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Clubs_10 =
{
    .data = gCards_10_Clubs_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_CLUBS_10,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Clubs_J =
{
    .data = gCards_J_Clubs_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_CLUBS_J,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Clubs_Q =
{
    .data = gCards_Q_Clubs_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_CLUBS_Q,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Clubs_A =
{
    .data = gCards_A_Clubs_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_CLUBS_A,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Clubs_K =
{
    .data = gCards_K_Clubs_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_CLUBS_K,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Diamonds_2 =
{
    .data = gCards_2_Diamonds_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_DIAMONDS_2,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Diamonds_3 =
{
    .data = gCards_3_Diamonds_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_DIAMONDS_3,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Diamonds_4 =
{
    .data = gCards_4_Diamonds_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_DIAMONDS_4,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Diamonds_5 =
{
    .data = gCards_5_Diamonds_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_DIAMONDS_5,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Diamonds_6 =
{
    .data = gCards_6_Diamonds_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_DIAMONDS_6,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Diamonds_7 =
{
    .data = gCards_7_Diamonds_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_DIAMONDS_7,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Diamonds_8 =
{
    .data = gCards_8_Diamonds_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_DIAMONDS_8,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Diamonds_9 =
{
    .data = gCards_9_Diamonds_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_DIAMONDS_9,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Diamonds_10 =
{
    .data = gCards_10_Diamonds_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_DIAMONDS_10,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Diamonds_J =
{
    .data = gCards_J_Diamonds_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_DIAMONDS_J,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Diamonds_Q =
{
    .data = gCards_Q_Diamonds_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_DIAMONDS_Q,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Diamonds_K =
{
    .data = gCards_K_Diamonds_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_DIAMONDS_K,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Diamonds_A =
{
    .data = gCards_A_Diamonds_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_DIAMONDS_A,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Spades_2 =
{
    .data = gCards_2_Spades_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_SPADES_2,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Spades_3 =
{
    .data = gCards_3_Spades_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_SPADES_3,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Spades_4 =
{
    .data = gCards_4_Spades_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_SPADES_4,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Spades_5 =
{
    .data = gCards_5_Spades_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_SPADES_5,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Spades_6 =
{
    .data = gCards_6_Spades_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_SPADES_6,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Spades_7 =
{
    .data = gCards_7_Spades_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_SPADES_7,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Spades_8 =
{
    .data = gCards_8_Spades_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_SPADES_8,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Spades_9 =
{
    .data = gCards_9_Spades_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_SPADES_9,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Spades_10 =
{
    .data = gCards_10_Spades_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_SPADES_10,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Spades_J =
{
    .data = gCards_J_Spades_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_SPADES_J,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Spades_Q =
{
    .data = gCards_Q_Spades_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_SPADES_Q,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Spades_K =
{
    .data = gCards_K_Spades_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_SPADES_K,
};

static const struct CompressedSpriteSheet sSpriteSheet_Cards_Spades_A =
{
    .data = gCards_A_Spades_Gfx,
    .size = 0x400,
    .tag = GFXTAG_CARDS_SPADES_A,
};

static const struct CompressedSpriteSheet sSpriteSheet_Facedown =
{
    .data = gFaceDown_Gfx,
    .size = 0x400,
    .tag = GFXTAG_FACEDOWN,
};

static const struct OamData sOamData_Cards_Hearts =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .shape = SPRITE_SHAPE(32x64),
    .size = SPRITE_SIZE(32x64),
    .tileNum = 0,
    .priority = 0,
};

static const struct OamData sOamData_Cards_Diamonds =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .shape = SPRITE_SHAPE(32x64),
    .size = SPRITE_SIZE(32x64),
    .tileNum = 0,
    .priority = 0,
};

static const struct OamData sOamData_Cards_Clubs =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .shape = SPRITE_SHAPE(32x64),
    .size = SPRITE_SIZE(32x64),
    .tileNum = 0,
    .priority = 0,
};

static const struct OamData sOamData_Cards_Spades =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .shape = SPRITE_SHAPE(32x64),
    .size = SPRITE_SIZE(32x64),
    .tileNum = 0,
    .priority = 0,
};

static const struct OamData sOamData_Facedown =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .shape = SPRITE_SHAPE(32x64),
    .size = SPRITE_SIZE(32x64),
    .tileNum = 0,
    .priority = 0,
};

static const struct OamData sOamData_Cursor =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .shape = SPRITE_SHAPE(64x32),
    .size = SPRITE_SIZE(64x32),
    .tileNum = 0,
    .priority = 0,
};

static const struct OamData sOamData_Popup =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .shape = SPRITE_SHAPE(64x64),
    .size = SPRITE_SIZE(64x64),
    .tileNum = 0,
    .priority = 0,
};

static const struct OamData sOamData_Option1 =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .shape = SPRITE_SHAPE(32x16),
    .size = SPRITE_SIZE(32x16),
    .tileNum = 0,
    .priority = 0,
};

static const struct OamData sOamData_Option2 =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .shape = SPRITE_SHAPE(32x16),
    .size = SPRITE_SIZE(32x16),
    .tileNum = 0,
    .priority = 0,
};

static const struct SpriteTemplate sSpriteTemplate_Facedown =
{
    .tileTag = GFXTAG_FACEDOWN,
    .paletteTag = PALTAG_FACEDOWN,
    .oam = &sOamData_Facedown,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Popup =
{
    .tileTag = GFXTAG_POPUP,
    .paletteTag = PALTAG_POPUP,
    .oam = &sOamData_Popup,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Hearts_2 =
{
    .tileTag = GFXTAG_CARDS_HEARTS_2,
    .paletteTag = PALTAG_CARDS_HEARTS,
    .oam = &sOamData_Cards_Hearts,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Hearts_3 =
{
    .tileTag = GFXTAG_CARDS_HEARTS_3,
    .paletteTag = PALTAG_CARDS_HEARTS,
    .oam = &sOamData_Cards_Hearts,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Hearts_4 =
{
    .tileTag = GFXTAG_CARDS_HEARTS_4,
    .paletteTag = PALTAG_CARDS_HEARTS,
    .oam = &sOamData_Cards_Hearts,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Hearts_5 =
{
    .tileTag = GFXTAG_CARDS_HEARTS_5,
    .paletteTag = PALTAG_CARDS_HEARTS,
    .oam = &sOamData_Cards_Hearts,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Hearts_6 =
{
    .tileTag = GFXTAG_CARDS_HEARTS_6,
    .paletteTag = PALTAG_CARDS_HEARTS,
    .oam = &sOamData_Cards_Hearts,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Hearts_7 =
{
    .tileTag = GFXTAG_CARDS_HEARTS_7,
    .paletteTag = PALTAG_CARDS_HEARTS,
    .oam = &sOamData_Cards_Hearts,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Hearts_8 =
{
    .tileTag = GFXTAG_CARDS_HEARTS_8,
    .paletteTag = PALTAG_CARDS_HEARTS,
    .oam = &sOamData_Cards_Hearts,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Hearts_9 =
{
    .tileTag = GFXTAG_CARDS_HEARTS_9,
    .paletteTag = PALTAG_CARDS_HEARTS,
    .oam = &sOamData_Cards_Hearts,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Hearts_10 =
{
    .tileTag = GFXTAG_CARDS_HEARTS_10,
    .paletteTag = PALTAG_CARDS_HEARTS,
    .oam = &sOamData_Cards_Hearts,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Hearts_J =
{
    .tileTag = GFXTAG_CARDS_HEARTS_J,
    .paletteTag = PALTAG_CARDS_HEARTS,
    .oam = &sOamData_Cards_Hearts,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Hearts_Q =
{
    .tileTag = GFXTAG_CARDS_HEARTS_Q,
    .paletteTag = PALTAG_CARDS_HEARTS,
    .oam = &sOamData_Cards_Hearts,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Hearts_K =
{
    .tileTag = GFXTAG_CARDS_HEARTS_K,
    .paletteTag = PALTAG_CARDS_HEARTS,
    .oam = &sOamData_Cards_Hearts,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Hearts_A =
{
    .tileTag = GFXTAG_CARDS_HEARTS_A,
    .paletteTag = PALTAG_CARDS_HEARTS,
    .oam = &sOamData_Cards_Hearts,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Clubs_2 =
{
    .tileTag = GFXTAG_CARDS_CLUBS_2,
    .paletteTag = PALTAG_CARDS_CLUBS,
    .oam = &sOamData_Cards_Clubs,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Clubs_3 =
{
    .tileTag = GFXTAG_CARDS_CLUBS_3,
    .paletteTag = PALTAG_CARDS_CLUBS,
    .oam = &sOamData_Cards_Clubs,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Clubs_4 =
{
    .tileTag = GFXTAG_CARDS_CLUBS_4,
    .paletteTag = PALTAG_CARDS_CLUBS,
    .oam = &sOamData_Cards_Clubs,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Clubs_5 =
{
    .tileTag = GFXTAG_CARDS_CLUBS_5,
    .paletteTag = PALTAG_CARDS_CLUBS,
    .oam = &sOamData_Cards_Clubs,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Clubs_6 =
{
    .tileTag = GFXTAG_CARDS_CLUBS_6,
    .paletteTag = PALTAG_CARDS_CLUBS,
    .oam = &sOamData_Cards_Clubs,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Clubs_7 =
{
    .tileTag = GFXTAG_CARDS_CLUBS_7,
    .paletteTag = PALTAG_CARDS_CLUBS,
    .oam = &sOamData_Cards_Clubs,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Clubs_8 =
{
    .tileTag = GFXTAG_CARDS_CLUBS_8,
    .paletteTag = PALTAG_CARDS_CLUBS,
    .oam = &sOamData_Cards_Clubs,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Clubs_9 =
{
    .tileTag = GFXTAG_CARDS_CLUBS_9,
    .paletteTag = PALTAG_CARDS_CLUBS,
    .oam = &sOamData_Cards_Clubs,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Clubs_10 =
{
    .tileTag = GFXTAG_CARDS_CLUBS_10,
    .paletteTag = PALTAG_CARDS_CLUBS,
    .oam = &sOamData_Cards_Clubs,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Clubs_J =
{
    .tileTag = GFXTAG_CARDS_CLUBS_J,
    .paletteTag = PALTAG_CARDS_CLUBS,
    .oam = &sOamData_Cards_Clubs,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Clubs_Q =
{
    .tileTag = GFXTAG_CARDS_CLUBS_Q,
    .paletteTag = PALTAG_CARDS_CLUBS,
    .oam = &sOamData_Cards_Clubs,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Clubs_K =
{
    .tileTag = GFXTAG_CARDS_CLUBS_K,
    .paletteTag = PALTAG_CARDS_CLUBS,
    .oam = &sOamData_Cards_Clubs,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Clubs_A =
{
    .tileTag = GFXTAG_CARDS_CLUBS_A,
    .paletteTag = PALTAG_CARDS_CLUBS,
    .oam = &sOamData_Cards_Clubs,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Diamonds_2 =
{
    .tileTag = GFXTAG_CARDS_DIAMONDS_2,
    .paletteTag = PALTAG_CARDS_DIAMONDS,
    .oam = &sOamData_Cards_Diamonds,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Diamonds_3 =
{
    .tileTag = GFXTAG_CARDS_DIAMONDS_3,
    .paletteTag = PALTAG_CARDS_DIAMONDS,
    .oam = &sOamData_Cards_Diamonds,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Diamonds_4 =
{
    .tileTag = GFXTAG_CARDS_DIAMONDS_4,
    .paletteTag = PALTAG_CARDS_DIAMONDS,
    .oam = &sOamData_Cards_Diamonds,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Diamonds_5 =
{
    .tileTag = GFXTAG_CARDS_DIAMONDS_5,
    .paletteTag = PALTAG_CARDS_DIAMONDS,
    .oam = &sOamData_Cards_Diamonds,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Diamonds_6 =
{
    .tileTag = GFXTAG_CARDS_DIAMONDS_6,
    .paletteTag = PALTAG_CARDS_DIAMONDS,
    .oam = &sOamData_Cards_Diamonds,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Diamonds_7 =
{
    .tileTag = GFXTAG_CARDS_DIAMONDS_7,
    .paletteTag = PALTAG_CARDS_DIAMONDS,
    .oam = &sOamData_Cards_Diamonds,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Diamonds_8 =
{
    .tileTag = GFXTAG_CARDS_DIAMONDS_8,
    .paletteTag = PALTAG_CARDS_DIAMONDS,
    .oam = &sOamData_Cards_Diamonds,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Diamonds_9 =
{
    .tileTag = GFXTAG_CARDS_DIAMONDS_9,
    .paletteTag = PALTAG_CARDS_DIAMONDS,
    .oam = &sOamData_Cards_Diamonds,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Diamonds_10 =
{
    .tileTag = GFXTAG_CARDS_DIAMONDS_10,
    .paletteTag = PALTAG_CARDS_DIAMONDS,
    .oam = &sOamData_Cards_Diamonds,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Diamonds_J =
{
    .tileTag = GFXTAG_CARDS_DIAMONDS_J,
    .paletteTag = PALTAG_CARDS_DIAMONDS,
    .oam = &sOamData_Cards_Diamonds,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Diamonds_Q =
{
    .tileTag = GFXTAG_CARDS_DIAMONDS_Q,
    .paletteTag = PALTAG_CARDS_DIAMONDS,
    .oam = &sOamData_Cards_Diamonds,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Diamonds_K =
{
    .tileTag = GFXTAG_CARDS_DIAMONDS_K,
    .paletteTag = PALTAG_CARDS_DIAMONDS,
    .oam = &sOamData_Cards_Diamonds,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Diamonds_A =
{
    .tileTag = GFXTAG_CARDS_DIAMONDS_A,
    .paletteTag = PALTAG_CARDS_DIAMONDS,
    .oam = &sOamData_Cards_Diamonds,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Spades_2 =
{
    .tileTag = GFXTAG_CARDS_SPADES_2,
    .paletteTag = PALTAG_CARDS_SPADES,
    .oam = &sOamData_Cards_Spades,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Spades_3 =
{
    .tileTag = GFXTAG_CARDS_SPADES_3,
    .paletteTag = PALTAG_CARDS_SPADES,
    .oam = &sOamData_Cards_Spades,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Spades_4 =
{
    .tileTag = GFXTAG_CARDS_SPADES_4,
    .paletteTag = PALTAG_CARDS_SPADES,
    .oam = &sOamData_Cards_Spades,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Spades_5 =
{
    .tileTag = GFXTAG_CARDS_SPADES_5,
    .paletteTag = PALTAG_CARDS_SPADES,
    .oam = &sOamData_Cards_Spades,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Spades_6 =
{
    .tileTag = GFXTAG_CARDS_SPADES_6,
    .paletteTag = PALTAG_CARDS_SPADES,
    .oam = &sOamData_Cards_Spades,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Spades_7 =
{
    .tileTag = GFXTAG_CARDS_SPADES_7,
    .paletteTag = PALTAG_CARDS_SPADES,
    .oam = &sOamData_Cards_Spades,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Spades_8 =
{
    .tileTag = GFXTAG_CARDS_SPADES_8,
    .paletteTag = PALTAG_CARDS_SPADES,
    .oam = &sOamData_Cards_Spades,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Spades_9 =
{
    .tileTag = GFXTAG_CARDS_SPADES_9,
    .paletteTag = PALTAG_CARDS_SPADES,
    .oam = &sOamData_Cards_Spades,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Spades_10 =
{
    .tileTag = GFXTAG_CARDS_SPADES_10,
    .paletteTag = PALTAG_CARDS_SPADES,
    .oam = &sOamData_Cards_Spades,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Spades_J =
{
    .tileTag = GFXTAG_CARDS_SPADES_J,
    .paletteTag = PALTAG_CARDS_SPADES,
    .oam = &sOamData_Cards_Spades,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Spades_Q =
{
    .tileTag = GFXTAG_CARDS_SPADES_Q,
    .paletteTag = PALTAG_CARDS_SPADES,
    .oam = &sOamData_Cards_Spades,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Spades_K =
{
    .tileTag = GFXTAG_CARDS_SPADES_K,
    .paletteTag = PALTAG_CARDS_SPADES,
    .oam = &sOamData_Cards_Spades,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cards_Spades_A =
{
    .tileTag = GFXTAG_CARDS_SPADES_A,
    .paletteTag = PALTAG_CARDS_SPADES,
    .oam = &sOamData_Cards_Spades,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Cursor =
{
    .tileTag = GFXTAG_CURSOR,
    .paletteTag = PALTAG_CURSOR,
    .oam = &sOamData_Cursor,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Option1 =
{
    .tileTag = GFXTAG_OPTION1,
    .paletteTag = PALTAG_OPTION1,
    .oam = &sOamData_Option1,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_Option2 =
{
    .tileTag = GFXTAG_OPTION2,
    .paletteTag = PALTAG_OPTION2,
    .oam = &sOamData_Option2,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

const struct PlayingCard sPlayingCards[CARD_COUNT] =
{
    [CARD_HEARTS_2] =
    {
        .points = CARD_SCORE_2,
        .sheet = sSpriteSheet_Cards_Hearts_2,
        .template = sSpriteTemplate_Cards_Hearts_2,
    },
    [CARD_HEARTS_3] =
    {
        .points = CARD_SCORE_3,
        .sheet = sSpriteSheet_Cards_Hearts_3,
        .template = sSpriteTemplate_Cards_Hearts_3,
    },
    [CARD_HEARTS_4] =
    {
        .points = CARD_SCORE_4,
        .sheet = sSpriteSheet_Cards_Hearts_4,
        .template = sSpriteTemplate_Cards_Hearts_4,
    },
    [CARD_HEARTS_5] =
    {
        .points = CARD_SCORE_5,
        .sheet = sSpriteSheet_Cards_Hearts_5,
        .template = sSpriteTemplate_Cards_Hearts_5,
    },
    [CARD_HEARTS_6] =
    {
        .points = CARD_SCORE_6,
        .sheet = sSpriteSheet_Cards_Hearts_6,
        .template = sSpriteTemplate_Cards_Hearts_6,
    },
    [CARD_HEARTS_7] =
    {
        .points = CARD_SCORE_7,
        .sheet = sSpriteSheet_Cards_Hearts_7,
        .template = sSpriteTemplate_Cards_Hearts_7,
    },
    [CARD_HEARTS_8] =
    {
        .points = CARD_SCORE_8,
        .sheet = sSpriteSheet_Cards_Hearts_8,
        .template = sSpriteTemplate_Cards_Hearts_8,
    },
    [CARD_HEARTS_9] =
    {
        .points = CARD_SCORE_9,
        .sheet = sSpriteSheet_Cards_Hearts_9,
        .template = sSpriteTemplate_Cards_Hearts_9,
    },
    [CARD_HEARTS_10] =
    {
        .points = CARD_SCORE_10,
        .sheet = sSpriteSheet_Cards_Hearts_10,
        .template = sSpriteTemplate_Cards_Hearts_10,
    },
    [CARD_HEARTS_JACK] =
    {
        .points = CARD_SCORE_FACE,
        .sheet = sSpriteSheet_Cards_Hearts_J,
        .template = sSpriteTemplate_Cards_Hearts_J,
    },
    [CARD_HEARTS_QUEEN] =
    {
        .points = CARD_SCORE_FACE,
        .sheet = sSpriteSheet_Cards_Hearts_Q,
        .template = sSpriteTemplate_Cards_Hearts_Q,
    },
    [CARD_HEARTS_KING] =
    {
        .points = CARD_SCORE_FACE,
        .sheet = sSpriteSheet_Cards_Hearts_K,
        .template = sSpriteTemplate_Cards_Hearts_K,
    },
    [CARD_HEARTS_ACE] =
    {
        .points = CARD_SCORE_ACE,
        .sheet = sSpriteSheet_Cards_Hearts_A,
        .template = sSpriteTemplate_Cards_Hearts_A,
    },
    [CARD_CLUBS_2] =
    {
        .points = CARD_SCORE_2,
        .sheet = sSpriteSheet_Cards_Clubs_2,
        .template = sSpriteTemplate_Cards_Clubs_2,
    },
    [CARD_CLUBS_3] =
    {
        .points = CARD_SCORE_3,
        .sheet = sSpriteSheet_Cards_Clubs_3,
        .template = sSpriteTemplate_Cards_Clubs_3,
    },
    [CARD_CLUBS_4] =
    {
        .points = CARD_SCORE_4,
        .sheet = sSpriteSheet_Cards_Clubs_4,
        .template = sSpriteTemplate_Cards_Clubs_4,
    },
    [CARD_CLUBS_5] =
    {
        .points = CARD_SCORE_5,
        .sheet = sSpriteSheet_Cards_Clubs_5,
        .template = sSpriteTemplate_Cards_Clubs_5,
    },
    [CARD_CLUBS_6] =
    {
        .points = CARD_SCORE_6,
        .sheet = sSpriteSheet_Cards_Clubs_6,
        .template = sSpriteTemplate_Cards_Clubs_6,
    },
    [CARD_CLUBS_7] =
    {
        .points = CARD_SCORE_7,
        .sheet = sSpriteSheet_Cards_Clubs_7,
        .template = sSpriteTemplate_Cards_Clubs_7,
    },
    [CARD_CLUBS_8] =
    {
        .points = CARD_SCORE_8,
        .sheet = sSpriteSheet_Cards_Clubs_8,
        .template = sSpriteTemplate_Cards_Clubs_8,
    },
    [CARD_CLUBS_9] =
    {
        .points = CARD_SCORE_9,
        .sheet = sSpriteSheet_Cards_Clubs_9,
        .template = sSpriteTemplate_Cards_Clubs_9,
    },
    [CARD_CLUBS_10] =
    {
        .points = CARD_SCORE_10,
        .sheet = sSpriteSheet_Cards_Clubs_10,
        .template = sSpriteTemplate_Cards_Clubs_10,
    },
    [CARD_CLUBS_JACK] =
    {
        .points = CARD_SCORE_FACE,
        .sheet = sSpriteSheet_Cards_Clubs_J,
        .template = sSpriteTemplate_Cards_Clubs_J,
    },
    [CARD_CLUBS_QUEEN] =
    {
        .points = CARD_SCORE_FACE,
        .sheet = sSpriteSheet_Cards_Clubs_Q,
        .template = sSpriteTemplate_Cards_Clubs_Q,
    },
    [CARD_CLUBS_KING] =
    {
        .points = CARD_SCORE_FACE,
        .sheet = sSpriteSheet_Cards_Clubs_K,
        .template = sSpriteTemplate_Cards_Clubs_K,
    },
    [CARD_CLUBS_ACE] =
    {
        .points = CARD_SCORE_ACE,
        .sheet = sSpriteSheet_Cards_Clubs_A,
        .template = sSpriteTemplate_Cards_Clubs_A,
    },
    [CARD_DIAMONDS_2] =
    {
        .points = CARD_SCORE_2,
        .sheet = sSpriteSheet_Cards_Diamonds_2,
        .template = sSpriteTemplate_Cards_Diamonds_2,
    },
    [CARD_DIAMONDS_3] =
    {
        .points = CARD_SCORE_3,
        .sheet = sSpriteSheet_Cards_Diamonds_3,
        .template = sSpriteTemplate_Cards_Diamonds_3,
    },
    [CARD_DIAMONDS_4] =
    {
        .points = CARD_SCORE_4,
        .sheet = sSpriteSheet_Cards_Diamonds_4,
        .template = sSpriteTemplate_Cards_Diamonds_4,
    },
    [CARD_DIAMONDS_5] =
    {
        .points = CARD_SCORE_5,
        .sheet = sSpriteSheet_Cards_Diamonds_5,
        .template = sSpriteTemplate_Cards_Diamonds_5,
    },
    [CARD_DIAMONDS_6] =
    {
        .points = CARD_SCORE_6,
        .sheet = sSpriteSheet_Cards_Diamonds_6,
        .template = sSpriteTemplate_Cards_Diamonds_6,
    },
    [CARD_DIAMONDS_7] =
    {
        .points = CARD_SCORE_7,
        .sheet = sSpriteSheet_Cards_Diamonds_7,
        .template = sSpriteTemplate_Cards_Diamonds_7,
    },
    [CARD_DIAMONDS_8] =
    {
        .points = CARD_SCORE_8,
        .sheet = sSpriteSheet_Cards_Diamonds_8,
        .template = sSpriteTemplate_Cards_Diamonds_8,
    },
    [CARD_DIAMONDS_9] =
    {
        .points = CARD_SCORE_9,
        .sheet = sSpriteSheet_Cards_Diamonds_9,
        .template = sSpriteTemplate_Cards_Diamonds_9,
    },
    [CARD_DIAMONDS_10] =
    {
        .points = CARD_SCORE_10,
        .sheet = sSpriteSheet_Cards_Diamonds_10,
        .template = sSpriteTemplate_Cards_Diamonds_10,
    },
    [CARD_DIAMONDS_JACK] =
    {
        .points = CARD_SCORE_FACE,
        .sheet = sSpriteSheet_Cards_Diamonds_J,
        .template = sSpriteTemplate_Cards_Diamonds_J,
    },
    [CARD_DIAMONDS_QUEEN] =
    {
        .points = CARD_SCORE_FACE,
        .sheet = sSpriteSheet_Cards_Diamonds_Q,
        .template = sSpriteTemplate_Cards_Diamonds_Q,
    },
    [CARD_DIAMONDS_KING] =
    {
        .points = CARD_SCORE_FACE,
        .sheet = sSpriteSheet_Cards_Diamonds_K,
        .template = sSpriteTemplate_Cards_Diamonds_K,
    },
    [CARD_DIAMONDS_ACE] =
    {
        .points = CARD_SCORE_ACE,
        .sheet = sSpriteSheet_Cards_Diamonds_A,
        .template = sSpriteTemplate_Cards_Diamonds_A,
    },
    [CARD_SPADES_2] =
    {
        .points = CARD_SCORE_2,
        .sheet = sSpriteSheet_Cards_Spades_2,
        .template = sSpriteTemplate_Cards_Spades_2,
    },
    [CARD_SPADES_3] =
    {
        .points = CARD_SCORE_3,
        .sheet = sSpriteSheet_Cards_Spades_3,
        .template = sSpriteTemplate_Cards_Spades_3,
    },
    [CARD_SPADES_4] =
    {
        .points = CARD_SCORE_4,
        .sheet = sSpriteSheet_Cards_Spades_4,
        .template = sSpriteTemplate_Cards_Spades_4,
    },
    [CARD_SPADES_5] =
    {
        .points = CARD_SCORE_5,
        .sheet = sSpriteSheet_Cards_Spades_5,
        .template = sSpriteTemplate_Cards_Spades_5,
    },
    [CARD_SPADES_6] =
    {
        .points = CARD_SCORE_6,
        .sheet = sSpriteSheet_Cards_Spades_6,
        .template = sSpriteTemplate_Cards_Spades_6,
    },
    [CARD_SPADES_7] =
    {
        .points = CARD_SCORE_7,
        .sheet = sSpriteSheet_Cards_Spades_7,
        .template = sSpriteTemplate_Cards_Spades_7,
    },
    [CARD_SPADES_8] =
    {
        .points = CARD_SCORE_8,
        .sheet = sSpriteSheet_Cards_Spades_8,
        .template = sSpriteTemplate_Cards_Spades_8,
    },
    [CARD_SPADES_9] =
    {
        .points = CARD_SCORE_9,
        .sheet = sSpriteSheet_Cards_Spades_9,
        .template = sSpriteTemplate_Cards_Spades_9,
    },
    [CARD_SPADES_10] =
    {
        .points = CARD_SCORE_10,
        .sheet = sSpriteSheet_Cards_Spades_10,
        .template = sSpriteTemplate_Cards_Spades_10,
    },
    [CARD_SPADES_JACK] =
    {
        .points = CARD_SCORE_FACE,
        .sheet = sSpriteSheet_Cards_Spades_J,
        .template = sSpriteTemplate_Cards_Spades_J,
    },
    [CARD_SPADES_QUEEN] =
    {
        .points = CARD_SCORE_FACE,
        .sheet = sSpriteSheet_Cards_Spades_Q,
        .template = sSpriteTemplate_Cards_Spades_Q,
    },
    [CARD_SPADES_KING] =
    {
        .points = CARD_SCORE_FACE,
        .sheet = sSpriteSheet_Cards_Spades_K,
        .template = sSpriteTemplate_Cards_Spades_K,
    },
    [CARD_SPADES_ACE] =
    {
        .points = CARD_SCORE_ACE,
        .sheet = sSpriteSheet_Cards_Spades_A,
        .template = sSpriteTemplate_Cards_Spades_A,
    },
};

void StartBlackJack(void)
{
    gSpecialVar_Result = BLACKJACK_RESULT_QUIT;
    sBlackJack = AllocZeroed(sizeof(*sBlackJack));
    if (sBlackJack != NULL)
        CreateTask(FadeToBJScreen, 0);
    else
        CreateTask(Task_ResumeAfterBlackjackAllocFailure, 0);
}

static void Task_ResumeAfterBlackjackAllocFailure(u8 taskId)
{
    ScriptContext_Enable();
    DestroyTask(taskId);
}

static void FadeToBJScreen(u8 taskId)
{
    switch (gTasks[taskId].data[0])
    {
    case 0:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].data[0]++;
        break;
    case 1:
        if (!gPaletteFade.active)
        {
            SetMainCallback2(InitBJScreen);
            DestroyTask(taskId);
        }
        break;
    }
}

static const struct CompressedSpriteSheet sSpriteSheets_PlayerInterface[] =
{
    {
        .data = gPlayer_Gfx,
        .size = 0x280,
        .tag = GFXTAG_PLAYER_DIGIT,
    },
    {},
};

static const struct CompressedSpriteSheet sSpriteSheets_DealerInterface[] =
{
    {
        .data = gDealer_Gfx,
        .size = 0x280,
        .tag = GFXTAG_DEALER_DIGIT,
    },
    {},
};

static const struct OamData sOam_ScoreDigit =
{
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .shape = SPRITE_SHAPE(8x16),
    .size = SPRITE_SIZE(8x16),
    .priority = 2,
};

static const struct SpriteTemplate sSpriteTemplate_PlayerDigit =
{
    .tileTag = GFXTAG_PLAYER_DIGIT,
    .paletteTag = PALTAG_INTERFACEPLAYER,
    .oam = &sOam_ScoreDigit,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static const struct SpriteTemplate sSpriteTemplate_DealerDigit =
{
    .tileTag = GFXTAG_DEALER_DIGIT,
    .paletteTag = PALTAG_INTERFACEDEALER,
    .oam = &sOam_ScoreDigit,
    .anims = gDummySpriteAnimTable,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy,
};

static void BJMainCallback(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    RunTextPrinters();
    UpdatePaletteFade();
}

static void SetScoreDigits(const u8 *spriteIds, u8 score)
{
    u8 i;

    for (i = 0; i < 2; i++)
    {
        u8 digit = (i == 0) ? score / 10 : score % 10;
        struct Sprite *sprite = &gSprites[spriteIds[i]];

        sprite->invisible = FALSE;
        sprite->oam.tileNum = sprite->sheetTileStart + digit * 2;
        sprite->oam.priority = 2;
    }
}

static void SetPlayerDigits(u16 score)
{
    SetScoreDigits(sBlackJack->PlayerSpriteIds, score);
}

static void SetDealerDigits(u16 score)
{
    SetScoreDigits(sBlackJack->DealerSpriteIds, score);
}

static void CreatePlayerSprites(void)
{
    u8 i;

    for (i = 0; i < ARRAY_COUNT(sSpriteSheets_PlayerInterface) - 1; i++)
        LoadCompressedSpriteSheet(&sSpriteSheets_PlayerInterface[i]);

    for (i = 0; i < MAX_SPRITES_PLAYER; i++)
        sBlackJack->PlayerSpriteIds[i] = CreateSprite(&sSpriteTemplate_PlayerDigit, i * 8 + 180, 148, 2);
}

static void CreateDealerSprites(void)
{
    u8 i;

    for (i = 0; i < ARRAY_COUNT(sSpriteSheets_DealerInterface) - 1; i++)
        LoadCompressedSpriteSheet(&sSpriteSheets_DealerInterface[i]);

    for (i = 0; i < MAX_SPRITES_DEALER; i++)
        sBlackJack->DealerSpriteIds[i] = CreateSprite(&sSpriteTemplate_DealerDigit, i * 8 + 211, 148, 2);
}

static void SetMode(void)
{
    bool8 showOptions = sBlackJack->optionMode == OPTION_HIT_STAND;

    gSprites[sBlackJack->cursorSpriteId].y = 57;
    gSprites[sBlackJack->cursorSpriteId].invisible = !showOptions;
    gSprites[sBlackJack->option1SpriteId].invisible = !showOptions;
    gSprites[sBlackJack->option2SpriteId].invisible = !showOptions;
}

static void SetOptionMode(u8 optionMode)
{
    sBlackJack->optionMode = optionMode;
    SetMode();
}

static void ShowMessage(const u8 *str)
{
    FillWindowPixelBuffer(sTextWindowId, PIXEL_FILL(0));
    PutWindowTilemap(sTextWindowId);
    LoadUserWindowBorderGfx(sTextWindowId, 0x214, BG_PLTT_ID(14));
    DrawStdWindowFrame(sTextWindowId, FALSE);
    AddTextPrinterParameterized(sTextWindowId, FONT_NORMAL, str, 0, 1, TEXT_SKIP_DRAW, NULL);
    CopyWindowToVram(sTextWindowId, COPYWIN_FULL);
}

static u8 CalculateHandScore(const u8 *cards, u8 count)
{
    u8 i;
    u8 aces = 0;
    u8 score = 0;

    for (i = 0; i < count; i++)
    {
        u8 points = sPlayingCards[cards[i]].points;

        if (points == CARD_SCORE_ACE)
        {
            aces++;
            score += CARD_SCORE_ACE_SHRUNK;
        }
        else
        {
            score += points;
        }
    }

    if (aces != 0 && score + (CARD_SCORE_ACE_EXPANDED - CARD_SCORE_ACE_SHRUNK) <= CARD_SCORE_BLACK_JACK)
        score += CARD_SCORE_ACE_EXPANDED - CARD_SCORE_ACE_SHRUNK;

    return score;
}

static void DealInitialHand(void)
{
    sBlackJack->numPlayerCards = 2;
    sBlackJack->numDealerCards = 1;
    UpdateCardVisibility();
    AdjustCards();
    gSprites[sBlackJack->DealerFaceDownId].invisible = FALSE;
    sBlackJack->playerScore = CalculateHandScore(sBlackJack->playerCardNumbers, sBlackJack->numPlayerCards);
    sBlackJack->dealerScore = CalculateHandScore(sBlackJack->dealerCardNumbers, sBlackJack->numDealerCards);
    sBlackJack->playerHasNatural = sBlackJack->playerScore == CARD_SCORE_BLACK_JACK;
    SetPlayerDigits(sBlackJack->playerScore);
    SetDealerDigits(sBlackJack->dealerScore);
}

static void InitBJScreen(void)
{
    SetVBlankCallback(NULL);
    ResetAllBgsCoordinates();
    ResetVramOamAndBgCntRegs();
    ResetBgsAndClearDma3BusyFlags(FALSE);
    ResetTempTileDataBuffers();

    InitBgsFromTemplates(0, sBJBgTemplates, ARRAY_COUNT(sBJBgTemplates));
    sBlackJack->bgTilemapBuffer = AllocZeroed(BG_SCREEN_SIZE);
    if (sBlackJack->bgTilemapBuffer == NULL)
    {
        FREE_AND_SET_NULL(sBlackJack);
        SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
        return;
    }
    SetBgTilemapBuffer(BJ_BG_BASE, sBlackJack->bgTilemapBuffer);
    DecompressAndLoadBgGfxUsingHeap(BJ_BG_BASE, sBJBackgroundGfx, 0xE00, 0, 0);
    CopyToBgTilemapBuffer(BJ_BG_BASE, sBJBackgroundTilemap, 0, 0);
    ResetPaletteFade();
    LoadPalette(sBJBackgroundPalette, 0, sizeof(sBJBackgroundPalette));

    ResetSpriteData();
    FreeAllSpritePalettes();
    LoadSpritePalettes(sSpritePalettes);
    CreatePlayerSprites();
    CreateDealerSprites();
    CreateCursorSprite();
    CreateOptions();
    CreatePopUpSprite();
    CreateFacedown();
    SetOptionMode(OPTION_NONE);

    ShuffleCards();
    DealInitialHand();

    DeactivateAllTextPrinters();
    InitWindows(sBJWinTemplates);
    sTextWindowId = 1;
    LoadPalette(GetTextWindowPalette(2), 11 * 16, 32);
    ShowHelpBar(sHelpBarHitStandText);
    ShowMessage(sText_ChooseAction);

    CopyBgTilemapBufferToVram(BJ_BG_BASE);
    CopyBgTilemapBufferToVram(BJ_WIN_MENU);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_MODE_0 | DISPCNT_OBJ_1D_MAP | DISPCNT_OBJ_ON | DISPCNT_BG2_ON);
    ShowBg(BJ_BG_BASE);
    ShowBg(BJ_WIN_MENU);
    BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
    SetVBlankCallback(BJVBlankCallback);
    SetMainCallback2(BJMainCallback);
    CreateTask(BJMain, 1);
}

static void SetResult(u8 result)
{
    const u8 *message;

    sBlackJack->result = result;
    gSpecialVar_Result = result;
    SetOptionMode(OPTION_NONE);
    ShowHelpBar(sHelpBarContinueText);

    switch (result)
    {
    case BLACKJACK_RESULT_WIN:
        message = sBlackJack->playerHasNatural ? sText_BlackJack : sText_YouWin;
        PlayFanfare(MUS_LEVEL_UP);
        break;
    case BLACKJACK_RESULT_DRAW:
        message = sText_Draw;
        PlaySE(SE_SELECT);
        break;
    default:
        message = sText_YouLose;
        PlaySE(SE_FAILURE);
        break;
    }

    ShowMessage(message);
    sBlackJack->delayTimer = ACTION_DELAY_FRAMES;
    sBlackJack->state = BJ_STATE_SHOW_RESULT;
}

static void DetermineResult(void)
{
    if (sBlackJack->dealerScore > CARD_SCORE_BLACK_JACK
     || sBlackJack->playerScore > sBlackJack->dealerScore)
        SetResult(BLACKJACK_RESULT_WIN);
    else if (sBlackJack->playerScore == sBlackJack->dealerScore)
        SetResult(BLACKJACK_RESULT_DRAW);
    else
        SetResult(BLACKJACK_RESULT_LOSS);
}

static void BeginDealerTurn(void)
{
    SetOptionMode(OPTION_NONE);
    sBlackJack->numDealerCards = 2;
    gSprites[sBlackJack->DealerFaceDownId].invisible = TRUE;
    UpdateCardVisibility();
    AdjustCards();
    sBlackJack->dealerScore = CalculateHandScore(sBlackJack->dealerCardNumbers, sBlackJack->numDealerCards);
    SetDealerDigits(sBlackJack->dealerScore);
    PlaySE(SE_REPEL);
    sBlackJack->delayTimer = ACTION_DELAY_FRAMES;
    sBlackJack->state = BJ_STATE_DEALER_REVEAL;
}

static void HitPlayer(void)
{
    if (sBlackJack->numPlayerCards >= MAX_PLAYER_CARDS)
    {
        BeginDealerTurn();
        return;
    }

    PlaySE(SE_CARD);
    sBlackJack->numPlayerCards++;
    UpdateCardVisibility();
    AdjustCards();
    sBlackJack->playerScore = CalculateHandScore(sBlackJack->playerCardNumbers, sBlackJack->numPlayerCards);
    SetPlayerDigits(sBlackJack->playerScore);

    if (sBlackJack->playerScore > CARD_SCORE_BLACK_JACK)
        SetResult(BLACKJACK_RESULT_LOSS);
    else if (sBlackJack->playerScore == CARD_SCORE_BLACK_JACK)
        BeginDealerTurn();
}

static void HandlePlayerInput(void)
{
    if (JOY_NEW(A_BUTTON))
    {
        if (gSprites[sBlackJack->cursorSpriteId].y == 57)
            HitPlayer();
        else
            BeginDealerTurn();
    }
    else if (JOY_NEW(B_BUTTON))
    {
        gSpecialVar_Result = BLACKJACK_RESULT_QUIT;
        sBlackJack->state = BJ_STATE_START_EXIT;
    }
    else if (JOY_NEW(DPAD_UP))
    {
        MoveCursor(-1);
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        MoveCursor(1);
    }
}

static void BJMain(u8 taskId)
{
    switch (sBlackJack->state)
    {
    case BJ_STATE_INIT:
        if (!gPaletteFade.active)
        {
            gSprites[sBlackJack->LogoId].invisible = TRUE;
            if (sBlackJack->playerHasNatural)
                BeginDealerTurn();
            else
            {
                SetOptionMode(OPTION_HIT_STAND);
                sBlackJack->state = BJ_STATE_PLAYER_TURN;
            }
        }
        break;
    case BJ_STATE_PLAYER_TURN:
        HandlePlayerInput();
        break;
    case BJ_STATE_DEALER_REVEAL:
        if (sBlackJack->delayTimer != 0)
        {
            sBlackJack->delayTimer--;
            break;
        }
        if (sBlackJack->playerHasNatural)
        {
            if (sBlackJack->dealerScore == CARD_SCORE_BLACK_JACK)
                SetResult(BLACKJACK_RESULT_DRAW);
            else
                SetResult(BLACKJACK_RESULT_WIN);
        }
        else if (sBlackJack->dealerScore == CARD_SCORE_BLACK_JACK)
        {
            SetResult(BLACKJACK_RESULT_LOSS);
        }
        else
        {
            sBlackJack->state = BJ_STATE_DEALER_DRAW;
        }
        break;
    case BJ_STATE_DEALER_DRAW:
        if (sBlackJack->delayTimer != 0)
        {
            sBlackJack->delayTimer--;
            break;
        }
        if (sBlackJack->dealerScore < 17 && sBlackJack->numDealerCards < MAX_DEALER_CARDS)
        {
            sBlackJack->numDealerCards++;
            UpdateCardVisibility();
            AdjustCards();
            sBlackJack->dealerScore = CalculateHandScore(sBlackJack->dealerCardNumbers, sBlackJack->numDealerCards);
            SetDealerDigits(sBlackJack->dealerScore);
            PlaySE(SE_REPEL);
            sBlackJack->delayTimer = ACTION_DELAY_FRAMES;
        }
        else
        {
            DetermineResult();
        }
        break;
    case BJ_STATE_SHOW_RESULT:
        if (sBlackJack->delayTimer != 0)
            sBlackJack->delayTimer--;
        else
            sBlackJack->state = BJ_STATE_WAIT_FOR_RESULT_INPUT;
        break;
    case BJ_STATE_WAIT_FOR_RESULT_INPUT:
        if ((sBlackJack->result != BLACKJACK_RESULT_WIN || IsFanfareTaskInactive())
         && JOY_NEW(A_BUTTON | B_BUTTON))
            sBlackJack->state = BJ_STATE_START_EXIT;
        break;
    case BJ_STATE_START_EXIT:
        StartExitBJ();
        break;
    case BJ_STATE_EXIT:
        if (!gPaletteFade.active)
        {
            DestroyTask(taskId);
            ExitBJ();
        }
        break;
    }
}

static void UpdateCardVisibility(void)
{
    u8 i;

    for (i = 0; i < MAX_PLAYER_CARDS; i++)
        gSprites[sBlackJack->playerCardIds[i]].invisible = i >= sBlackJack->numPlayerCards;

    for (i = 0; i < MAX_DEALER_CARDS; i++)
        gSprites[sBlackJack->dealerCardIds[i]].invisible = i >= sBlackJack->numDealerCards;
}

static void MoveCursor(s8 direction)
{
    s16 oldY = gSprites[sBlackJack->cursorSpriteId].y;
    s16 newY = oldY + direction * 16;

    if (newY < 57 || newY > 73)
    {
        PlaySE(SE_WALL_HIT);
        return;
    }

    gSprites[sBlackJack->cursorSpriteId].y = newY;
    PlaySE(SE_CLICK);
}

static void ShuffleCards(void)
{
    u8 allCardNumbers[CARD_COUNT];
    u8 i;

    for (i = 0; i < CARD_COUNT; i++)
        allCardNumbers[i] = i;

    for (i = CARD_COUNT - 1; i != 0; i--)
    {
        u8 j = Random() % (i + 1);
        u8 temp = allCardNumbers[i];

        allCardNumbers[i] = allCardNumbers[j];
        allCardNumbers[j] = temp;
    }

    for (i = 0; i < MAX_PLAYER_CARDS; i++)
        sBlackJack->playerCardNumbers[i] = allCardNumbers[i];

    for (i = 0; i < MAX_DEALER_CARDS; i++)
        sBlackJack->dealerCardNumbers[i] = allCardNumbers[MAX_PLAYER_CARDS + i];

    UpdateCards();
}

static void UpdateCards(void)
{
    u8 i;

    for (i = 0; i < MAX_PLAYER_CARDS; i++)
        SetCardSprite(sBlackJack->playerCardNumbers[i], i, TRUE);

    for (i = 0; i < MAX_DEALER_CARDS; i++)
        SetCardSprite(sBlackJack->dealerCardNumbers[i], i + MAX_PLAYER_CARDS, FALSE);
}

static void SetCardSprite(u8 cardNum, u8 cardIndex, bool8 isPlayerCard)
{
    u8 spriteId;

    LoadCompressedSpriteSheet(&sPlayingCards[cardNum].sheet);
    spriteId = CreateSprite(&sPlayingCards[cardNum].template,
                            cardPositions[cardIndex].x,
                            cardPositions[cardIndex].y,
                            cardPositions[cardIndex].priority);
    gSprites[spriteId].oam.priority = 1;
    gSprites[spriteId].invisible = TRUE;

    if (isPlayerCard)
        sBlackJack->playerCardIds[cardIndex] = spriteId;
    else
        sBlackJack->dealerCardIds[cardIndex - MAX_PLAYER_CARDS] = spriteId;
}

static void CreateFacedown(void)
{
    LoadCompressedSpriteSheet(&sSpriteSheet_Facedown);
    sBlackJack->DealerFaceDownId = CreateSprite(&sSpriteTemplate_Facedown, 48, 56, 0);
    gSprites[sBlackJack->DealerFaceDownId].oam.priority = 0;
    gSprites[sBlackJack->DealerFaceDownId].invisible = TRUE;
}

static void CreateCursorSprite(void)
{
    LoadCompressedSpriteSheet(&sSpriteSheet_Cursor);
    sBlackJack->cursorSpriteId = CreateSprite(&sSpriteTemplate_Cursor, 173, 57, 9);
    gSprites[sBlackJack->cursorSpriteId].oam.priority = 3;
}

static void CreatePopUpSprite(void)
{
    LoadCompressedSpriteSheet(&sSpriteSheet_Popup);
    sBlackJack->LogoId = CreateSprite(&sSpriteTemplate_Popup, 80, 72, 1);
    gSprites[sBlackJack->LogoId].oam.priority = 3;
}

static void CreateOptions(void)
{
    LoadCompressedSpriteSheet(&sSpriteSheet_Option1);
    sBlackJack->option1SpriteId = CreateSprite(&sSpriteTemplate_Option1, 219, 58, 9);
    gSprites[sBlackJack->option1SpriteId].oam.priority = 2;

    LoadCompressedSpriteSheet(&sSpriteSheet_Option2);
    sBlackJack->option2SpriteId = CreateSprite(&sSpriteTemplate_Option2, 219, 74, 9);
    gSprites[sBlackJack->option2SpriteId].oam.priority = 2;

}

static void AdjustCards(void)
{
    u8 i;

    if (sBlackJack->numPlayerCards > 5)
    {
        for (i = 1; i < MAX_PLAYER_CARDS; i++)
            gSprites[sBlackJack->playerCardIds[i]].x = 144 - i * 16;
    }
    else
    {
        for (i = 1; i < MAX_PLAYER_CARDS; i++)
            gSprites[sBlackJack->playerCardIds[i]].x = 144 - i * 32;
    }

    if (sBlackJack->numDealerCards > 5)
    {
        for (i = 1; i < MAX_DEALER_CARDS; i++)
            gSprites[sBlackJack->dealerCardIds[i]].x = 16 + i * 16;
    }
    else
    {
        for (i = 1; i < MAX_DEALER_CARDS; i++)
            gSprites[sBlackJack->dealerCardIds[i]].x = 16 + i * 32;
    }
}

static void BJVBlankCallback(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void ShowHelpBar(const u8 *str)
{
    const u8 color[3] = {TEXT_COLOR_TRANSPARENT, 1, 2};

    FillWindowPixelBuffer(0, PIXEL_FILL(0xF));
    AddTextPrinterParameterized3(0, FONT_NORMAL, GetStringRightAlignXOffset(FONT_NORMAL, str, DISPLAY_WIDTH) - 4,
                                 0, color, TEXT_SKIP_DRAW, str);
    PutWindowTilemap(0);
    CopyWindowToVram(0, COPYWIN_FULL);
}

static void StartExitBJ(void)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    sBlackJack->state = BJ_STATE_EXIT;
}

static void ExitBJ(void)
{
    SetVBlankCallback(NULL);
    FreeAllWindowBuffers();
    UnsetBgTilemapBuffer(BJ_BG_BASE);
    FREE_AND_SET_NULL(sBlackJack->bgTilemapBuffer);
    FREE_AND_SET_NULL(sBlackJack);
    SetMainCallback2(CB2_ReturnToFieldContinueScriptPlayMapMusic);
}
