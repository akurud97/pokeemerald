# 1 "data/maps/Route1/scripts.pory"

# 2 "data/maps/Route1/scripts.pory"
.set LOCALID_SITKA, LOCALID_ROUTE1_PROFESSOR_SITKA
# 3 "data/maps/Route1/scripts.pory"
.set LOCALID_APRIL, LOCALID_ROUTE1_APRIL
# 4 "data/maps/Route1/scripts.pory"

# 5 "data/maps/Route1/scripts.pory"
Route1_MapScripts::
# 6 "data/maps/Route1/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route1_OnTransition
# 7 "data/maps/Route1/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route1_OnFrame
# 8 "data/maps/Route1/scripts.pory"
	.byte 0
# 9 "data/maps/Route1/scripts.pory"

# 10 "data/maps/Route1/scripts.pory"
Route1_OnTransition:
# 11 "data/maps/Route1/scripts.pory"
	call_if_eq VAR_ALASIA_INTRO_STATE, 3, Route1_EventScript_HideStoryActors
# 12 "data/maps/Route1/scripts.pory"
	end
# 13 "data/maps/Route1/scripts.pory"

# 14 "data/maps/Route1/scripts.pory"
Route1_EventScript_HideStoryActors:
# 15 "data/maps/Route1/scripts.pory"
	setflag FLAG_HIDE_ROUTE1_PROFESSOR_SITKA
# 16 "data/maps/Route1/scripts.pory"
	setflag FLAG_HIDE_ROUTE1_APRIL
# 17 "data/maps/Route1/scripts.pory"
	return
# 18 "data/maps/Route1/scripts.pory"

# 19 "data/maps/Route1/scripts.pory"
Route1_OnFrame:
# 20 "data/maps/Route1/scripts.pory"
	map_script_2 VAR_ALASIA_INTRO_STATE, 6, Route1_EventScript_FirstAprilBattle
# 21 "data/maps/Route1/scripts.pory"
	.2byte 0
# 22 "data/maps/Route1/scripts.pory"

# 23 "data/maps/Route1/scripts.pory"
Route1_EventScript_FirstAprilBattle::
# 24 "data/maps/Route1/scripts.pory"
	lockall
# 25 "data/maps/Route1/scripts.pory"
	setvar VAR_ALASIA_INTRO_STATE, 7
# 26 "data/maps/Route1/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkLeft
# 27 "data/maps/Route1/scripts.pory"
	waitmovement 0
# 28 "data/maps/Route1/scripts.pory"
	setobjectxyperm LOCALID_APRIL, 19, 15
# 29 "data/maps/Route1/scripts.pory"
	clearflag FLAG_HIDE_ROUTE1_APRIL
# 30 "data/maps/Route1/scripts.pory"
	addobject LOCALID_APRIL
# 31 "data/maps/Route1/scripts.pory"
	opendoor 19, 15
# 32 "data/maps/Route1/scripts.pory"
	waitdooranim
# 33 "data/maps/Route1/scripts.pory"
	applymovement LOCALID_APRIL, Route1_Movement_AprilExitLabForBattle
# 34 "data/maps/Route1/scripts.pory"
	waitmovement 0
# 35 "data/maps/Route1/scripts.pory"
	closedoor 19, 15
# 36 "data/maps/Route1/scripts.pory"
	waitdooranim
# 37 "data/maps/Route1/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
# 38 "data/maps/Route1/scripts.pory"
	waitmovement 0
# 39 "data/maps/Route1/scripts.pory"
	special BufferAprilName
# 40 "data/maps/Route1/scripts.pory"
	setspeaker Route1_Text_AprilSpeakerName
# 41 "data/maps/Route1/scripts.pory"
	msgbox Route1_Text_AprilChallengesPlayer, MSGBOX_DEFAULT
# 42 "data/maps/Route1/scripts.pory"
	setflag FLAG_SPECIAL_NO_WHITEOUT
