# 1 "data/maps/Route110/scripts.pory"

# 2 "data/maps/Route110/scripts.pory"
.set LOCALID_RIVAL, 28
# 3 "data/maps/Route110/scripts.pory"
.set LOCALID_RIVAL_ON_BIKE, 29
# 4 "data/maps/Route110/scripts.pory"
.set LOCALID_BIRCH, 36
# 5 "data/maps/Route110/scripts.pory"

# 6 "data/maps/Route110/scripts.pory"
Route110_MapScripts::
# 7 "data/maps/Route110/scripts.pory"
	map_script MAP_SCRIPT_ON_RESUME, Route110_OnResume
# 8 "data/maps/Route110/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, Route110_OnTransition
# 9 "data/maps/Route110/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, Route110_OnFrame
# 10 "data/maps/Route110/scripts.pory"
	.byte 0
# 11 "data/maps/Route110/scripts.pory"

# 12 "data/maps/Route110/scripts.pory"
Route110_OnResume:
# 13 "data/maps/Route110/scripts.pory"
	special UpdateCyclingRoadState
# 14 "data/maps/Route110/scripts.pory"
	end
# 15 "data/maps/Route110/scripts.pory"

# 16 "data/maps/Route110/scripts.pory"
Route110_OnTransition:
# 17 "data/maps/Route110/scripts.pory"
	call Common_EventScript_SetupRivalGfxId
# 18 "data/maps/Route110/scripts.pory"
	call Common_EventScript_SetupRivalOnBikeGfxId
# 19 "data/maps/Route110/scripts.pory"
	end
# 20 "data/maps/Route110/scripts.pory"

# 21 "data/maps/Route110/scripts.pory"
Route110_OnFrame:
# 22 "data/maps/Route110/scripts.pory"
	map_script_2 VAR_CYCLING_CHALLENGE_STATE, 1, Route110_EventScript_BeginCylcingRoadChallenge
# 23 "data/maps/Route110/scripts.pory"
	.2byte 0
# 24 "data/maps/Route110/scripts.pory"

# 25 "data/maps/Route110/scripts.pory"
Route110_EventScript_BeginCylcingRoadChallenge::
# 26 "data/maps/Route110/scripts.pory"
	special Special_BeginCyclingRoadChallenge
# 27 "data/maps/Route110/scripts.pory"
	setvar VAR_CYCLING_CHALLENGE_STATE, 2
# 28 "data/maps/Route110/scripts.pory"
	return
# 29 "data/maps/Route110/scripts.pory"

# 30 "data/maps/Route110/scripts.pory"
Route110_EventScript_AquaGrunt1::
# 31 "data/maps/Route110/scripts.pory"
	lock
# 32 "data/maps/Route110/scripts.pory"
	faceplayer
# 33 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_WeCantTalkAboutAquaActivities, MSGBOX_DEFAULT
# 34 "data/maps/Route110/scripts.pory"
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
# 35 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 36 "data/maps/Route110/scripts.pory"
	release
# 37 "data/maps/Route110/scripts.pory"
	end
# 38 "data/maps/Route110/scripts.pory"

# 39 "data/maps/Route110/scripts.pory"
Route110_EventScript_AquaGrunt2::
# 40 "data/maps/Route110/scripts.pory"
	lock
# 41 "data/maps/Route110/scripts.pory"
	faceplayer
# 42 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_KickUpARuckus, MSGBOX_DEFAULT
# 43 "data/maps/Route110/scripts.pory"
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
# 44 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 45 "data/maps/Route110/scripts.pory"
	release
# 46 "data/maps/Route110/scripts.pory"
	end
# 47 "data/maps/Route110/scripts.pory"

# 48 "data/maps/Route110/scripts.pory"
Route110_EventScript_AquaGrunt3::
# 49 "data/maps/Route110/scripts.pory"
	lock
# 50 "data/maps/Route110/scripts.pory"
	faceplayer
# 51 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_MyFirstJobInAqua, MSGBOX_DEFAULT
# 52 "data/maps/Route110/scripts.pory"
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
# 53 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 54 "data/maps/Route110/scripts.pory"
	release
# 55 "data/maps/Route110/scripts.pory"
	end
# 56 "data/maps/Route110/scripts.pory"

# 57 "data/maps/Route110/scripts.pory"
Route110_EventScript_AquaGrunt4::
# 58 "data/maps/Route110/scripts.pory"
	lock
# 59 "data/maps/Route110/scripts.pory"
	faceplayer
# 60 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_AquaActionsBringSmiles, MSGBOX_DEFAULT
# 61 "data/maps/Route110/scripts.pory"
	applymovement VAR_LAST_TALKED, Common_Movement_FaceOriginalDirection
# 62 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 63 "data/maps/Route110/scripts.pory"
	release
# 64 "data/maps/Route110/scripts.pory"
	end
# 65 "data/maps/Route110/scripts.pory"

# 66 "data/maps/Route110/scripts.pory"
Route110_EventScript_Boy1::
# 67 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_RideBikeAtFullSpeed, MSGBOX_NPC
# 68 "data/maps/Route110/scripts.pory"
	end
# 69 "data/maps/Route110/scripts.pory"

# 70 "data/maps/Route110/scripts.pory"
Route110_EventScript_CyclingGirl1::
# 71 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_HairStreamsBehindMe, MSGBOX_NPC
# 72 "data/maps/Route110/scripts.pory"
	end
# 73 "data/maps/Route110/scripts.pory"

# 74 "data/maps/Route110/scripts.pory"
Route110_EventScript_CyclingGuy1::
# 75 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_YouGotBikeFromRydel, MSGBOX_NPC
# 76 "data/maps/Route110/scripts.pory"
	end
# 77 "data/maps/Route110/scripts.pory"

# 78 "data/maps/Route110/scripts.pory"
Route110_EventScript_OldMan::
# 79 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_TwoRoads, MSGBOX_NPC
# 80 "data/maps/Route110/scripts.pory"
	end
# 81 "data/maps/Route110/scripts.pory"

# 82 "data/maps/Route110/scripts.pory"
Route110_EventScript_OldWoman::
# 83 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_WalkOnTheLowRoad, MSGBOX_NPC
# 84 "data/maps/Route110/scripts.pory"
	end
# 85 "data/maps/Route110/scripts.pory"

# 86 "data/maps/Route110/scripts.pory"
Route110_EventScript_CyclingGuy2::
# 87 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_BikeTechniques, MSGBOX_NPC
# 88 "data/maps/Route110/scripts.pory"
	end
# 89 "data/maps/Route110/scripts.pory"

# 90 "data/maps/Route110/scripts.pory"
Route110_EventScript_Boy2::
# 91 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_WhichShouldIChoose, MSGBOX_NPC
# 92 "data/maps/Route110/scripts.pory"
	end
# 93 "data/maps/Route110/scripts.pory"

# 94 "data/maps/Route110/scripts.pory"
Route110_EventScript_SlateportCitySign::
# 95 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_SlateportCitySign, MSGBOX_SIGN
# 96 "data/maps/Route110/scripts.pory"
	end
# 97 "data/maps/Route110/scripts.pory"

# 98 "data/maps/Route110/scripts.pory"
Route110_EventScript_CyclingRoadSign::
# 99 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_CyclingRoadSign, MSGBOX_SIGN
# 100 "data/maps/Route110/scripts.pory"
	end
# 101 "data/maps/Route110/scripts.pory"

# 102 "data/maps/Route110/scripts.pory"
Route110_EventScript_VandalizedSign::
# 103 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_AquaWasHere, MSGBOX_SIGN
# 104 "data/maps/Route110/scripts.pory"
	end
# 105 "data/maps/Route110/scripts.pory"

# 106 "data/maps/Route110/scripts.pory"
Route110_EventScript_Route103Sign::
# 107 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_Route103Sign, MSGBOX_SIGN
# 108 "data/maps/Route110/scripts.pory"
	end
# 109 "data/maps/Route110/scripts.pory"

# 110 "data/maps/Route110/scripts.pory"
Route110_EventScript_SeasideParkingSign::
# 111 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_SeasideParkingSign, MSGBOX_SIGN
# 112 "data/maps/Route110/scripts.pory"
	end
# 113 "data/maps/Route110/scripts.pory"

# 114 "data/maps/Route110/scripts.pory"
Route110_EventScript_MauvilleCitySign::
# 115 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_MauvilleCitySign, MSGBOX_SIGN
# 116 "data/maps/Route110/scripts.pory"
	end
# 117 "data/maps/Route110/scripts.pory"

# 118 "data/maps/Route110/scripts.pory"
Route110_EventScript_TrainerTipsPrlzSleep::
# 119 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_TrainerTipsPrlzSleep, MSGBOX_SIGN
# 120 "data/maps/Route110/scripts.pory"
	end
# 121 "data/maps/Route110/scripts.pory"

# 122 "data/maps/Route110/scripts.pory"
Route110_EventScript_TrainerTipsRegisterItems::
# 123 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_TrainerTipsRegisterItems, MSGBOX_SIGN
# 124 "data/maps/Route110/scripts.pory"
	end
# 125 "data/maps/Route110/scripts.pory"

# 126 "data/maps/Route110/scripts.pory"
Route110_EventScript_TrickHouseSign::
# 127 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_TrickHouseSign, MSGBOX_SIGN
# 128 "data/maps/Route110/scripts.pory"
	end
# 129 "data/maps/Route110/scripts.pory"

# 130 "data/maps/Route110/scripts.pory"
Route110_EventScript_CyclingRoadResultsSign::
# 131 "data/maps/Route110/scripts.pory"
	lockall
# 132 "data/maps/Route110/scripts.pory"
	specialvar VAR_RESULT, GetRecordedCyclingRoadResults
# 133 "data/maps/Route110/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Route110_EventScript_NoRecordSet
# 134 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_BestRecord, MSGBOX_DEFAULT
# 135 "data/maps/Route110/scripts.pory"
	releaseall
