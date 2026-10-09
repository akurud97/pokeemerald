# 1 "data/maps/Alasiaville/scripts.pory"

# 2 "data/maps/Alasiaville/scripts.pory"
.set LOCALID_APRIL, LOCALID_ALASIAVILLE_APRIL
# 3 "data/maps/Alasiaville/scripts.pory"

# 4 "data/maps/Alasiaville/scripts.pory"
Alasiaville_MapScripts::
# 5 "data/maps/Alasiaville/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Alasiaville_OnTransition
# 6 "data/maps/Alasiaville/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Alasiaville_OnFrame
# 7 "data/maps/Alasiaville/scripts.pory"
	.byte 0
# 8 "data/maps/Alasiaville/scripts.pory"

# 9 "data/maps/Alasiaville/scripts.pory"
Alasiaville_OnTransition:
# 10 "data/maps/Alasiaville/scripts.pory"
	call_if_eq VAR_ALASIA_INTRO_STATE, 9, Alasiaville_EventScript_PrepareAprilChapterOneFinale
# 11 "data/maps/Alasiaville/scripts.pory"
	end
# 12 "data/maps/Alasiaville/scripts.pory"

# 13 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_PrepareAprilChapterOneFinale:
# 14 "data/maps/Alasiaville/scripts.pory"
	setobjectxyperm LOCALID_APRIL, 20, 21
# 15 "data/maps/Alasiaville/scripts.pory"
	setobjectmovementtype LOCALID_APRIL, MOVEMENT_TYPE_FACE_RIGHT
# 16 "data/maps/Alasiaville/scripts.pory"
	clearflag FLAG_HIDE_ALASIAVILLE_APRIL
# 17 "data/maps/Alasiaville/scripts.pory"
	return
# 18 "data/maps/Alasiaville/scripts.pory"

# 19 "data/maps/Alasiaville/scripts.pory"
Alasiaville_OnFrame:
# 20 "data/maps/Alasiaville/scripts.pory"
	map_script_2 VAR_ALASIA_INTRO_STATE, 0, Alasiaville_EventScript_Intro
# 21 "data/maps/Alasiaville/scripts.pory"
	map_script_2 VAR_ALASIA_INTRO_STATE, 9, Alasiaville_EventScript_AprilChapterOneFinale
# 22 "data/maps/Alasiaville/scripts.pory"
	.2byte 0
# 23 "data/maps/Alasiaville/scripts.pory"

# 24 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_Intro::
# 25 "data/maps/Alasiaville/scripts.pory"
	lockall
# 26 "data/maps/Alasiaville/scripts.pory"
	setvar VAR_ALASIA_INTRO_STATE, 1
# 27 "data/maps/Alasiaville/scripts.pory"
	clearflag FLAG_SYS_POKEDEX_GET
# 28 "data/maps/Alasiaville/scripts.pory"
	clearflag FLAG_SYS_NATIONAL_DEX
# 29 "data/maps/Alasiaville/scripts.pory"
	clearflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
# 30 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_SchoolYearFlewBy, MSGBOX_DEFAULT
# 31 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_KidsGettingPokemon, MSGBOX_DEFAULT
# 32 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_WishForPokemon, MSGBOX_DEFAULT
# 33 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_AprilSaysGoodbye, MSGBOX_DEFAULT
# 34 "data/maps/Alasiaville/scripts.pory"
	closemessage
# 35 "data/maps/Alasiaville/scripts.pory"
	applymovement LOCALID_APRIL, Alasiaville_Movement_AprilApproachDoor
# 36 "data/maps/Alasiaville/scripts.pory"
	waitmovement 0
# 37 "data/maps/Alasiaville/scripts.pory"
	opendoor 11, 4
# 38 "data/maps/Alasiaville/scripts.pory"
	waitdooranim
# 39 "data/maps/Alasiaville/scripts.pory"
	applymovement LOCALID_APRIL, Alasiaville_Movement_AprilEnterDoor
# 40 "data/maps/Alasiaville/scripts.pory"
	waitmovement 0
# 41 "data/maps/Alasiaville/scripts.pory"
	setflag FLAG_HIDE_ALASIAVILLE_APRIL
# 42 "data/maps/Alasiaville/scripts.pory"
	removeobject LOCALID_APRIL
# 43 "data/maps/Alasiaville/scripts.pory"
	closedoor 11, 4