# 43 "data/maps/Route1/scripts.pory"
	goto_if_eq VAR_APRIL_STARTER, SPECIES_SPHEAL, Route1_EventScript_BattleAprilSpheal
# 44 "data/maps/Route1/scripts.pory"
	goto_if_eq VAR_APRIL_STARTER, SPECIES_SANDILE, Route1_EventScript_BattleAprilSandile
# 45 "data/maps/Route1/scripts.pory"

# 46 "data/maps/Route1/scripts.pory"
Route1_EventScript_BattleAprilMareep::
# 47 "data/maps/Route1/scripts.pory"
	trainerbattle_no_intro TRAINER_APRIL_MAREEP, Route1_Text_AprilDefeated
# 48 "data/maps/Route1/scripts.pory"
	goto Route1_EventScript_AfterAprilBattle
# 49 "data/maps/Route1/scripts.pory"

# 50 "data/maps/Route1/scripts.pory"
Route1_EventScript_BattleAprilSpheal::
# 51 "data/maps/Route1/scripts.pory"
	trainerbattle_no_intro TRAINER_APRIL_SPHEAL, Route1_Text_AprilDefeated
# 52 "data/maps/Route1/scripts.pory"
	goto Route1_EventScript_AfterAprilBattle
# 53 "data/maps/Route1/scripts.pory"

# 54 "data/maps/Route1/scripts.pory"
Route1_EventScript_BattleAprilSandile::
# 55 "data/maps/Route1/scripts.pory"
	trainerbattle_no_intro TRAINER_APRIL_SANDILE, Route1_Text_AprilDefeated
# 56 "data/maps/Route1/scripts.pory"

# 57 "data/maps/Route1/scripts.pory"
Route1_EventScript_AfterAprilBattle::
# 58 "data/maps/Route1/scripts.pory"
	clearflag FLAG_SPECIAL_NO_WHITEOUT
# 59 "data/maps/Route1/scripts.pory"
	specialvar VAR_RESULT, GetBattleOutcome
# 60 "data/maps/Route1/scripts.pory"
	goto_if_eq VAR_RESULT, B_OUTCOME_LOST, Route1_EventScript_AprilWonBattle
# 61 "data/maps/Route1/scripts.pory"
	special HealPlayerParty
# 62 "data/maps/Route1/scripts.pory"
	special BufferAprilName
# 63 "data/maps/Route1/scripts.pory"
	setspeaker Route1_Text_AprilSpeakerName
# 64 "data/maps/Route1/scripts.pory"
	msgbox Route1_Text_AprilAfterPlayerWins, MSGBOX_DEFAULT
# 65 "data/maps/Route1/scripts.pory"
	goto Route1_EventScript_AprilLeavesAfterBattle
# 66 "data/maps/Route1/scripts.pory"

# 67 "data/maps/Route1/scripts.pory"
Route1_EventScript_AprilWonBattle::
# 68 "data/maps/Route1/scripts.pory"
	special HealPlayerParty
# 69 "data/maps/Route1/scripts.pory"
	special BufferAprilName
# 70 "data/maps/Route1/scripts.pory"
	setspeaker Route1_Text_AprilSpeakerName
# 71 "data/maps/Route1/scripts.pory"
	msgbox Route1_Text_AprilAfterPlayerLoses, MSGBOX_DEFAULT
# 72 "data/maps/Route1/scripts.pory"

# 73 "data/maps/Route1/scripts.pory"
Route1_EventScript_AprilLeavesAfterBattle::
# 74 "data/maps/Route1/scripts.pory"
	applymovement LOCALID_APRIL, Route1_Movement_AprilLeaveAfterBattle
# 75 "data/maps/Route1/scripts.pory"
	waitmovement 0
# 76 "data/maps/Route1/scripts.pory"
	setflag FLAG_HIDE_SITKA_LAB_APRIL