# 136 "data/maps/Route110/scripts.pory"
	end
# 137 "data/maps/Route110/scripts.pory"

# 138 "data/maps/Route110/scripts.pory"
Route110_EventScript_NoRecordSet::
# 139 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_ThereIsNoRecord, MSGBOX_DEFAULT
# 140 "data/maps/Route110/scripts.pory"
	releaseall
# 141 "data/maps/Route110/scripts.pory"
	end
# 142 "data/maps/Route110/scripts.pory"

# 143 "data/maps/Route110/scripts.pory"
Route110_EventScript_ChallengeGuy::
# 144 "data/maps/Route110/scripts.pory"
	lock
# 145 "data/maps/Route110/scripts.pory"
	faceplayer
# 146 "data/maps/Route110/scripts.pory"
	specialvar VAR_RESULT, GetPlayerAvatarBike
# 147 "data/maps/Route110/scripts.pory"
	goto_if_eq VAR_RESULT, 1, Route110_EventScript_PlayerRidingAcroBike
# 148 "data/maps/Route110/scripts.pory"
	goto_if_eq VAR_CYCLING_CHALLENGE_STATE, 0, Route110_EventScript_PlayerNotRidingBike
# 149 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_AlwaysAimHigher, MSGBOX_DEFAULT
# 150 "data/maps/Route110/scripts.pory"
	release
# 151 "data/maps/Route110/scripts.pory"
	end
# 152 "data/maps/Route110/scripts.pory"

# 153 "data/maps/Route110/scripts.pory"
Route110_EventScript_PlayerNotRidingBike::
# 154 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_RatedForNumberOfCollisions, MSGBOX_DEFAULT
# 155 "data/maps/Route110/scripts.pory"
	release
# 156 "data/maps/Route110/scripts.pory"
	end
# 157 "data/maps/Route110/scripts.pory"

# 158 "data/maps/Route110/scripts.pory"
Route110_EventScript_PlayerRidingAcroBike::
# 159 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_AcroBikesDoNotQualify, MSGBOX_DEFAULT
# 160 "data/maps/Route110/scripts.pory"
	release
# 161 "data/maps/Route110/scripts.pory"
	end
# 162 "data/maps/Route110/scripts.pory"

# 163 "data/maps/Route110/scripts.pory"
Route110_EventScript_Edward::
# 164 "data/maps/Route110/scripts.pory"
	trainerbattle_single TRAINER_EDWARD, Route110_Text_EdwardIntro, Route110_Text_EdwardDefeated
# 165 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_EdwardPostBattle, MSGBOX_AUTOCLOSE
# 166 "data/maps/Route110/scripts.pory"
	end
# 167 "data/maps/Route110/scripts.pory"

# 168 "data/maps/Route110/scripts.pory"
Route110_EventScript_Jaclyn::
# 169 "data/maps/Route110/scripts.pory"
	trainerbattle_single TRAINER_JACLYN, Route110_Text_JaclynIntro, Route110_Text_JaclynDefeated
# 170 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_JaclynPostBattle, MSGBOX_AUTOCLOSE
# 171 "data/maps/Route110/scripts.pory"
	end
# 172 "data/maps/Route110/scripts.pory"

# 173 "data/maps/Route110/scripts.pory"
Route110_EventScript_Edwin::
# 174 "data/maps/Route110/scripts.pory"
	trainerbattle_single TRAINER_EDWIN_1, Route110_Text_EdwinIntro, Route110_Text_EdwinDefeated, Route110_EventScript_EdwinRegisterMatchCallAfterBattle
# 175 "data/maps/Route110/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 176 "data/maps/Route110/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route110_EventScript_EdwinRematch
# 177 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_EdwinPostBattle, MSGBOX_DEFAULT
# 178 "data/maps/Route110/scripts.pory"
	release
# 179 "data/maps/Route110/scripts.pory"
	end
# 180 "data/maps/Route110/scripts.pory"

# 181 "data/maps/Route110/scripts.pory"
Route110_EventScript_EdwinRegisterMatchCallAfterBattle::
# 182 "data/maps/Route110/scripts.pory"
	special PlayerFaceTrainerAfterBattle
# 183 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 184 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_EdwinRegister, MSGBOX_DEFAULT
# 185 "data/maps/Route110/scripts.pory"
	register_matchcall TRAINER_EDWIN_1
# 186 "data/maps/Route110/scripts.pory"
	release
# 187 "data/maps/Route110/scripts.pory"
	end
# 188 "data/maps/Route110/scripts.pory"

# 189 "data/maps/Route110/scripts.pory"
Route110_EventScript_EdwinRematch::
# 190 "data/maps/Route110/scripts.pory"
	trainerbattle_rematch TRAINER_EDWIN_1, Route110_Text_EdwinRematchIntro, Route110_Text_EdwinRematchDefeated
# 191 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_EdwinRematchPostBattle, MSGBOX_AUTOCLOSE
# 192 "data/maps/Route110/scripts.pory"
	end
# 193 "data/maps/Route110/scripts.pory"

# 194 "data/maps/Route110/scripts.pory"
Route110_EventScript_Dale::
# 195 "data/maps/Route110/scripts.pory"
	trainerbattle_single TRAINER_DALE, Route110_Text_DaleIntro, Route110_Text_DaleDefeated
# 196 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_DalePostBattle, MSGBOX_AUTOCLOSE
# 197 "data/maps/Route110/scripts.pory"
	end
# 198 "data/maps/Route110/scripts.pory"

# 199 "data/maps/Route110/scripts.pory"
Route110_EventScript_Jacob::
# 200 "data/maps/Route110/scripts.pory"
	trainerbattle_single TRAINER_JACOB, Route110_Text_JacobIntro, Route110_Text_JacobDefeated
# 201 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_JacobPostBattle, MSGBOX_AUTOCLOSE
# 202 "data/maps/Route110/scripts.pory"
	end
# 203 "data/maps/Route110/scripts.pory"

# 204 "data/maps/Route110/scripts.pory"
Route110_EventScript_Anthony::
# 205 "data/maps/Route110/scripts.pory"
	trainerbattle_single TRAINER_ANTHONY, Route110_Text_AnthonyIntro, Route110_Text_AnthonyDefeated
# 206 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_AnthonyPostBattle, MSGBOX_AUTOCLOSE
# 207 "data/maps/Route110/scripts.pory"
	end
# 208 "data/maps/Route110/scripts.pory"

# 209 "data/maps/Route110/scripts.pory"
Route110_EventScript_Benjamin::
# 210 "data/maps/Route110/scripts.pory"
	trainerbattle_single TRAINER_BENJAMIN_1, Route110_Text_BenjaminIntro, Route110_Text_BenjaminDefeated, Route110_EventScript_BenjaminRegisterMatchCallAfterBattle
# 211 "data/maps/Route110/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 212 "data/maps/Route110/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route110_EventScript_BenjaminRematch
# 213 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_BenjaminPostBattle, MSGBOX_DEFAULT
# 214 "data/maps/Route110/scripts.pory"
	release
# 215 "data/maps/Route110/scripts.pory"
	end
# 216 "data/maps/Route110/scripts.pory"

# 217 "data/maps/Route110/scripts.pory"
Route110_EventScript_BenjaminRegisterMatchCallAfterBattle::
# 218 "data/maps/Route110/scripts.pory"
	special PlayerFaceTrainerAfterBattle
# 219 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 220 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_BenjaminRegister, MSGBOX_DEFAULT
# 221 "data/maps/Route110/scripts.pory"
	register_matchcall TRAINER_BENJAMIN_1
# 222 "data/maps/Route110/scripts.pory"
	release
# 223 "data/maps/Route110/scripts.pory"
	end
# 224 "data/maps/Route110/scripts.pory"

# 225 "data/maps/Route110/scripts.pory"
Route110_EventScript_BenjaminRematch::
# 226 "data/maps/Route110/scripts.pory"
	trainerbattle_rematch TRAINER_BENJAMIN_1, Route110_Text_BenjaminRematchIntro, Route110_Text_BenjaminRematchDefeated
# 227 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_BenjaminRematchPostBattle, MSGBOX_AUTOCLOSE
# 228 "data/maps/Route110/scripts.pory"
	end
# 229 "data/maps/Route110/scripts.pory"

# 230 "data/maps/Route110/scripts.pory"
Route110_EventScript_Jasmine::
# 231 "data/maps/Route110/scripts.pory"
	trainerbattle_single TRAINER_JASMINE, Route110_Text_JasmineIntro, Route110_Text_JasmineDefeated
# 232 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_JasminePostBattle, MSGBOX_AUTOCLOSE
# 233 "data/maps/Route110/scripts.pory"
	end
# 234 "data/maps/Route110/scripts.pory"

# 235 "data/maps/Route110/scripts.pory"
Route110_EventScript_Abigail::
# 236 "data/maps/Route110/scripts.pory"
	trainerbattle_single TRAINER_ABIGAIL_1, Route110_Text_AbigailIntro, Route110_Text_AbigailDefeated, Route110_EventScript_AbigailRegisterMatchCallAfterBattle
# 237 "data/maps/Route110/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 238 "data/maps/Route110/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route110_EventScript_AbigailRematch
# 239 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_AbigailPostBattle, MSGBOX_DEFAULT
# 240 "data/maps/Route110/scripts.pory"
	release
# 241 "data/maps/Route110/scripts.pory"
	end
# 242 "data/maps/Route110/scripts.pory"

# 243 "data/maps/Route110/scripts.pory"
Route110_EventScript_AbigailRegisterMatchCallAfterBattle::
# 244 "data/maps/Route110/scripts.pory"
	special PlayerFaceTrainerAfterBattle
# 245 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 246 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_AbigailRegister, MSGBOX_DEFAULT
# 247 "data/maps/Route110/scripts.pory"
	register_matchcall TRAINER_ABIGAIL_1