# 44 "data/maps/Alasiaville/scripts.pory"
	waitdooranim
# 45 "data/maps/Alasiaville/scripts.pory"
	setvar VAR_ALASIA_INTRO_STATE, 2
# 46 "data/maps/Alasiaville/scripts.pory"
	releaseall
# 47 "data/maps/Alasiaville/scripts.pory"
	end
# 48 "data/maps/Alasiaville/scripts.pory"

# 49 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_AprilChapterOneFinale::
# 50 "data/maps/Alasiaville/scripts.pory"
	lockall
# 51 "data/maps/Alasiaville/scripts.pory"
	applymovement LOCALID_APRIL, Alasiaville_Movement_AprilApproachPlayerAfterMom
# 52 "data/maps/Alasiaville/scripts.pory"
	waitmovement 0
# 53 "data/maps/Alasiaville/scripts.pory"
	special BufferAprilName
# 54 "data/maps/Alasiaville/scripts.pory"
	setspeaker Alasiaville_Text_AprilSpeakerName
# 55 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_DidYouTalkToYourMom, MSGBOX_DEFAULT
# 56 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_DadKeptHisCool, MSGBOX_DEFAULT
# 57 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_JoinMyAdventure, MSGBOX_DEFAULT
# 58 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_SummerWillBeAwesome, MSGBOX_DEFAULT
# 59 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_GetAHeadStart, MSGBOX_DEFAULT
# 60 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_GiveYouMap, MSGBOX_DEFAULT
# 61 "data/maps/Alasiaville/scripts.pory"
	setspeaker SP_NAME_NONE
# 62 "data/maps/Alasiaville/scripts.pory"
	giveitem ITEM_TOWN_MAP
# 63 "data/maps/Alasiaville/scripts.pory"
	special BufferAprilName
# 64 "data/maps/Alasiaville/scripts.pory"
	setspeaker Alasiaville_Text_AprilSpeakerName
# 65 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_RaceToPokemonLeague, MSGBOX_DEFAULT
# 66 "data/maps/Alasiaville/scripts.pory"
	closemessage
# 67 "data/maps/Alasiaville/scripts.pory"
	applymovement LOCALID_APRIL, Alasiaville_Movement_AprilLeaveAfterMap
# 68 "data/maps/Alasiaville/scripts.pory"
	waitmovement 0
# 69 "data/maps/Alasiaville/scripts.pory"
	setflag FLAG_HIDE_ALASIAVILLE_APRIL
# 70 "data/maps/Alasiaville/scripts.pory"
	removeobject LOCALID_APRIL
# 71 "data/maps/Alasiaville/scripts.pory"
	setvar VAR_ALASIA_INTRO_STATE, 10
# 72 "data/maps/Alasiaville/scripts.pory"
	releaseall
# 73 "data/maps/Alasiaville/scripts.pory"
	end
# 74 "data/maps/Alasiaville/scripts.pory"

# 75 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_VacationMan::
# 76 "data/maps/Alasiaville/scripts.pory"
	lock
# 77 "data/maps/Alasiaville/scripts.pory"
	faceplayer
# 78 "data/maps/Alasiaville/scripts.pory"
	setspeaker SP_NAME_NONE
# 79 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_VacationMan, MSGBOX_DEFAULT
# 80 "data/maps/Alasiaville/scripts.pory"
	release
# 81 "data/maps/Alasiaville/scripts.pory"
	end
# 82 "data/maps/Alasiaville/scripts.pory"

# 83 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_YoungStudent::
# 84 "data/maps/Alasiaville/scripts.pory"
	lock
# 85 "data/maps/Alasiaville/scripts.pory"
	faceplayer
# 86 "data/maps/Alasiaville/scripts.pory"
	setspeaker SP_NAME_NONE
# 87 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_YoungStudent, MSGBOX_DEFAULT
# 88 "data/maps/Alasiaville/scripts.pory"
	release
# 89 "data/maps/Alasiaville/scripts.pory"
	end
# 90 "data/maps/Alasiaville/scripts.pory"

# 91 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_TownSign::
# 92 "data/maps/Alasiaville/scripts.pory"
	setspeaker SP_NAME_NONE
# 93 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_TownSign, MSGBOX_SIGN
# 94 "data/maps/Alasiaville/scripts.pory"
	end
# 95 "data/maps/Alasiaville/scripts.pory"