# 77 "data/maps/Route1/scripts.pory"
	setflag FLAG_HIDE_ROUTE1_APRIL
# 78 "data/maps/Route1/scripts.pory"
	setflag FLAG_HIDE_APRIL_HOUSE2F_APRIL
# 79 "data/maps/Route1/scripts.pory"
	removeobject LOCALID_APRIL
# 80 "data/maps/Route1/scripts.pory"
	releaseall
# 81 "data/maps/Route1/scripts.pory"
	end
# 82 "data/maps/Route1/scripts.pory"

# 83 "data/maps/Route1/scripts.pory"
Route1_EventScript_LabDoorLocked::
# 84 "data/maps/Route1/scripts.pory"
	lockall
# 85 "data/maps/Route1/scripts.pory"
	msgbox Route1_Text_DoorLocked, MSGBOX_DEFAULT
# 86 "data/maps/Route1/scripts.pory"
	releaseall
# 87 "data/maps/Route1/scripts.pory"
	end
# 88 "data/maps/Route1/scripts.pory"

# 89 "data/maps/Route1/scripts.pory"
Route1_EventScript_SitkaLabSign::
# 90 "data/maps/Route1/scripts.pory"
	setspeaker SP_NAME_NONE
# 91 "data/maps/Route1/scripts.pory"
	msgbox Route1_Text_SitkaLabSign, MSGBOX_SIGN
# 92 "data/maps/Route1/scripts.pory"
	end
# 93 "data/maps/Route1/scripts.pory"

# 94 "data/maps/Route1/scripts.pory"
Route1_EventScript_GrassWarning::
# 95 "data/maps/Route1/scripts.pory"
	lockall
# 96 "data/maps/Route1/scripts.pory"
	setvar VAR_ALASIA_INTRO_STATE, 4
# 97 "data/maps/Route1/scripts.pory"
	opendoor 19, 15
# 98 "data/maps/Route1/scripts.pory"
	waitdooranim
# 99 "data/maps/Route1/scripts.pory"
	clearflag FLAG_HIDE_ROUTE1_PROFESSOR_SITKA
# 100 "data/maps/Route1/scripts.pory"
	addobject LOCALID_SITKA
# 101 "data/maps/Route1/scripts.pory"
	applymovement LOCALID_SITKA, Route1_Movement_SitkaExitLab
# 102 "data/maps/Route1/scripts.pory"
	waitmovement 0
# 103 "data/maps/Route1/scripts.pory"
	closedoor 19, 15
# 104 "data/maps/Route1/scripts.pory"
	waitdooranim
# 105 "data/maps/Route1/scripts.pory"
	setspeaker SP_NAME_PROFESSOR_SITKA
# 106 "data/maps/Route1/scripts.pory"
	msgbox Route1_Text_Wait, MSGBOX_DEFAULT
# 107 "data/maps/Route1/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
# 108 "data/maps/Route1/scripts.pory"
	waitmovement 0
# 109 "data/maps/Route1/scripts.pory"
	msgbox Route1_Text_GrassOvergrown, MSGBOX_DEFAULT
# 110 "data/maps/Route1/scripts.pory"
	msgbox Route1_Text_DangerousWithoutPokemon, MSGBOX_DEFAULT
# 111 "data/maps/Route1/scripts.pory"
	msgbox Route1_Text_MaintainPath, MSGBOX_DEFAULT
# 112 "data/maps/Route1/scripts.pory"
	msgbox Route1_Text_OutOfSchool, MSGBOX_DEFAULT
# 113 "data/maps/Route1/scripts.pory"
	msgbox Route1_Text_ComeIntoLab, MSGBOX_DEFAULT
# 114 "data/maps/Route1/scripts.pory"
	goto_if_eq VAR_0x8000, 1, Route1_EventScript_ApproachSitkaFromCenter
# 115 "data/maps/Route1/scripts.pory"
	goto_if_eq VAR_0x8000, 2, Route1_EventScript_ApproachSitkaFromEast