# 248 "data/maps/Route110/scripts.pory"
	release
# 249 "data/maps/Route110/scripts.pory"
	end
# 250 "data/maps/Route110/scripts.pory"

# 251 "data/maps/Route110/scripts.pory"
Route110_EventScript_AbigailRematch::
# 252 "data/maps/Route110/scripts.pory"
	trainerbattle_rematch TRAINER_ABIGAIL_1, Route110_Text_AbigailRematchIntro, Route110_Text_AbigailRematchDefeated
# 253 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_AbigailRematchPostBattle, MSGBOX_AUTOCLOSE
# 254 "data/maps/Route110/scripts.pory"
	end
# 255 "data/maps/Route110/scripts.pory"

# 256 "data/maps/Route110/scripts.pory"
Route110_EventScript_Isabel::
# 257 "data/maps/Route110/scripts.pory"
	trainerbattle_single TRAINER_ISABEL_1, Route110_Text_IsabelIntro, Route110_Text_IsabelDefeated, Route110_EventScript_IsabelRegisterMatchCallAfterBattle
# 258 "data/maps/Route110/scripts.pory"
	specialvar VAR_RESULT, ShouldTryRematchBattle
# 259 "data/maps/Route110/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Route110_EventScript_IsabelRematch
# 260 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_IsabelPostBattle, MSGBOX_DEFAULT
# 261 "data/maps/Route110/scripts.pory"
	release
# 262 "data/maps/Route110/scripts.pory"
	end
# 263 "data/maps/Route110/scripts.pory"

# 264 "data/maps/Route110/scripts.pory"
Route110_EventScript_IsabelRegisterMatchCallAfterBattle::
# 265 "data/maps/Route110/scripts.pory"
	special PlayerFaceTrainerAfterBattle
# 266 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 267 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_IsabelRegister, MSGBOX_DEFAULT
# 268 "data/maps/Route110/scripts.pory"
	register_matchcall TRAINER_ISABEL_1
# 269 "data/maps/Route110/scripts.pory"
	release
# 270 "data/maps/Route110/scripts.pory"
	end
# 271 "data/maps/Route110/scripts.pory"

# 272 "data/maps/Route110/scripts.pory"
Route110_EventScript_IsabelRematch::
# 273 "data/maps/Route110/scripts.pory"
	trainerbattle_rematch TRAINER_ISABEL_1, Route110_Text_IsabelRematchIntro, Route110_Text_IsabelRematchDefeated
# 274 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_IsabelRematchPostBattle, MSGBOX_AUTOCLOSE
# 275 "data/maps/Route110/scripts.pory"
	end
# 276 "data/maps/Route110/scripts.pory"

# 277 "data/maps/Route110/scripts.pory"
Route110_EventScript_Timmy::
# 278 "data/maps/Route110/scripts.pory"
	trainerbattle_single TRAINER_TIMMY, Route110_Text_TimmyIntro, Route110_Text_TimmyDefeated
# 279 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_TimmyPostBattle, MSGBOX_AUTOCLOSE
# 280 "data/maps/Route110/scripts.pory"
	end
# 281 "data/maps/Route110/scripts.pory"

# 282 "data/maps/Route110/scripts.pory"
Route110_EventScript_Unused::
# 283 "data/maps/Route110/scripts.pory"
	end
# 284 "data/maps/Route110/scripts.pory"

# 285 "data/maps/Route110/scripts.pory"
Route110_EventScript_Kaleb::
# 286 "data/maps/Route110/scripts.pory"
	trainerbattle_single TRAINER_KALEB, Route110_Text_KalebIntro, Route110_Text_KalebDefeated
# 287 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_KalebPostBattle, MSGBOX_AUTOCLOSE
# 288 "data/maps/Route110/scripts.pory"
	end
# 289 "data/maps/Route110/scripts.pory"

# 290 "data/maps/Route110/scripts.pory"
Route110_EventScript_Joseph::
# 291 "data/maps/Route110/scripts.pory"
	trainerbattle_single TRAINER_JOSEPH, Route110_Text_JosephIntro, Route110_Text_JosephDefeated
# 292 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_JosephPostBattle, MSGBOX_AUTOCLOSE
# 293 "data/maps/Route110/scripts.pory"
	end
# 294 "data/maps/Route110/scripts.pory"

# 295 "data/maps/Route110/scripts.pory"
Route110_EventScript_Alyssa::
# 296 "data/maps/Route110/scripts.pory"
	trainerbattle_single TRAINER_ALYSSA, Route110_Text_AlyssaIntro, Route110_Text_AlyssaDefeated
# 297 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_AlyssaPostBattle, MSGBOX_AUTOCLOSE
# 298 "data/maps/Route110/scripts.pory"
	end
# 299 "data/maps/Route110/scripts.pory"

# 300 "data/maps/Route110/scripts.pory"
Route110_EventScript_CyclingChallengeEnd::
# 301 "data/maps/Route110/scripts.pory"
	lockall
# 302 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_CHALLENGE_BIKER, Common_Movement_WalkInPlaceFasterRight
# 303 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 304 "data/maps/Route110/scripts.pory"
	call Route110_EventScript_CyclingChallengeResults
# 305 "data/maps/Route110/scripts.pory"
	releaseall
# 306 "data/maps/Route110/scripts.pory"
	end
# 307 "data/maps/Route110/scripts.pory"

# 308 "data/maps/Route110/scripts.pory"
Route110_EventScript_CyclingChallengeResults::
# 309 "data/maps/Route110/scripts.pory"
	special FinishCyclingRoadChallenge
# 310 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_CyclingChallengeResultSummary, MSGBOX_DEFAULT
# 311 "data/maps/Route110/scripts.pory"
	switch VAR_RESULT
# 312 "data/maps/Route110/scripts.pory"
	case 10, Route110_EventScript_ChallengeReactionBest
# 313 "data/maps/Route110/scripts.pory"
	case 9, Route110_EventScript_ChallengeReactionGood
# 314 "data/maps/Route110/scripts.pory"
	case 8, Route110_EventScript_ChallengeReactionGood
# 315 "data/maps/Route110/scripts.pory"
	case 7, Route110_EventScript_ChallengeReactionGood
# 316 "data/maps/Route110/scripts.pory"
	case 6, Route110_EventScript_ChallengeReactionOk
# 317 "data/maps/Route110/scripts.pory"
	case 5, Route110_EventScript_ChallengeReactionOk
# 318 "data/maps/Route110/scripts.pory"
	case 4, Route110_EventScript_ChallengeReactionOk
# 319 "data/maps/Route110/scripts.pory"
	case 3, Route110_EventScript_ChallengeReactionBad
# 320 "data/maps/Route110/scripts.pory"
	case 2, Route110_EventScript_ChallengeReactionBad
# 321 "data/maps/Route110/scripts.pory"
	case 1, Route110_EventScript_ChallengeReactionBad
# 322 "data/maps/Route110/scripts.pory"
	case 0, Route110_EventScript_ChallengeReactionWorst
# 323 "data/maps/Route110/scripts.pory"
	end
# 324 "data/maps/Route110/scripts.pory"

# 325 "data/maps/Route110/scripts.pory"
Route110_EventScript_ChallengeReactionBest::
# 326 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_ChallengeReactionBest, MSGBOX_DEFAULT
# 327 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_EndChallenge
# 328 "data/maps/Route110/scripts.pory"
	end
# 329 "data/maps/Route110/scripts.pory"

# 330 "data/maps/Route110/scripts.pory"
Route110_EventScript_ChallengeReactionGood::
# 331 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_ChallengeReactionGood, MSGBOX_DEFAULT
# 332 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_EndChallenge
# 333 "data/maps/Route110/scripts.pory"
	end
# 334 "data/maps/Route110/scripts.pory"

# 335 "data/maps/Route110/scripts.pory"
Route110_EventScript_ChallengeReactionOk::
# 336 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_ChallengeReactionOk, MSGBOX_DEFAULT
# 337 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_EndChallenge
# 338 "data/maps/Route110/scripts.pory"
	end
# 339 "data/maps/Route110/scripts.pory"

# 340 "data/maps/Route110/scripts.pory"
Route110_EventScript_ChallengeReactionBad::
# 341 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_ChallengeReactionBad, MSGBOX_DEFAULT
# 342 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_EndChallenge
# 343 "data/maps/Route110/scripts.pory"
	end
# 344 "data/maps/Route110/scripts.pory"

# 345 "data/maps/Route110/scripts.pory"
Route110_EventScript_ChallengeReactionWorst::
# 346 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_ChallengeReactionWorst, MSGBOX_DEFAULT
# 347 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_EndChallenge
# 348 "data/maps/Route110/scripts.pory"
	end
# 349 "data/maps/Route110/scripts.pory"

# 350 "data/maps/Route110/scripts.pory"
Route110_EventScript_EndChallenge::
# 351 "data/maps/Route110/scripts.pory"
	setvar VAR_CYCLING_CHALLENGE_STATE, 3
# 352 "data/maps/Route110/scripts.pory"
	savebgm MUS_DUMMY
# 353 "data/maps/Route110/scripts.pory"
	fadedefaultbgm
# 354 "data/maps/Route110/scripts.pory"
	return
# 355 "data/maps/Route110/scripts.pory"

# 356 "data/maps/Route110/scripts.pory"
Route110_EventScript_RivalTrigger1::
# 357 "data/maps/Route110/scripts.pory"
	setvar VAR_0x8008, 1
# 358 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_RivalScene
# 359 "data/maps/Route110/scripts.pory"
	end
# 360 "data/maps/Route110/scripts.pory"

# 361 "data/maps/Route110/scripts.pory"
Route110_EventScript_RivalTrigger2::
# 362 "data/maps/Route110/scripts.pory"
	setvar VAR_0x8008, 2