# 96 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_PlayerHouseSign::
# 97 "data/maps/Alasiaville/scripts.pory"
	setspeaker SP_NAME_NONE
# 98 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_PlayerHouseSign, MSGBOX_SIGN
# 99 "data/maps/Alasiaville/scripts.pory"
	end
# 100 "data/maps/Alasiaville/scripts.pory"

# 101 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_BlockConnectionExit::
# 102 "data/maps/Alasiaville/scripts.pory"
	lockall
# 103 "data/maps/Alasiaville/scripts.pory"
	goto_if_eq VAR_ALASIA_INTRO_STATE, 8, Alasiaville_EventScript_BlockTellMomExit
# 104 "data/maps/Alasiaville/scripts.pory"
	goto_if_ge VAR_ALASIA_INTRO_STATE, 3, Alasiaville_EventScript_BlockPackageExit
# 105 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_ShouldTalkToMom, MSGBOX_DEFAULT
# 106 "data/maps/Alasiaville/scripts.pory"
	goto Alasiaville_EventScript_TurnPlayerAround
# 107 "data/maps/Alasiaville/scripts.pory"

# 108 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_BlockPackageExit::
# 109 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_ShouldReturnPackage, MSGBOX_DEFAULT
# 110 "data/maps/Alasiaville/scripts.pory"
	goto Alasiaville_EventScript_TurnPlayerAround
# 111 "data/maps/Alasiaville/scripts.pory"

# 112 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_BlockTellMomExit::
# 113 "data/maps/Alasiaville/scripts.pory"
	msgbox Alasiaville_Text_NeedToTellMom, MSGBOX_DEFAULT
# 114 "data/maps/Alasiaville/scripts.pory"

# 115 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_TurnPlayerAround::
# 116 "data/maps/Alasiaville/scripts.pory"
	goto_if_eq VAR_0x8000, DIR_NORTH, Alasiaville_EventScript_TurnPlayerSouth
# 117 "data/maps/Alasiaville/scripts.pory"
	goto_if_eq VAR_0x8000, DIR_SOUTH, Alasiaville_EventScript_TurnPlayerNorth
# 118 "data/maps/Alasiaville/scripts.pory"
	goto_if_eq VAR_0x8000, DIR_WEST, Alasiaville_EventScript_TurnPlayerEast
# 119 "data/maps/Alasiaville/scripts.pory"
	goto Alasiaville_EventScript_TurnPlayerWest
# 120 "data/maps/Alasiaville/scripts.pory"

# 121 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_TurnPlayerSouth::
# 122 "data/maps/Alasiaville/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
# 123 "data/maps/Alasiaville/scripts.pory"
	goto Alasiaville_EventScript_FinishBlockedExit
# 124 "data/maps/Alasiaville/scripts.pory"

# 125 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_TurnPlayerNorth::
# 126 "data/maps/Alasiaville/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterUp
# 127 "data/maps/Alasiaville/scripts.pory"
	goto Alasiaville_EventScript_FinishBlockedExit
# 128 "data/maps/Alasiaville/scripts.pory"

# 129 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_TurnPlayerEast::
# 130 "data/maps/Alasiaville/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
# 131 "data/maps/Alasiaville/scripts.pory"
	goto Alasiaville_EventScript_FinishBlockedExit
# 132 "data/maps/Alasiaville/scripts.pory"

# 133 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_TurnPlayerWest::
# 134 "data/maps/Alasiaville/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
# 135 "data/maps/Alasiaville/scripts.pory"

# 136 "data/maps/Alasiaville/scripts.pory"
Alasiaville_EventScript_FinishBlockedExit::
# 137 "data/maps/Alasiaville/scripts.pory"
	waitmovement 0
# 138 "data/maps/Alasiaville/scripts.pory"
	releaseall
# 139 "data/maps/Alasiaville/scripts.pory"
	end
# 140 "data/maps/Alasiaville/scripts.pory"

# 141 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Movement_AprilApproachDoor:
# 142 "data/maps/Alasiaville/scripts.pory"
	walk_up
# 143 "data/maps/Alasiaville/scripts.pory"
	walk_up
# 144 "data/maps/Alasiaville/scripts.pory"
	walk_up
# 145 "data/maps/Alasiaville/scripts.pory"
	step_end
# 146 "data/maps/Alasiaville/scripts.pory"