# 116 "data/maps/Route1/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Route1_Movement_PlayerApproachFromSouthwest
# 117 "data/maps/Route1/scripts.pory"
	goto Route1_EventScript_PlayerBesideSitka
# 118 "data/maps/Route1/scripts.pory"

# 119 "data/maps/Route1/scripts.pory"
Route1_EventScript_ApproachSitkaFromCenter::
# 120 "data/maps/Route1/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Route1_Movement_PlayerApproachFromCenter
# 121 "data/maps/Route1/scripts.pory"
	goto Route1_EventScript_PlayerBesideSitka
# 122 "data/maps/Route1/scripts.pory"

# 123 "data/maps/Route1/scripts.pory"
Route1_EventScript_ApproachSitkaFromEast::
# 124 "data/maps/Route1/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Route1_Movement_PlayerApproachFromEast
# 125 "data/maps/Route1/scripts.pory"

# 126 "data/maps/Route1/scripts.pory"
Route1_EventScript_PlayerBesideSitka::
# 127 "data/maps/Route1/scripts.pory"
	waitmovement 0
# 128 "data/maps/Route1/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkUp
# 129 "data/maps/Route1/scripts.pory"
	applymovement LOCALID_SITKA, Common_Movement_WalkUp
# 130 "data/maps/Route1/scripts.pory"
	waitmovement 0
# 131 "data/maps/Route1/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterRight
# 132 "data/maps/Route1/scripts.pory"
	waitmovement 0
# 133 "data/maps/Route1/scripts.pory"
	clearflag FLAG_HIDE_ROUTE1_APRIL
# 134 "data/maps/Route1/scripts.pory"
	addobject LOCALID_APRIL
# 135 "data/maps/Route1/scripts.pory"
	applymovement LOCALID_APRIL, Route1_Movement_AprilApproach
# 136 "data/maps/Route1/scripts.pory"
	waitmovement 0
# 137 "data/maps/Route1/scripts.pory"
	special BufferAprilName
# 138 "data/maps/Route1/scripts.pory"
	setspeaker Route1_Text_AprilSpeakerName
# 139 "data/maps/Route1/scripts.pory"
	msgbox Route1_Text_AprilCallsPlayer, MSGBOX_DEFAULT
# 140 "data/maps/Route1/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterDown
# 141 "data/maps/Route1/scripts.pory"
	applymovement LOCALID_SITKA, Common_Movement_WalkInPlaceFasterDown
# 142 "data/maps/Route1/scripts.pory"
	waitmovement 0
# 143 "data/maps/Route1/scripts.pory"
	msgbox Route1_Text_AprilCookies, MSGBOX_DEFAULT
# 144 "data/maps/Route1/scripts.pory"
	msgbox Route1_Text_AprilCottageGreeting, MSGBOX_DEFAULT
# 145 "data/maps/Route1/scripts.pory"
	special BufferAprilName
# 146 "data/maps/Route1/scripts.pory"
	setspeaker SP_NAME_PROFESSOR_SITKA
# 147 "data/maps/Route1/scripts.pory"
	msgbox Route1_Text_SitkaInvitesApril, MSGBOX_DEFAULT
# 148 "data/maps/Route1/scripts.pory"
	opendoor 19, 15
# 149 "data/maps/Route1/scripts.pory"
	waitdooranim
# 150 "data/maps/Route1/scripts.pory"
	applymovement LOCALID_SITKA, Route1_Movement_SitkaEnterLab
# 151 "data/maps/Route1/scripts.pory"
	waitmovement 0
# 152 "data/maps/Route1/scripts.pory"
	setflag FLAG_HIDE_ROUTE1_PROFESSOR_SITKA
# 153 "data/maps/Route1/scripts.pory"
	removeobject LOCALID_SITKA