# 363 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_RivalScene
# 364 "data/maps/Route110/scripts.pory"
	end
# 365 "data/maps/Route110/scripts.pory"

# 366 "data/maps/Route110/scripts.pory"
Route110_EventScript_RivalTrigger3::
# 367 "data/maps/Route110/scripts.pory"
	setvar VAR_0x8008, 3
# 368 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_RivalScene
# 369 "data/maps/Route110/scripts.pory"
	end
# 370 "data/maps/Route110/scripts.pory"

# 371 "data/maps/Route110/scripts.pory"
Route110_EventScript_RivalScene::
# 372 "data/maps/Route110/scripts.pory"
	lockall
# 373 "data/maps/Route110/scripts.pory"
	checkplayergender
# 374 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_RESULT, MALE, Route110_EventScript_PlayMayMusic
# 375 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_RESULT, FEMALE, Route110_EventScript_PlayBrendanMusic
# 376 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_RIVAL, Common_Movement_WalkInPlaceFasterDown
# 377 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 378 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_RIVAL, Common_Movement_ExclamationMark
# 379 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 380 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_RIVAL, Common_Movement_Delay48
# 381 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 382 "data/maps/Route110/scripts.pory"
	delay 30
# 383 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 1, Route110_EventScript_RivalApproachPlayer1
# 384 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 2, Route110_EventScript_RivalApproachPlayer2
# 385 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 3, Route110_EventScript_RivalApproachPlayer3
# 386 "data/maps/Route110/scripts.pory"
	checkplayergender
# 387 "data/maps/Route110/scripts.pory"
	goto_if_eq VAR_RESULT, MALE, Route110_EventScript_MayBattle
# 388 "data/maps/Route110/scripts.pory"
	goto_if_eq VAR_RESULT, FEMALE, Route110_EventScript_BrendanBattle
# 389 "data/maps/Route110/scripts.pory"
	releaseall
# 390 "data/maps/Route110/scripts.pory"
	end
# 391 "data/maps/Route110/scripts.pory"

# 392 "data/maps/Route110/scripts.pory"
Route110_EventScript_PlayMayMusic::
# 393 "data/maps/Route110/scripts.pory"
	playbgm MUS_ENCOUNTER_MAY, TRUE
# 394 "data/maps/Route110/scripts.pory"
	return
# 395 "data/maps/Route110/scripts.pory"

# 396 "data/maps/Route110/scripts.pory"
Route110_EventScript_PlayBrendanMusic::
# 397 "data/maps/Route110/scripts.pory"
	playbgm MUS_ENCOUNTER_BRENDAN, TRUE
# 398 "data/maps/Route110/scripts.pory"
	return
# 399 "data/maps/Route110/scripts.pory"

# 400 "data/maps/Route110/scripts.pory"
Route110_EventScript_MayBattle::
# 401 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_MayLetsBattle, MSGBOX_DEFAULT
# 402 "data/maps/Route110/scripts.pory"
	switch VAR_STARTER_MON
# 403 "data/maps/Route110/scripts.pory"
	case 0, Route110_EventScript_MayBattleTreecko
# 404 "data/maps/Route110/scripts.pory"
	case 1, Route110_EventScript_MayBattleTorchic
# 405 "data/maps/Route110/scripts.pory"
	case 2, Route110_EventScript_MayBattleMudkip
# 406 "data/maps/Route110/scripts.pory"
	end
# 407 "data/maps/Route110/scripts.pory"

# 408 "data/maps/Route110/scripts.pory"
Route110_EventScript_MayBattleTreecko::
# 409 "data/maps/Route110/scripts.pory"
	trainerbattle_no_intro TRAINER_MAY_ROUTE_110_TREECKO, Route110_Text_MayDefeated
# 410 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_MayDefeated
# 411 "data/maps/Route110/scripts.pory"
	end
# 412 "data/maps/Route110/scripts.pory"

# 413 "data/maps/Route110/scripts.pory"
Route110_EventScript_MayBattleTorchic::
# 414 "data/maps/Route110/scripts.pory"
	trainerbattle_no_intro TRAINER_MAY_ROUTE_110_TORCHIC, Route110_Text_MayDefeated
# 415 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_MayDefeated
# 416 "data/maps/Route110/scripts.pory"
	end
# 417 "data/maps/Route110/scripts.pory"

# 418 "data/maps/Route110/scripts.pory"
Route110_EventScript_MayBattleMudkip::
# 419 "data/maps/Route110/scripts.pory"
	trainerbattle_no_intro TRAINER_MAY_ROUTE_110_MUDKIP, Route110_Text_MayDefeated
# 420 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_MayDefeated
# 421 "data/maps/Route110/scripts.pory"
	end
# 422 "data/maps/Route110/scripts.pory"

# 423 "data/maps/Route110/scripts.pory"
Route110_EventScript_MayDefeated::
# 424 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_MayTakeThis, MSGBOX_DEFAULT
# 425 "data/maps/Route110/scripts.pory"
	call Route110_EventScript_GiveItemfinder
# 426 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_MayExplainItemfinder, MSGBOX_DEFAULT
# 427 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_RivalExit
# 428 "data/maps/Route110/scripts.pory"
	end
# 429 "data/maps/Route110/scripts.pory"

# 430 "data/maps/Route110/scripts.pory"
Route110_EventScript_BrendanBattle::
# 431 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_BrendanLetsBattle, MSGBOX_DEFAULT
# 432 "data/maps/Route110/scripts.pory"
	switch VAR_STARTER_MON
# 433 "data/maps/Route110/scripts.pory"
	case 0, Route110_EventScript_BrendanBattleTreecko
# 434 "data/maps/Route110/scripts.pory"
	case 1, Route110_EventScript_BrendanBattleTorchic
# 435 "data/maps/Route110/scripts.pory"
	case 2, Route110_EventScript_BrendanBattleMudkip
# 436 "data/maps/Route110/scripts.pory"
	end
# 437 "data/maps/Route110/scripts.pory"

# 438 "data/maps/Route110/scripts.pory"
Route110_EventScript_BrendanBattleTreecko::
# 439 "data/maps/Route110/scripts.pory"
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_110_TREECKO, Route110_Text_BrendanDefeated
# 440 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_BrendanDefeated
# 441 "data/maps/Route110/scripts.pory"
	end
# 442 "data/maps/Route110/scripts.pory"

# 443 "data/maps/Route110/scripts.pory"
Route110_EventScript_BrendanBattleTorchic::
# 444 "data/maps/Route110/scripts.pory"
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_110_TORCHIC, Route110_Text_BrendanDefeated
# 445 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_BrendanDefeated
# 446 "data/maps/Route110/scripts.pory"
	end
# 447 "data/maps/Route110/scripts.pory"

# 448 "data/maps/Route110/scripts.pory"
Route110_EventScript_BrendanBattleMudkip::
# 449 "data/maps/Route110/scripts.pory"
	trainerbattle_no_intro TRAINER_BRENDAN_ROUTE_110_MUDKIP, Route110_Text_BrendanDefeated
# 450 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_BrendanDefeated
# 451 "data/maps/Route110/scripts.pory"
	end
# 452 "data/maps/Route110/scripts.pory"

# 453 "data/maps/Route110/scripts.pory"
Route110_EventScript_BrendanDefeated::
# 454 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_BrendanTakeThis, MSGBOX_DEFAULT
# 455 "data/maps/Route110/scripts.pory"
	call Route110_EventScript_GiveItemfinder
# 456 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_BrendanExplainItemfinder, MSGBOX_DEFAULT
# 457 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_RivalExit
# 458 "data/maps/Route110/scripts.pory"
	end
# 459 "data/maps/Route110/scripts.pory"

# 460 "data/maps/Route110/scripts.pory"
Route110_EventScript_GiveItemfinder::
# 461 "data/maps/Route110/scripts.pory"
	giveitem ITEM_DOWSING_MACHINE
# 462 "data/maps/Route110/scripts.pory"
	return
# 463 "data/maps/Route110/scripts.pory"

# 464 "data/maps/Route110/scripts.pory"
Route110_EventScript_RivalExit::
# 465 "data/maps/Route110/scripts.pory"
	closemessage
# 466 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 1, Route110_EventScript_MoveRival1
# 467 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 2, Route110_EventScript_MoveRival2
# 468 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 3, Route110_EventScript_MoveRival3
# 469 "data/maps/Route110/scripts.pory"
	setobjectmovementtype LOCALID_RIVAL, MOVEMENT_TYPE_FACE_RIGHT
# 470 "data/maps/Route110/scripts.pory"
	setobjectmovementtype LOCALID_RIVAL_ON_BIKE, MOVEMENT_TYPE_FACE_RIGHT
# 471 "data/maps/Route110/scripts.pory"
	removeobject LOCALID_RIVAL
# 472 "data/maps/Route110/scripts.pory"
	addobject LOCALID_RIVAL_ON_BIKE
# 473 "data/maps/Route110/scripts.pory"
	delay 45
# 474 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 1, Route110_EventScript_RivalExit1
# 475 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 2, Route110_EventScript_RivalExit2
# 476 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 3, Route110_EventScript_RivalExit3
# 477 "data/maps/Route110/scripts.pory"
	removeobject LOCALID_RIVAL_ON_BIKE
# 478 "data/maps/Route110/scripts.pory"
	setvar VAR_ROUTE110_STATE, 1
# 479 "data/maps/Route110/scripts.pory"
	savebgm MUS_DUMMY
# 480 "data/maps/Route110/scripts.pory"
	fadedefaultbgm
# 481 "data/maps/Route110/scripts.pory"
	releaseall
# 482 "data/maps/Route110/scripts.pory"
	end
# 483 "data/maps/Route110/scripts.pory"

# 484 "data/maps/Route110/scripts.pory"
Route110_EventScript_RivalApproachPlayer1::
# 485 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_RIVAL, Route110_Movement_RivalApproachPlayer1
# 486 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 487 "data/maps/Route110/scripts.pory"
	return