# 147 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Movement_AprilEnterDoor:
# 148 "data/maps/Alasiaville/scripts.pory"
	walk_up
# 149 "data/maps/Alasiaville/scripts.pory"
	set_invisible
# 150 "data/maps/Alasiaville/scripts.pory"
	step_end
# 151 "data/maps/Alasiaville/scripts.pory"

# 152 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Movement_AprilApproachPlayerAfterMom:
# 153 "data/maps/Alasiaville/scripts.pory"
	walk_right
# 154 "data/maps/Alasiaville/scripts.pory"
	walk_right
# 155 "data/maps/Alasiaville/scripts.pory"
	walk_right
# 156 "data/maps/Alasiaville/scripts.pory"
	walk_right
# 157 "data/maps/Alasiaville/scripts.pory"
	walk_right
# 158 "data/maps/Alasiaville/scripts.pory"
	walk_in_place_faster_up
# 159 "data/maps/Alasiaville/scripts.pory"
	step_end
# 160 "data/maps/Alasiaville/scripts.pory"

# 161 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Movement_AprilLeaveAfterMap:
# 162 "data/maps/Alasiaville/scripts.pory"
	walk_left
# 163 "data/maps/Alasiaville/scripts.pory"
	walk_left
# 164 "data/maps/Alasiaville/scripts.pory"
	walk_left
# 165 "data/maps/Alasiaville/scripts.pory"
	walk_left
# 166 "data/maps/Alasiaville/scripts.pory"
	walk_left
# 167 "data/maps/Alasiaville/scripts.pory"
	walk_left
# 168 "data/maps/Alasiaville/scripts.pory"
	walk_left
# 169 "data/maps/Alasiaville/scripts.pory"
	walk_left
# 170 "data/maps/Alasiaville/scripts.pory"
	walk_left
# 171 "data/maps/Alasiaville/scripts.pory"
	walk_left
# 172 "data/maps/Alasiaville/scripts.pory"
	set_invisible
# 173 "data/maps/Alasiaville/scripts.pory"
	step_end
# 174 "data/maps/Alasiaville/scripts.pory"

# 175 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_AprilSpeakerName:
# 176 "data/maps/Alasiaville/scripts.pory"
	.string "{STR_VAR_1}$"
# 177 "data/maps/Alasiaville/scripts.pory"

# 178 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_DidYouTalkToYourMom:
# 179 "data/maps/Alasiaville/scripts.pory"
	.string "{PLAYER}! Did you talk to your mom?$"
# 180 "data/maps/Alasiaville/scripts.pory"

# 181 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_DadKeptHisCool:
# 182 "data/maps/Alasiaville/scripts.pory"
	.string "My dad kept his cool, surprisingly.$"
# 183 "data/maps/Alasiaville/scripts.pory"

# 184 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_JoinMyAdventure:
# 185 "data/maps/Alasiaville/scripts.pory"
	.string "Listen, {PLAYER}. I want to go on\n"
# 186 "data/maps/Alasiaville/scripts.pory"
	.string "an adventure. I know you do too.\p"
# 187 "data/maps/Alasiaville/scripts.pory"
	.string "I’m going to take on the gym\n"
# 188 "data/maps/Alasiaville/scripts.pory"
	.string "challenge and see how far I can get!\p"
# 189 "data/maps/Alasiaville/scripts.pory"
	.string "Will you join me?$"
# 190 "data/maps/Alasiaville/scripts.pory"

# 191 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_SummerWillBeAwesome:
# 192 "data/maps/Alasiaville/scripts.pory"
	.string "You will? YEAH! I told you this\n"
# 193 "data/maps/Alasiaville/scripts.pory"
	.string "summer was going to be awesome!$"
# 194 "data/maps/Alasiaville/scripts.pory"

# 195 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_GetAHeadStart:
# 196 "data/maps/Alasiaville/scripts.pory"
	.string "Okay, I’m going to get a head start.$"
# 197 "data/maps/Alasiaville/scripts.pory"

# 198 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_GiveYouMap:
# 199 "data/maps/Alasiaville/scripts.pory"
	.string "Oh, first I wanted to give you this.\n"
# 200 "data/maps/Alasiaville/scripts.pory"
	.string "My dad gave me an extra.$"
# 201 "data/maps/Alasiaville/scripts.pory"

# 202 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_RaceToPokemonLeague:
# 203 "data/maps/Alasiaville/scripts.pory"
	.string "Alright, {PLAYER}. I’m going to race\n"