# 154 "data/maps/Route1/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Route1_Movement_PlayerEnterLab
# 155 "data/maps/Route1/scripts.pory"
	waitmovement 0
# 156 "data/maps/Route1/scripts.pory"
	setflag FLAG_HIDE_ROUTE1_APRIL
# 157 "data/maps/Route1/scripts.pory"
	removeobject LOCALID_APRIL
# 158 "data/maps/Route1/scripts.pory"
	closedoor 19, 15
# 159 "data/maps/Route1/scripts.pory"
	waitdooranim
# 160 "data/maps/Route1/scripts.pory"
	warp MAP_SITKA_LAB, 5, 10
# 161 "data/maps/Route1/scripts.pory"
	waitstate
# 162 "data/maps/Route1/scripts.pory"
	end
# 163 "data/maps/Route1/scripts.pory"

# 164 "data/maps/Route1/scripts.pory"
Route1_Movement_SitkaExitLab:
# 165 "data/maps/Route1/scripts.pory"
	walk_down
# 166 "data/maps/Route1/scripts.pory"
	walk_down
# 167 "data/maps/Route1/scripts.pory"
	face_left
# 168 "data/maps/Route1/scripts.pory"
	step_end
# 169 "data/maps/Route1/scripts.pory"

# 170 "data/maps/Route1/scripts.pory"
Route1_Movement_PlayerApproachFromSouthwest:
# 171 "data/maps/Route1/scripts.pory"
	walk_up
# 172 "data/maps/Route1/scripts.pory"
	walk_up
# 173 "data/maps/Route1/scripts.pory"
	walk_right
# 174 "data/maps/Route1/scripts.pory"
	walk_right
# 175 "data/maps/Route1/scripts.pory"
	walk_right
# 176 "data/maps/Route1/scripts.pory"
	walk_right
# 177 "data/maps/Route1/scripts.pory"
	walk_right
# 178 "data/maps/Route1/scripts.pory"
	walk_right
# 179 "data/maps/Route1/scripts.pory"
	step_end
# 180 "data/maps/Route1/scripts.pory"

# 181 "data/maps/Route1/scripts.pory"
Route1_Movement_PlayerApproachFromCenter:
# 182 "data/maps/Route1/scripts.pory"
	walk_up
# 183 "data/maps/Route1/scripts.pory"
	walk_right
# 184 "data/maps/Route1/scripts.pory"
	walk_right
# 185 "data/maps/Route1/scripts.pory"
	walk_right
# 186 "data/maps/Route1/scripts.pory"
	walk_right
# 187 "data/maps/Route1/scripts.pory"
	walk_right
# 188 "data/maps/Route1/scripts.pory"
	step_end
# 189 "data/maps/Route1/scripts.pory"

# 190 "data/maps/Route1/scripts.pory"
Route1_Movement_PlayerApproachFromEast:
# 191 "data/maps/Route1/scripts.pory"
	walk_right
# 192 "data/maps/Route1/scripts.pory"
	walk_right
# 193 "data/maps/Route1/scripts.pory"
	walk_right
# 194 "data/maps/Route1/scripts.pory"
	walk_right
# 195 "data/maps/Route1/scripts.pory"
	step_end
# 196 "data/maps/Route1/scripts.pory"

# 197 "data/maps/Route1/scripts.pory"
Route1_Movement_AprilApproach:
# 198 "data/maps/Route1/scripts.pory"
	walk_up
# 199 "data/maps/Route1/scripts.pory"
	walk_up
# 200 "data/maps/Route1/scripts.pory"
	walk_up
# 201 "data/maps/Route1/scripts.pory"
	walk_up
# 202 "data/maps/Route1/scripts.pory"
	face_up
# 203 "data/maps/Route1/scripts.pory"
	step_end
# 204 "data/maps/Route1/scripts.pory"

# 205 "data/maps/Route1/scripts.pory"
Route1_Movement_AprilExitLabForBattle:
# 206 "data/maps/Route1/scripts.pory"
	walk_down