# 488 "data/maps/Route110/scripts.pory"

# 489 "data/maps/Route110/scripts.pory"
Route110_EventScript_RivalApproachPlayer2::
# 490 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_RIVAL, Route110_Movement_RivalApproachPlayer2
# 491 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 492 "data/maps/Route110/scripts.pory"
	return
# 493 "data/maps/Route110/scripts.pory"

# 494 "data/maps/Route110/scripts.pory"
Route110_EventScript_RivalApproachPlayer3::
# 495 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_RIVAL, Route110_Movement_RivalApproachPlayer3
# 496 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 497 "data/maps/Route110/scripts.pory"
	return
# 498 "data/maps/Route110/scripts.pory"

# 499 "data/maps/Route110/scripts.pory"
Route110_EventScript_RivalExit1::
# 500 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_RIVAL_ON_BIKE, Route110_Movement_RivalExit1
# 501 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 502 "data/maps/Route110/scripts.pory"
	return
# 503 "data/maps/Route110/scripts.pory"

# 504 "data/maps/Route110/scripts.pory"
Route110_EventScript_RivalExit2::
# 505 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_RIVAL_ON_BIKE, Route110_Movement_RivalExit2
# 506 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 507 "data/maps/Route110/scripts.pory"
	return
# 508 "data/maps/Route110/scripts.pory"

# 509 "data/maps/Route110/scripts.pory"
Route110_EventScript_RivalExit3::
# 510 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_RIVAL_ON_BIKE, Route110_Movement_RivalExit3
# 511 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 512 "data/maps/Route110/scripts.pory"
	return
# 513 "data/maps/Route110/scripts.pory"

# 514 "data/maps/Route110/scripts.pory"
Route110_EventScript_MoveRival1::
# 515 "data/maps/Route110/scripts.pory"
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 33, 55
# 516 "data/maps/Route110/scripts.pory"
	return
# 517 "data/maps/Route110/scripts.pory"

# 518 "data/maps/Route110/scripts.pory"
Route110_EventScript_MoveRival2::
# 519 "data/maps/Route110/scripts.pory"
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 34, 55
# 520 "data/maps/Route110/scripts.pory"
	return
# 521 "data/maps/Route110/scripts.pory"

# 522 "data/maps/Route110/scripts.pory"
Route110_EventScript_MoveRival3::
# 523 "data/maps/Route110/scripts.pory"
	setobjectxyperm LOCALID_RIVAL_ON_BIKE, 35, 55
# 524 "data/maps/Route110/scripts.pory"
	return
# 525 "data/maps/Route110/scripts.pory"

# 526 "data/maps/Route110/scripts.pory"
Route110_Movement_RivalApproachPlayer1:
# 527 "data/maps/Route110/scripts.pory"
	walk_down
# 528 "data/maps/Route110/scripts.pory"
	walk_left
# 529 "data/maps/Route110/scripts.pory"
	walk_in_place_faster_down
# 530 "data/maps/Route110/scripts.pory"
	step_end
# 531 "data/maps/Route110/scripts.pory"

# 532 "data/maps/Route110/scripts.pory"
Route110_Movement_RivalApproachPlayer2:
# 533 "data/maps/Route110/scripts.pory"
	walk_down
# 534 "data/maps/Route110/scripts.pory"
	step_end
# 535 "data/maps/Route110/scripts.pory"

# 536 "data/maps/Route110/scripts.pory"
Route110_Movement_RivalApproachPlayer3:
# 537 "data/maps/Route110/scripts.pory"
	walk_down
# 538 "data/maps/Route110/scripts.pory"
	walk_right
# 539 "data/maps/Route110/scripts.pory"
	walk_in_place_faster_down
# 540 "data/maps/Route110/scripts.pory"
	step_end
# 541 "data/maps/Route110/scripts.pory"

# 542 "data/maps/Route110/scripts.pory"
Route110_Movement_RivalExit1:
# 543 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 544 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 545 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 546 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 547 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 548 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 549 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 550 "data/maps/Route110/scripts.pory"
	step_end
# 551 "data/maps/Route110/scripts.pory"

# 552 "data/maps/Route110/scripts.pory"
Route110_Movement_RivalExit2:
# 553 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 554 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 555 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 556 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 557 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 558 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 559 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 560 "data/maps/Route110/scripts.pory"
	walk_fast_down
# 561 "data/maps/Route110/scripts.pory"
	step_end
# 562 "data/maps/Route110/scripts.pory"

# 563 "data/maps/Route110/scripts.pory"
Route110_Movement_RivalExit3:
# 564 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 565 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 566 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 567 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 568 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 569 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 570 "data/maps/Route110/scripts.pory"
	walk_fast_up
# 571 "data/maps/Route110/scripts.pory"
	step_end
# 572 "data/maps/Route110/scripts.pory"

# 573 "data/maps/Route110/scripts.pory"
Route110_EventScript_BirchScene1::
# 574 "data/maps/Route110/scripts.pory"
	lockall
# 575 "data/maps/Route110/scripts.pory"
	setvar VAR_0x8008, 1
# 576 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_BirchScene
# 577 "data/maps/Route110/scripts.pory"

# 578 "data/maps/Route110/scripts.pory"
Route110_EventScript_BirchScene2::
# 579 "data/maps/Route110/scripts.pory"
	lockall
# 580 "data/maps/Route110/scripts.pory"
	setvar VAR_0x8008, 2
# 581 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_BirchScene
# 582 "data/maps/Route110/scripts.pory"

# 583 "data/maps/Route110/scripts.pory"
Route110_EventScript_BirchScene3::
# 584 "data/maps/Route110/scripts.pory"
	lockall
# 585 "data/maps/Route110/scripts.pory"
	setvar VAR_0x8008, 3
# 586 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_BirchScene
# 587 "data/maps/Route110/scripts.pory"

# 588 "data/maps/Route110/scripts.pory"
Route110_EventScript_BirchScene4::
# 589 "data/maps/Route110/scripts.pory"
	lockall
# 590 "data/maps/Route110/scripts.pory"
	setvar VAR_0x8008, 4
# 591 "data/maps/Route110/scripts.pory"
	goto Route110_EventScript_BirchScene
# 592 "data/maps/Route110/scripts.pory"

# 593 "data/maps/Route110/scripts.pory"
Route110_EventScript_BirchScene::
# 594 "data/maps/Route110/scripts.pory"
	addobject LOCALID_BIRCH
# 595 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_BIRCH, Route110_Movement_BirchEntrance
# 596 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 597 "data/maps/Route110/scripts.pory"
	playse SE_PIN
# 598 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_BIRCH, Common_Movement_ExclamationMark
# 599 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 600 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_BIRCH, Common_Movement_Delay48
# 601 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 602 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 1, Route110_EventScript_BirchApproachPlayer1
# 603 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 2, Route110_EventScript_BirchApproachPlayer2
# 604 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 3, Route110_EventScript_BirchApproachPlayer3
# 605 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 4, Route110_EventScript_BirchApproachPlayer4
# 606 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_ImagineSeeingYouHere, MSGBOX_DEFAULT
# 607 "data/maps/Route110/scripts.pory"
	closemessage
# 608 "data/maps/Route110/scripts.pory"
	delay 20
# 609 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterLeft
# 610 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 611 "data/maps/Route110/scripts.pory"
	delay 10
# 612 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterRight
# 613 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 614 "data/maps/Route110/scripts.pory"
	delay 20
# 615 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_BIRCH, Common_Movement_WalkInPlaceFasterDown
# 616 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 617 "data/maps/Route110/scripts.pory"
	delay 30
# 618 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_HeardYouInstallMatchCall, MSGBOX_DEFAULT
# 619 "data/maps/Route110/scripts.pory"
	closemessage
# 620 "data/maps/Route110/scripts.pory"
	delay 30
# 621 "data/maps/Route110/scripts.pory"
	playfanfare MUS_REGISTER_MATCH_CALL
# 622 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_RegisteredBirchInPokenav, MSGBOX_DEFAULT
# 623 "data/maps/Route110/scripts.pory"
	waitfanfare
# 624 "data/maps/Route110/scripts.pory"
	closemessage
# 625 "data/maps/Route110/scripts.pory"
	delay 30
# 626 "data/maps/Route110/scripts.pory"
	setflag FLAG_ENABLE_PROF_BIRCH_MATCH_CALL
# 627 "data/maps/Route110/scripts.pory"
	msgbox Route110_Text_KeepAnEyeOutForRival, MSGBOX_DEFAULT
# 628 "data/maps/Route110/scripts.pory"
	closemessage
# 629 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 1, Route110_EventScript_BirchExit1
# 630 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 2, Route110_EventScript_BirchExit2
# 631 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 3, Route110_EventScript_BirchExit3
# 632 "data/maps/Route110/scripts.pory"
	call_if_eq VAR_0x8008, 4, Route110_EventScript_BirchExit4
# 633 "data/maps/Route110/scripts.pory"
	removeobject LOCALID_BIRCH
# 634 "data/maps/Route110/scripts.pory"
	setvar VAR_REGISTER_BIRCH_STATE, 2
# 635 "data/maps/Route110/scripts.pory"
	releaseall
# 636 "data/maps/Route110/scripts.pory"
	end
# 637 "data/maps/Route110/scripts.pory"

# 638 "data/maps/Route110/scripts.pory"
Route110_EventScript_BirchApproachPlayer1::
# 639 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_BIRCH, Route110_Movement_BirchApproachPlayer1
# 640 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 641 "data/maps/Route110/scripts.pory"
	return
# 642 "data/maps/Route110/scripts.pory"

# 643 "data/maps/Route110/scripts.pory"
Route110_EventScript_BirchApproachPlayer2::
# 644 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_BIRCH, Route110_Movement_BirchApproachPlayer2
# 645 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 646 "data/maps/Route110/scripts.pory"
	return