# 204 "data/maps/Alasiaville/scripts.pory"
	.string "you to the Pokémon League! See you!$"
# 205 "data/maps/Alasiaville/scripts.pory"

# 206 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_SchoolYearFlewBy:
# 207 "data/maps/Alasiaville/scripts.pory"
	.string "That school year flew by, huh?\n"
# 208 "data/maps/Alasiaville/scripts.pory"
	.string "Are you excited for summer,\l"
# 209 "data/maps/Alasiaville/scripts.pory"
	.string "{PLAYER}?$"
# 210 "data/maps/Alasiaville/scripts.pory"

# 211 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_KidsGettingPokemon:
# 212 "data/maps/Alasiaville/scripts.pory"
	.string "A lot of kids will be getting\n"
# 213 "data/maps/Alasiaville/scripts.pory"
	.string "Pokémon and won’t be back next\l"
# 214 "data/maps/Alasiaville/scripts.pory"
	.string "year…$"
# 215 "data/maps/Alasiaville/scripts.pory"

# 216 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_WishForPokemon:
# 217 "data/maps/Alasiaville/scripts.pory"
	.string "Sigh…I wish I could have my own\n"
# 218 "data/maps/Alasiaville/scripts.pory"
	.string "Pokémon.$"
# 219 "data/maps/Alasiaville/scripts.pory"

# 220 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_AprilSaysGoodbye:
# 221 "data/maps/Alasiaville/scripts.pory"
	.string "Alright, {PLAYER}! I’m going to say\n"
# 222 "data/maps/Alasiaville/scripts.pory"
	.string "hi to my dad. You should let your\l"
# 223 "data/maps/Alasiaville/scripts.pory"
	.string "mom know you’re home too.\p"
# 224 "data/maps/Alasiaville/scripts.pory"
	.string "I’ll see you later!$"
# 225 "data/maps/Alasiaville/scripts.pory"

# 226 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_ShouldTalkToMom:
# 227 "data/maps/Alasiaville/scripts.pory"
	.string "I should go talk to my mom before\n"
# 228 "data/maps/Alasiaville/scripts.pory"
	.string "going anywhere.$"
# 229 "data/maps/Alasiaville/scripts.pory"

# 230 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_ShouldReturnPackage:
# 231 "data/maps/Alasiaville/scripts.pory"
	.string "I need to return an item to my\n"
# 232 "data/maps/Alasiaville/scripts.pory"
	.string "uncle on Route 1. I shouldn't waste\l"
# 233 "data/maps/Alasiaville/scripts.pory"
	.string "too much time.$"
# 234 "data/maps/Alasiaville/scripts.pory"

# 235 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_NeedToTellMom:
# 236 "data/maps/Alasiaville/scripts.pory"
	.string "I need to tell my mom before I go\n"
# 237 "data/maps/Alasiaville/scripts.pory"
	.string "anywhere.$"
# 238 "data/maps/Alasiaville/scripts.pory"

# 239 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_VacationMan:
# 240 "data/maps/Alasiaville/scripts.pory"
	.string "Hmm? Oh, {PLAYER}, is it summer\n"
# 241 "data/maps/Alasiaville/scripts.pory"
	.string "break already?\p"
# 242 "data/maps/Alasiaville/scripts.pory"
	.string "Boy, I wish I had a vacation.$"
# 243 "data/maps/Alasiaville/scripts.pory"

# 244 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_YoungStudent:
# 245 "data/maps/Alasiaville/scripts.pory"
	.string "Next year I’m going to school just\n"
# 246 "data/maps/Alasiaville/scripts.pory"
	.string "like you, {PLAYER}!\p"
# 247 "data/maps/Alasiaville/scripts.pory"
	.string "I can’t wait to learn lots!$"
# 248 "data/maps/Alasiaville/scripts.pory"

# 249 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_TownSign:
# 250 "data/maps/Alasiaville/scripts.pory"
	.string "Alasiaville\n"
# 251 "data/maps/Alasiaville/scripts.pory"
	.string "Gateway to lake country.$"
# 252 "data/maps/Alasiaville/scripts.pory"

# 253 "data/maps/Alasiaville/scripts.pory"
Alasiaville_Text_PlayerHouseSign:
# 254 "data/maps/Alasiaville/scripts.pory"
	.string "{PLAYER}’s House$"