# 207 "data/maps/Route1/scripts.pory"
	face_left
# 208 "data/maps/Route1/scripts.pory"
	step_end
# 209 "data/maps/Route1/scripts.pory"

# 210 "data/maps/Route1/scripts.pory"
Route1_Movement_AprilLeaveAfterBattle:
# 211 "data/maps/Route1/scripts.pory"
	walk_down
# 212 "data/maps/Route1/scripts.pory"
	walk_down
# 213 "data/maps/Route1/scripts.pory"
	walk_down
# 214 "data/maps/Route1/scripts.pory"
	walk_down
# 215 "data/maps/Route1/scripts.pory"
	walk_down
# 216 "data/maps/Route1/scripts.pory"
	walk_down
# 217 "data/maps/Route1/scripts.pory"
	set_invisible
# 218 "data/maps/Route1/scripts.pory"
	step_end
# 219 "data/maps/Route1/scripts.pory"

# 220 "data/maps/Route1/scripts.pory"
Route1_Movement_SitkaEnterLab:
# 221 "data/maps/Route1/scripts.pory"
	walk_up
# 222 "data/maps/Route1/scripts.pory"
	set_invisible
# 223 "data/maps/Route1/scripts.pory"
	step_end
# 224 "data/maps/Route1/scripts.pory"

# 225 "data/maps/Route1/scripts.pory"
Route1_Movement_PlayerEnterLab:
# 226 "data/maps/Route1/scripts.pory"
	walk_right
# 227 "data/maps/Route1/scripts.pory"
	walk_up
# 228 "data/maps/Route1/scripts.pory"
	set_invisible
# 229 "data/maps/Route1/scripts.pory"
	step_end
# 230 "data/maps/Route1/scripts.pory"

# 231 "data/maps/Route1/scripts.pory"
Route1_Text_DoorLocked:
# 232 "data/maps/Route1/scripts.pory"
	.string "The door is locked.$"
# 233 "data/maps/Route1/scripts.pory"

# 234 "data/maps/Route1/scripts.pory"
Route1_Text_SitkaLabSign:
# 235 "data/maps/Route1/scripts.pory"
	.string "Professor Sitka’s Lab$"
# 236 "data/maps/Route1/scripts.pory"

# 237 "data/maps/Route1/scripts.pory"
Route1_Text_AprilSpeakerName:
# 238 "data/maps/Route1/scripts.pory"
	.string "{STR_VAR_1}$"
# 239 "data/maps/Route1/scripts.pory"

# 240 "data/maps/Route1/scripts.pory"
Route1_Text_AprilChallengesPlayer:
# 241 "data/maps/Route1/scripts.pory"
	.string "{PLAYER}, wait! We have to have a\n"
# 242 "data/maps/Route1/scripts.pory"
	.string "Pokémon battle!\p"
# 243 "data/maps/Route1/scripts.pory"
	.string "Ohh, I never thought I’d say that!\p"
# 244 "data/maps/Route1/scripts.pory"
	.string "Come on, let’s do this!$"
# 245 "data/maps/Route1/scripts.pory"

# 246 "data/maps/Route1/scripts.pory"
Route1_Text_AprilDefeated:
# 247 "data/maps/Route1/scripts.pory"
	.string "Wow, you’re a natural!$"
# 248 "data/maps/Route1/scripts.pory"

# 249 "data/maps/Route1/scripts.pory"
Route1_Text_AprilVictory:
# 250 "data/maps/Route1/scripts.pory"
	.string "Haha! I kicked your butt!$"
# 251 "data/maps/Route1/scripts.pory"

# 252 "data/maps/Route1/scripts.pory"
Route1_Text_AprilAfterPlayerWins:
# 253 "data/maps/Route1/scripts.pory"
	.string "That was awesome!\p"
# 254 "data/maps/Route1/scripts.pory"
	.string "Listen, I know you need to go see\n"