# 647 "data/maps/Route110/scripts.pory"

# 648 "data/maps/Route110/scripts.pory"
Route110_EventScript_BirchApproachPlayer3::
# 649 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_BIRCH, Route110_Movement_BirchApproachPlayer3
# 650 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 651 "data/maps/Route110/scripts.pory"
	return
# 652 "data/maps/Route110/scripts.pory"

# 653 "data/maps/Route110/scripts.pory"
Route110_EventScript_BirchApproachPlayer4::
# 654 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_BIRCH, Route110_Movement_BirchApproachPlayer4
# 655 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 656 "data/maps/Route110/scripts.pory"
	return
# 657 "data/maps/Route110/scripts.pory"

# 658 "data/maps/Route110/scripts.pory"
Route110_EventScript_BirchExit1::
# 659 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_BIRCH, Route110_Movement_BirchExit1
# 660 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 661 "data/maps/Route110/scripts.pory"
	return
# 662 "data/maps/Route110/scripts.pory"

# 663 "data/maps/Route110/scripts.pory"
Route110_EventScript_BirchExit2::
# 664 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_BIRCH, Route110_Movement_BirchExit2
# 665 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 666 "data/maps/Route110/scripts.pory"
	return
# 667 "data/maps/Route110/scripts.pory"

# 668 "data/maps/Route110/scripts.pory"
Route110_EventScript_BirchExit3::
# 669 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_BIRCH, Route110_Movement_BirchExit3
# 670 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 671 "data/maps/Route110/scripts.pory"
	return
# 672 "data/maps/Route110/scripts.pory"

# 673 "data/maps/Route110/scripts.pory"
Route110_EventScript_BirchExit4::
# 674 "data/maps/Route110/scripts.pory"
	applymovement LOCALID_BIRCH, Route110_Movement_BirchExit4
# 675 "data/maps/Route110/scripts.pory"
	waitmovement 0
# 676 "data/maps/Route110/scripts.pory"
	return
# 677 "data/maps/Route110/scripts.pory"

# 678 "data/maps/Route110/scripts.pory"
Route110_Movement_BirchEntrance:
# 679 "data/maps/Route110/scripts.pory"
	walk_down
# 680 "data/maps/Route110/scripts.pory"
	walk_down
# 681 "data/maps/Route110/scripts.pory"
	walk_down
# 682 "data/maps/Route110/scripts.pory"
	step_end
# 683 "data/maps/Route110/scripts.pory"

# 684 "data/maps/Route110/scripts.pory"
Route110_Movement_BirchApproachPlayer1:
# 685 "data/maps/Route110/scripts.pory"
	walk_down
# 686 "data/maps/Route110/scripts.pory"
	walk_left
# 687 "data/maps/Route110/scripts.pory"
	walk_left
# 688 "data/maps/Route110/scripts.pory"
	walk_down
# 689 "data/maps/Route110/scripts.pory"
	step_end
# 690 "data/maps/Route110/scripts.pory"

# 691 "data/maps/Route110/scripts.pory"
Route110_Movement_BirchApproachPlayer2:
# 692 "data/maps/Route110/scripts.pory"
	walk_down
# 693 "data/maps/Route110/scripts.pory"
	walk_left
# 694 "data/maps/Route110/scripts.pory"
	walk_down
# 695 "data/maps/Route110/scripts.pory"
	step_end
# 696 "data/maps/Route110/scripts.pory"

# 697 "data/maps/Route110/scripts.pory"
Route110_Movement_BirchApproachPlayer3:
# 698 "data/maps/Route110/scripts.pory"
	walk_down
# 699 "data/maps/Route110/scripts.pory"
	walk_down
# 700 "data/maps/Route110/scripts.pory"
	step_end
# 701 "data/maps/Route110/scripts.pory"

# 702 "data/maps/Route110/scripts.pory"
Route110_Movement_BirchApproachPlayer4:
# 703 "data/maps/Route110/scripts.pory"
	walk_down
# 704 "data/maps/Route110/scripts.pory"
	walk_right
# 705 "data/maps/Route110/scripts.pory"
	walk_down
# 706 "data/maps/Route110/scripts.pory"
	step_end
# 707 "data/maps/Route110/scripts.pory"

# 708 "data/maps/Route110/scripts.pory"
Route110_Movement_BirchExit1:
# 709 "data/maps/Route110/scripts.pory"
	walk_up
# 710 "data/maps/Route110/scripts.pory"
	walk_up
# 711 "data/maps/Route110/scripts.pory"
	walk_right
# 712 "data/maps/Route110/scripts.pory"
	walk_up
# 713 "data/maps/Route110/scripts.pory"
	walk_up
# 714 "data/maps/Route110/scripts.pory"
	walk_up
# 715 "data/maps/Route110/scripts.pory"
	step_end
# 716 "data/maps/Route110/scripts.pory"

# 717 "data/maps/Route110/scripts.pory"
Route110_Movement_BirchExit2:
# 718 "data/maps/Route110/scripts.pory"
	walk_up
# 719 "data/maps/Route110/scripts.pory"
	walk_up
# 720 "data/maps/Route110/scripts.pory"
	walk_up
# 721 "data/maps/Route110/scripts.pory"
	walk_up
# 722 "data/maps/Route110/scripts.pory"
	walk_up
# 723 "data/maps/Route110/scripts.pory"
	step_end
# 724 "data/maps/Route110/scripts.pory"

# 725 "data/maps/Route110/scripts.pory"
Route110_Movement_BirchExit3:
# 726 "data/maps/Route110/scripts.pory"
	walk_up
# 727 "data/maps/Route110/scripts.pory"
	walk_up
# 728 "data/maps/Route110/scripts.pory"
	walk_up
# 729 "data/maps/Route110/scripts.pory"
	walk_up
# 730 "data/maps/Route110/scripts.pory"
	walk_up
# 731 "data/maps/Route110/scripts.pory"
	step_end
# 732 "data/maps/Route110/scripts.pory"

# 733 "data/maps/Route110/scripts.pory"
Route110_Movement_BirchExit4:
# 734 "data/maps/Route110/scripts.pory"
	walk_up
# 735 "data/maps/Route110/scripts.pory"
	walk_up
# 736 "data/maps/Route110/scripts.pory"
	walk_up
# 737 "data/maps/Route110/scripts.pory"
	walk_up
# 738 "data/maps/Route110/scripts.pory"
	walk_up
# 739 "data/maps/Route110/scripts.pory"
	step_end
# 740 "data/maps/Route110/scripts.pory"

# 741 "data/maps/Route110/scripts.pory"
Route110_Text_WeCantTalkAboutAquaActivities:
# 742 "data/maps/Route110/scripts.pory"
	.string "TEAM AQUA's activities…\n"
# 743 "data/maps/Route110/scripts.pory"
	.string "We can't talk about them yet.$"
# 744 "data/maps/Route110/scripts.pory"

# 745 "data/maps/Route110/scripts.pory"
Route110_Text_KickUpARuckus:
# 746 "data/maps/Route110/scripts.pory"
	.string "I want to get going to SLATEPORT and\n"
# 747 "data/maps/Route110/scripts.pory"
	.string "kick up a ruckus!$"
# 748 "data/maps/Route110/scripts.pory"

# 749 "data/maps/Route110/scripts.pory"
Route110_Text_MyFirstJobInAqua:
# 750 "data/maps/Route110/scripts.pory"
	.string "This is my first job after joining\n"
# 751 "data/maps/Route110/scripts.pory"
	.string "TEAM AQUA. It's a little scary.$"
# 752 "data/maps/Route110/scripts.pory"

# 753 "data/maps/Route110/scripts.pory"
Route110_Text_AquaActionsBringSmiles:
# 754 "data/maps/Route110/scripts.pory"
	.string "TEAM AQUA's actions should bring\n"
# 755 "data/maps/Route110/scripts.pory"
	.string "smiles to people's faces!$"
# 756 "data/maps/Route110/scripts.pory"

# 757 "data/maps/Route110/scripts.pory"
Route110_Text_MayLetsBattle:
# 758 "data/maps/Route110/scripts.pory"
	.string "MAY: Hi, {PLAYER}{KUN}, long time no see!\p"
# 759 "data/maps/Route110/scripts.pory"
	.string "While I was searching for other\n"
# 760 "data/maps/Route110/scripts.pory"
	.string "POKéMON, my POKéMON grew stronger.\p"
# 761 "data/maps/Route110/scripts.pory"
	.string "So…\n"
# 762 "data/maps/Route110/scripts.pory"
	.string "How about a little battle?$"
# 763 "data/maps/Route110/scripts.pory"

# 764 "data/maps/Route110/scripts.pory"
Route110_Text_MayDefeated:
# 765 "data/maps/Route110/scripts.pory"
	.string "Yikes!\n"
# 766 "data/maps/Route110/scripts.pory"
	.string "You're better than I expected!$"
# 767 "data/maps/Route110/scripts.pory"

# 768 "data/maps/Route110/scripts.pory"
Route110_Text_MayTakeThis:
# 769 "data/maps/Route110/scripts.pory"
	.string "MAY: {PLAYER}{KUN}, you've been busy\n"
# 770 "data/maps/Route110/scripts.pory"
	.string "training, too, haven't you?\p"
# 771 "data/maps/Route110/scripts.pory"
	.string "I think you deserve a reward!\n"
# 772 "data/maps/Route110/scripts.pory"
	.string "This is from me!$"
# 773 "data/maps/Route110/scripts.pory"

# 774 "data/maps/Route110/scripts.pory"
Route110_Text_MayExplainItemfinder:
# 775 "data/maps/Route110/scripts.pory"
	.string "MAY: That's an ITEMFINDER.\p"
# 776 "data/maps/Route110/scripts.pory"
	.string "Try it out. If there is an item that's\n"
# 777 "data/maps/Route110/scripts.pory"
	.string "not visible, it emits a sound.\p"
# 778 "data/maps/Route110/scripts.pory"
	.string "Okay, {PLAYER}{KUN}, let's meet again!\p"
# 779 "data/maps/Route110/scripts.pory"
	.string "I know it's a little silly coming from\n"
# 780 "data/maps/Route110/scripts.pory"
	.string "me, but I think you should train a lot\l"
# 781 "data/maps/Route110/scripts.pory"
	.string "harder for the next time.$"
# 782 "data/maps/Route110/scripts.pory"

# 783 "data/maps/Route110/scripts.pory"
Route110_Text_BrendanLetsBattle:
# 784 "data/maps/Route110/scripts.pory"
	.string "BRENDAN: Hey, {PLAYER}.\n"
# 785 "data/maps/Route110/scripts.pory"
	.string "So this is where you were.\l"
# 786 "data/maps/Route110/scripts.pory"
	.string "How's it going?\p"
# 787 "data/maps/Route110/scripts.pory"
	.string "Have you been raising your POKéMON?\n"
# 788 "data/maps/Route110/scripts.pory"
	.string "I'll check for you.$"
# 789 "data/maps/Route110/scripts.pory"

# 790 "data/maps/Route110/scripts.pory"
Route110_Text_BrendanDefeated:
# 791 "data/maps/Route110/scripts.pory"
	.string "Hmm…\n"
# 792 "data/maps/Route110/scripts.pory"
	.string "You're pretty good.$"
# 793 "data/maps/Route110/scripts.pory"

# 794 "data/maps/Route110/scripts.pory"
Route110_Text_BrendanTakeThis:
# 795 "data/maps/Route110/scripts.pory"
	.string "BRENDAN: {PLAYER}, you've trained\n"
# 796 "data/maps/Route110/scripts.pory"
	.string "without me noticing…\p"
# 797 "data/maps/Route110/scripts.pory"
	.string "Good enough!\n"
# 798 "data/maps/Route110/scripts.pory"
	.string "Here, take this.$"
# 799 "data/maps/Route110/scripts.pory"

# 800 "data/maps/Route110/scripts.pory"
Route110_Text_BrendanExplainItemfinder:
# 801 "data/maps/Route110/scripts.pory"
	.string "BRENDAN: That's an ITEMFINDER.\p"
# 802 "data/maps/Route110/scripts.pory"
	.string "Use it to root around for items that\n"
# 803 "data/maps/Route110/scripts.pory"
	.string "aren't visible.\p"
# 804 "data/maps/Route110/scripts.pory"
	.string "If it senses something, it emits\n"
# 805 "data/maps/Route110/scripts.pory"
	.string "a sound.\p"
# 806 "data/maps/Route110/scripts.pory"
	.string "Anyway, I'm off to look for new\n"
# 807 "data/maps/Route110/scripts.pory"
	.string "POKéMON.$"
# 808 "data/maps/Route110/scripts.pory"

# 809 "data/maps/Route110/scripts.pory"
Route110_Text_RideBikeAtFullSpeed:
# 810 "data/maps/Route110/scripts.pory"
	.string "Wouldn't it be great to ride a BIKE\n"
# 811 "data/maps/Route110/scripts.pory"
	.string "at full speed on CYCLING ROAD?$"
# 812 "data/maps/Route110/scripts.pory"

# 813 "data/maps/Route110/scripts.pory"
Route110_Text_HairStreamsBehindMe:
# 814 "data/maps/Route110/scripts.pory"
	.string "How do you like the way my raven-\n"
# 815 "data/maps/Route110/scripts.pory"
	.string "colored hair streams behind me?\p"
# 816 "data/maps/Route110/scripts.pory"
	.string "I grew my hair out just for that.$"
# 817 "data/maps/Route110/scripts.pory"

# 818 "data/maps/Route110/scripts.pory"
Route110_Text_YouGotBikeFromRydel:
# 819 "data/maps/Route110/scripts.pory"
	.string "Oh, hey, you got that BIKE from RYDEL!\p"
# 820 "data/maps/Route110/scripts.pory"
	.string "Oh, it's glaringly obvious.\n"
# 821 "data/maps/Route110/scripts.pory"
	.string "It says right on your bike…\p"
# 822 "data/maps/Route110/scripts.pory"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\n"
# 823 "data/maps/Route110/scripts.pory"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\p"
# 824 "data/maps/Route110/scripts.pory"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\n"
# 825 "data/maps/Route110/scripts.pory"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\p"
# 826 "data/maps/Route110/scripts.pory"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\n"
# 827 "data/maps/Route110/scripts.pory"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\p"
# 828 "data/maps/Route110/scripts.pory"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\n"
# 829 "data/maps/Route110/scripts.pory"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL,\p"
# 830 "data/maps/Route110/scripts.pory"
	.string "RYDEL, RYDEL, RYDEL, RYDEL, RYDEL…\n"
# 831 "data/maps/Route110/scripts.pory"
	.string "That name's everywhere.\p"
# 832 "data/maps/Route110/scripts.pory"
	.string "You should ride it around all over\n"
# 833 "data/maps/Route110/scripts.pory"
	.string "the place--it's good advertising!$"
# 834 "data/maps/Route110/scripts.pory"

# 835 "data/maps/Route110/scripts.pory"
Route110_Text_TwoRoads:
# 836 "data/maps/Route110/scripts.pory"
	.string "The two roads, one above, one below…\p"
# 837 "data/maps/Route110/scripts.pory"
	.string "A road each for people and POKéMON.\n"
# 838 "data/maps/Route110/scripts.pory"
	.string "Perhaps that is right and fair.$"
# 839 "data/maps/Route110/scripts.pory"

# 840 "data/maps/Route110/scripts.pory"
Route110_Text_WalkOnTheLowRoad:
# 841 "data/maps/Route110/scripts.pory"
	.string "I don't have a BIKE, so I'll take\n"
# 842 "data/maps/Route110/scripts.pory"
	.string "a leisurely walk on the low road.$"
# 843 "data/maps/Route110/scripts.pory"

# 844 "data/maps/Route110/scripts.pory"
Route110_Text_BikeTechniques:
# 845 "data/maps/Route110/scripts.pory"
	.string "Learning techniques will make BIKE\n"
# 846 "data/maps/Route110/scripts.pory"
	.string "riding even more fun.\p"
# 847 "data/maps/Route110/scripts.pory"
	.string "There are some places that you can\n"
# 848 "data/maps/Route110/scripts.pory"
	.string "reach only by using a BIKE technique.$"
# 849 "data/maps/Route110/scripts.pory"

# 850 "data/maps/Route110/scripts.pory"
Route110_Text_WhichShouldIChoose:
# 851 "data/maps/Route110/scripts.pory"
	.string "Which should I choose?\p"
# 852 "data/maps/Route110/scripts.pory"
	.string "Make a beeline for MAUVILLE on\n"
# 853 "data/maps/Route110/scripts.pory"
	.string "CYCLING ROAD, or take the low road\l"
# 854 "data/maps/Route110/scripts.pory"
	.string "and look for POKéMON?$"
# 855 "data/maps/Route110/scripts.pory"

# 856 "data/maps/Route110/scripts.pory"
Route110_Text_CyclingChallengeResultSummary:
# 857 "data/maps/Route110/scripts.pory"
	.string "Number of collisions:\n"
# 858 "data/maps/Route110/scripts.pory"
	.string "… … {STR_VAR_1}!\p"
# 859 "data/maps/Route110/scripts.pory"
	.string "Total time:\n"
# 860 "data/maps/Route110/scripts.pory"
	.string "… … {STR_VAR_2}!$"
# 861 "data/maps/Route110/scripts.pory"

# 862 "data/maps/Route110/scripts.pory"
Route110_Text_ChallengeReactionBest:
# 863 "data/maps/Route110/scripts.pory"
	.string "Bravo! Splendid showing!\p"
# 864 "data/maps/Route110/scripts.pory"
	.string "Your love of cycling comes from deep\n"
# 865 "data/maps/Route110/scripts.pory"
	.string "within your heart.\l"
# 866 "data/maps/Route110/scripts.pory"
	.string "You've shaken me to my very soul!$"
# 867 "data/maps/Route110/scripts.pory"

# 868 "data/maps/Route110/scripts.pory"
Route110_Text_ChallengeReactionGood:
# 869 "data/maps/Route110/scripts.pory"
	.string "Your technique is remarkable.\p"
# 870 "data/maps/Route110/scripts.pory"
	.string "I suggest you speed up a bit while\n"
# 871 "data/maps/Route110/scripts.pory"
	.string "still avoiding collisions.$"
# 872 "data/maps/Route110/scripts.pory"

# 873 "data/maps/Route110/scripts.pory"
Route110_Text_ChallengeReactionOk:
# 874 "data/maps/Route110/scripts.pory"
	.string "I would consider you a work in\n"
# 875 "data/maps/Route110/scripts.pory"
	.string "progress.\p"
# 876 "data/maps/Route110/scripts.pory"
	.string "Still, I hope you don't forget the\n"
# 877 "data/maps/Route110/scripts.pory"
	.string "sheer pleasure of cycling.$"
# 878 "data/maps/Route110/scripts.pory"

# 879 "data/maps/Route110/scripts.pory"
Route110_Text_ChallengeReactionBad:
# 880 "data/maps/Route110/scripts.pory"
	.string "My word… Your cycling skills border\n"
# 881 "data/maps/Route110/scripts.pory"
	.string "on terrifying.\p"
# 882 "data/maps/Route110/scripts.pory"
	.string "Most certainly, you need much more\n"
# 883 "data/maps/Route110/scripts.pory"
	.string "practice riding.$"
# 884 "data/maps/Route110/scripts.pory"