# 255 "data/maps/Route1/scripts.pory"
	.string "your uncle, but I need to go tell my\l"
# 256 "data/maps/Route1/scripts.pory"
	.string "dad about this…\p"
# 257 "data/maps/Route1/scripts.pory"
	.string "He’s not going to be happy, but he\n"
# 258 "data/maps/Route1/scripts.pory"
	.string "should find out from me.\p"
# 259 "data/maps/Route1/scripts.pory"
	.string "I’ll see you later!$"
# 260 "data/maps/Route1/scripts.pory"

# 261 "data/maps/Route1/scripts.pory"
Route1_Text_AprilAfterPlayerLoses:
# 262 "data/maps/Route1/scripts.pory"
	.string "Haha! I kicked your butt!\p"
# 263 "data/maps/Route1/scripts.pory"
	.string "That was awesome!\p"
# 264 "data/maps/Route1/scripts.pory"
	.string "Listen, I know you need to go see\n"
# 265 "data/maps/Route1/scripts.pory"
	.string "your uncle, but I need to go tell my\l"
# 266 "data/maps/Route1/scripts.pory"
	.string "dad about this…\p"
# 267 "data/maps/Route1/scripts.pory"
	.string "He’s not going to be happy, but he\n"
# 268 "data/maps/Route1/scripts.pory"
	.string "should find out from me.\p"
# 269 "data/maps/Route1/scripts.pory"
	.string "I’ll see you later!$"
# 270 "data/maps/Route1/scripts.pory"

# 271 "data/maps/Route1/scripts.pory"
Route1_Text_Wait:
# 272 "data/maps/Route1/scripts.pory"
	.string "Wait!$"
# 273 "data/maps/Route1/scripts.pory"

# 274 "data/maps/Route1/scripts.pory"
Route1_Text_GrassOvergrown:
# 275 "data/maps/Route1/scripts.pory"
	.string "That grass is overgrown and there\n"
# 276 "data/maps/Route1/scripts.pory"
	.string "may be Pokémon lurking in it.$"
# 277 "data/maps/Route1/scripts.pory"

# 278 "data/maps/Route1/scripts.pory"
Route1_Text_DangerousWithoutPokemon:
# 279 "data/maps/Route1/scripts.pory"
	.string "It’s dangerous without a Pokémon\n"
# 280 "data/maps/Route1/scripts.pory"
	.string "of your own.$"
# 281 "data/maps/Route1/scripts.pory"

# 282 "data/maps/Route1/scripts.pory"
Route1_Text_MaintainPath:
# 283 "data/maps/Route1/scripts.pory"
	.string "I really should maintain this path\n"
# 284 "data/maps/Route1/scripts.pory"
	.string "better. I’m just so caught up in my\l"
# 285 "data/maps/Route1/scripts.pory"
	.string "studies.$"
# 286 "data/maps/Route1/scripts.pory"

# 287 "data/maps/Route1/scripts.pory"
Route1_Text_OutOfSchool:
# 288 "data/maps/Route1/scripts.pory"
	.string "Hey, you’re {PLAYER}, right? Are you\n"
# 289 "data/maps/Route1/scripts.pory"
	.string "out of school for the summer?$"
# 290 "data/maps/Route1/scripts.pory"

# 291 "data/maps/Route1/scripts.pory"
Route1_Text_ComeIntoLab:
# 292 "data/maps/Route1/scripts.pory"
	.string "Hmm…I really shouldn’t do this\n"
# 293 "data/maps/Route1/scripts.pory"
	.string "without consulting your mother…but\l"
# 294 "data/maps/Route1/scripts.pory"
	.string "you’re old enough now. I have an\l"
# 295 "data/maps/Route1/scripts.pory"
	.string "idea. Come into my lab with me.$"
# 296 "data/maps/Route1/scripts.pory"