# 885 "data/maps/Route110/scripts.pory"
Route110_Text_ChallengeReactionWorst:
# 886 "data/maps/Route110/scripts.pory"
	.string "…I am aghast…\p"
# 887 "data/maps/Route110/scripts.pory"
	.string "You're perhaps not cut out for this\n"
# 888 "data/maps/Route110/scripts.pory"
	.string "unfortunate cycling business.\p"
# 889 "data/maps/Route110/scripts.pory"
	.string "You ought to give serious thought to\n"
# 890 "data/maps/Route110/scripts.pory"
	.string "returning that BIKE to RYDEL.$"
# 891 "data/maps/Route110/scripts.pory"

# 892 "data/maps/Route110/scripts.pory"
Route110_Text_RatedForNumberOfCollisions:
# 893 "data/maps/Route110/scripts.pory"
	.string "This is CYCLING ROAD.\p"
# 894 "data/maps/Route110/scripts.pory"
	.string "If you were to ride from MAUVILLE to\n"
# 895 "data/maps/Route110/scripts.pory"
	.string "SLATEPORT on a MACH BIKE, you would\l"
# 896 "data/maps/Route110/scripts.pory"
	.string "be rated for the number of collisions\l"
# 897 "data/maps/Route110/scripts.pory"
	.string "and your total time.$"
# 898 "data/maps/Route110/scripts.pory"

# 899 "data/maps/Route110/scripts.pory"
Route110_Text_AlwaysAimHigher:
# 900 "data/maps/Route110/scripts.pory"
	.string "Regardless of the results, I count on\n"
# 901 "data/maps/Route110/scripts.pory"
	.string "seeing more challenges from you.\l"
# 902 "data/maps/Route110/scripts.pory"
	.string "Always aim higher!$"
# 903 "data/maps/Route110/scripts.pory"

# 904 "data/maps/Route110/scripts.pory"
Route110_Text_AcroBikesDoNotQualify:
# 905 "data/maps/Route110/scripts.pory"
	.string "On this CYCLING ROAD, those riding\n"
# 906 "data/maps/Route110/scripts.pory"
	.string "MACH BIKES are rated for their number\l"
# 907 "data/maps/Route110/scripts.pory"
	.string "of collisions and their total times.\p"
# 908 "data/maps/Route110/scripts.pory"
	.string "ACRO BIKES do not qualify for rating.\n"
# 909 "data/maps/Route110/scripts.pory"
	.string "They are easy to turn, so it's not fair.$"
# 910 "data/maps/Route110/scripts.pory"

# 911 "data/maps/Route110/scripts.pory"
Route110_Text_SlateportCitySign:
# 912 "data/maps/Route110/scripts.pory"
	.string "ROUTE 110\n"
# 913 "data/maps/Route110/scripts.pory"
	.string "{DOWN_ARROW} SLATEPORT CITY$"
# 914 "data/maps/Route110/scripts.pory"

# 915 "data/maps/Route110/scripts.pory"
Route110_Text_CyclingRoadSign:
# 916 "data/maps/Route110/scripts.pory"
	.string "SEASIDE CYCLING ROAD$"
# 917 "data/maps/Route110/scripts.pory"

# 918 "data/maps/Route110/scripts.pory"
Route110_Text_AquaWasHere:
# 919 "data/maps/Route110/scripts.pory"
	.string "“TEAM AQUA was here!”\p"
# 920 "data/maps/Route110/scripts.pory"
	.string "Someone painted that onto this sign,\n"
# 921 "data/maps/Route110/scripts.pory"
	.string "but then someone else painted over it.\p"
# 922 "data/maps/Route110/scripts.pory"
	.string "“TEAM MAGMA rules!” is what it\n"
# 923 "data/maps/Route110/scripts.pory"
	.string "says now.$"
# 924 "data/maps/Route110/scripts.pory"

# 925 "data/maps/Route110/scripts.pory"
Route110_Text_Route103Sign:
# 926 "data/maps/Route110/scripts.pory"
	.string "ROUTE 110\n"
# 927 "data/maps/Route110/scripts.pory"
	.string "{LEFT_ARROW} ROUTE 103$"
# 928 "data/maps/Route110/scripts.pory"

# 929 "data/maps/Route110/scripts.pory"
Route110_Text_SeasideParkingSign:
# 930 "data/maps/Route110/scripts.pory"
	.string "SEASIDE PARKING$"
# 931 "data/maps/Route110/scripts.pory"

# 932 "data/maps/Route110/scripts.pory"
Route110_Text_MauvilleCitySign:
# 933 "data/maps/Route110/scripts.pory"
	.string "ROUTE 110\n"
# 934 "data/maps/Route110/scripts.pory"
	.string "{UP_ARROW} MAUVILLE CITY$"
# 935 "data/maps/Route110/scripts.pory"

# 936 "data/maps/Route110/scripts.pory"
Route110_Text_TrainerTipsPrlzSleep:
# 937 "data/maps/Route110/scripts.pory"
	.string "TRAINER TIPS\p"
# 938 "data/maps/Route110/scripts.pory"
	.string "The foe can be made helpless by\n"
# 939 "data/maps/Route110/scripts.pory"
	.string "paralyzing it or causing it to sleep.\p"
# 940 "data/maps/Route110/scripts.pory"
	.string "It is an important technique for\n"
# 941 "data/maps/Route110/scripts.pory"
	.string "POKéMON battles.$"
# 942 "data/maps/Route110/scripts.pory"

# 943 "data/maps/Route110/scripts.pory"
Route110_Text_TrainerTipsRegisterItems:
# 944 "data/maps/Route110/scripts.pory"
	.string "TRAINER TIPS\p"
# 945 "data/maps/Route110/scripts.pory"
	.string "The items in the BAG can be reorganized\n"
# 946 "data/maps/Route110/scripts.pory"
	.string "by pressing SELECT.$"
# 947 "data/maps/Route110/scripts.pory"

# 948 "data/maps/Route110/scripts.pory"
Route110_Text_TrickHouseSign:
# 949 "data/maps/Route110/scripts.pory"
	.string "“Three steps {RIGHT_ARROW} and two steps {UP_ARROW}\n"
# 950 "data/maps/Route110/scripts.pory"
	.string "to reach the wondrous TRICK HOUSE.”$"
# 951 "data/maps/Route110/scripts.pory"

# 952 "data/maps/Route110/scripts.pory"
Route110_Text_BestRecord:
# 953 "data/maps/Route110/scripts.pory"
	.string "THE BEST RECORD TO DATE…\p"
# 954 "data/maps/Route110/scripts.pory"
	.string "No. of collisions: {STR_VAR_1}\p"
# 955 "data/maps/Route110/scripts.pory"
	.string "Elapsed time: {STR_VAR_2}$"
# 956 "data/maps/Route110/scripts.pory"

# 957 "data/maps/Route110/scripts.pory"
Route110_Text_ThereIsNoRecord:
# 958 "data/maps/Route110/scripts.pory"
	.string "THE BEST RECORD TO DATE…\p"
# 959 "data/maps/Route110/scripts.pory"
	.string "No one seems to have taken the\n"
# 960 "data/maps/Route110/scripts.pory"
	.string "challenge. There is no record…$"
# 961 "data/maps/Route110/scripts.pory"

# 962 "data/maps/Route110/scripts.pory"
Route110_Text_ImagineSeeingYouHere:
# 963 "data/maps/Route110/scripts.pory"
	.string "PROF. BIRCH: Oh, {PLAYER}{KUN}!\n"
# 964 "data/maps/Route110/scripts.pory"
	.string "Imagine seeing you here!\p"
# 965 "data/maps/Route110/scripts.pory"
	.string "And where might my {RIVAL} be?$"
# 966 "data/maps/Route110/scripts.pory"

# 967 "data/maps/Route110/scripts.pory"
Route110_Text_HeardYouInstallMatchCall:
# 968 "data/maps/Route110/scripts.pory"
	.string "Oh, I see!\n"
# 969 "data/maps/Route110/scripts.pory"
	.string "You two are running separately.\l"
# 970 "data/maps/Route110/scripts.pory"
	.string "Well, that's fine.\p"
# 971 "data/maps/Route110/scripts.pory"
	.string "Oh, yes, I heard that your POKéNAV\n"
# 972 "data/maps/Route110/scripts.pory"
	.string "had the MATCH CALL system installed.\p"
# 973 "data/maps/Route110/scripts.pory"
	.string "Well, then, I should register you in\n"
# 974 "data/maps/Route110/scripts.pory"
	.string "my POKéNAV as well.\p"
# 975 "data/maps/Route110/scripts.pory"
	.string "That way, even when we're apart,\n"
# 976 "data/maps/Route110/scripts.pory"
	.string "I can rate your POKéDEX anytime.\p"
# 977 "data/maps/Route110/scripts.pory"
	.string "… … … … … …$"
# 978 "data/maps/Route110/scripts.pory"

# 979 "data/maps/Route110/scripts.pory"
Route110_Text_RegisteredBirchInPokenav:
# 980 "data/maps/Route110/scripts.pory"
	.string "Registered PROF. BIRCH\n"
# 981 "data/maps/Route110/scripts.pory"
	.string "in the POKéNAV.$"
# 982 "data/maps/Route110/scripts.pory"

# 983 "data/maps/Route110/scripts.pory"
Route110_Text_KeepAnEyeOutForRival:
# 984 "data/maps/Route110/scripts.pory"
	.string "PROF. BIRCH: {PLAYER}{KUN}…\p"
# 985 "data/maps/Route110/scripts.pory"
	.string "Please keep an eye out for my {RIVAL}.\n"
# 986 "data/maps/Route110/scripts.pory"
	.string "… … … … … …\p"
# 987 "data/maps/Route110/scripts.pory"
	.string "Well, I had better get going.\n"
# 988 "data/maps/Route110/scripts.pory"
	.string "See you again, {PLAYER}{KUN}!$"