# 297 "data/maps/Route1/scripts.pory"
Route1_Text_AprilCallsPlayer:
# 298 "data/maps/Route1/scripts.pory"
	.string "{PLAYER}!$"
# 299 "data/maps/Route1/scripts.pory"

# 300 "data/maps/Route1/scripts.pory"
Route1_Text_AprilCookies:
# 301 "data/maps/Route1/scripts.pory"
	.string "Your mom told me you were coming\n"
# 302 "data/maps/Route1/scripts.pory"
	.string "this way! Her cookies were\l"
# 303 "data/maps/Route1/scripts.pory"
	.string "delicious.$"
# 304 "data/maps/Route1/scripts.pory"

# 305 "data/maps/Route1/scripts.pory"
Route1_Text_AprilCottageGreeting:
# 306 "data/maps/Route1/scripts.pory"
	.string "I wanted to come see your uncle’s\n"
# 307 "data/maps/Route1/scripts.pory"
	.string "cottage… Oh, hi, Professor Sitka!$"
# 308 "data/maps/Route1/scripts.pory"

# 309 "data/maps/Route1/scripts.pory"
Route1_Text_SitkaInvitesApril:
# 310 "data/maps/Route1/scripts.pory"
	.string "You’re {PLAYER}’s friend,\n"
# 311 "data/maps/Route1/scripts.pory"
	.string "{STR_VAR_1}, right? I was just\l"
# 312 "data/maps/Route1/scripts.pory"
	.string "showing {PLAYER} something in my\l"
# 313 "data/maps/Route1/scripts.pory"
	.string "lab. Why don’t you join us?$"
# 314 "data/maps/Route1/scripts.pory"

# 315 "data/maps/Route1/scripts.pory"
Route1_EventScript_Landon::
# 316 "data/maps/Route1/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_LANDON, Landon_Intro, Landon_Defeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Landon_Victory, NULL, FALSE, TRUE, FALSE, FALSE
# 317 "data/maps/Route1/scripts.pory"
	msgbox PostBattle_Landon, MSGBOX_AUTOCLOSE
# 318 "data/maps/Route1/scripts.pory"
	end
# 319 "data/maps/Route1/scripts.pory"

# 320 "data/maps/Route1/scripts.pory"
Route1_EventScript_Evelyn::
# 321 "data/maps/Route1/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_EVELYN, Evelyn_Intro, Evelyn_Defeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Evelyn_Victory, NULL, FALSE, TRUE, FALSE, FALSE
# 322 "data/maps/Route1/scripts.pory"
	msgbox PostBattle_Evelyn, MSGBOX_AUTOCLOSE
# 323 "data/maps/Route1/scripts.pory"
	end

Landon_Intro::
# 326 "data/maps/Route1/scripts.pory"
	.string "Hey, {PLAYER}! You got a Pokémon\n"
	.string "too? Let’s battle!$"

Landon_Defeat::
# 331 "data/maps/Route1/scripts.pory"
	.string "Drat… You’re that strong already?$"

Landon_Victory::
# 332 "data/maps/Route1/scripts.pory"
	.string "You’re gonna have to do better than that!$"

PostBattle_Landon::
# 333 "data/maps/Route1/scripts.pory"
	.string "So, what are you going to do over\nsummer vacation?$"

Evelyn_Intro::
# 335 "data/maps/Route1/scripts.pory"
	.string "Hey, weren’t you in my class? Let’s\n"
	.string "test what we learned!$"

Evelyn_Defeat::
# 340 "data/maps/Route1/scripts.pory"
	.string "I guess I should have studied more…$"

Evelyn_Victory::
# 341 "data/maps/Route1/scripts.pory"
	.string "Ha! My top marks weren’t for nothing.$"

PostBattle_Evelyn::
# 342 "data/maps/Route1/scripts.pory"
	.string "My parents are making me go back to\n"
	.string "school next year, but I just want to\l"
	.string "travel with my Pokémon.$"
