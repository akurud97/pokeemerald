# 1 "data/maps/MintakaCity/scripts.pory"

# 2 "data/maps/MintakaCity/scripts.pory"
MintakaCity_MapScripts::
# 3 "data/maps/MintakaCity/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, MintakaCity_HideAcolyteActors
# 4 "data/maps/MintakaCity/scripts.pory"
	.byte 0
# 5 "data/maps/MintakaCity/scripts.pory"

# 6 "data/maps/MintakaCity/scripts.pory"
MintakaCity_HideAcolyteActors:
# 7 "data/maps/MintakaCity/scripts.pory"
	setflag FLAG_HIDE_MINTAKA_ACOLYTE
# 8 "data/maps/MintakaCity/scripts.pory"
	setflag FLAG_HIDE_MINTAKA_CARGO_WORKER
# 9 "data/maps/MintakaCity/scripts.pory"
	end

MintakaCity_EventScript_Object1::
# 13 "data/maps/MintakaCity/scripts.pory"
	lock
# 14 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_Object1, MSGBOX_DEFAULT
# 15 "data/maps/MintakaCity/scripts.pory"
	release
	end


MintakaCity_EventScript_Object2::
# 20 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_Object2, MSGBOX_NPC
	end


MintakaCity_EventScript_Object3::
# 25 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_Object3, MSGBOX_NPC
	end


MintakaCity_EventScript_Object5::
# 30 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_Object5, MSGBOX_NPC
	end


MintakaCity_EventScript_Object6::
# 35 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_Object6, MSGBOX_NPC
	end


MintakaCity_EventScript_Object7::
# 40 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_Object7, MSGBOX_NPC
	end


MintakaCity_EventScript_Object8::
# 45 "data/maps/MintakaCity/scripts.pory"
	lock
# 46 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_Object8, MSGBOX_DEFAULT
# 47 "data/maps/MintakaCity/scripts.pory"
	release
	end


MintakaCity_EventScript_Object9::
# 52 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_Object9, MSGBOX_NPC
	end


MintakaCity_EventScript_Object10::
# 57 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_Object10, MSGBOX_NPC
	end


MintakaCity_EventScript_Object11::
# 62 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_Object11, MSGBOX_NPC
	end


MintakaCity_EventScript_Object12::
# 67 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_Object12, MSGBOX_NPC
	end


MintakaCity_EventScript_Object14::
# 72 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_Object14, MSGBOX_NPC
	end


MintakaCity_EventScript_Object15::
# 77 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_Object15, MSGBOX_NPC
	end


MintakaCity_EventScript_Object16::
# 82 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_Object16, MSGBOX_NPC
	end


# 153 "data/maps/MintakaCity/scripts.pory"

# 154 "data/maps/MintakaCity/scripts.pory"
@ Both coordinate approaches use VAR_MINTAKA_ACOLYTE_EVENT. A loss blackouts
# 155 "data/maps/MintakaCity/scripts.pory"
@ normally and leaves the scene available; only a completed rescue consumes it.
# 156 "data/maps/MintakaCity/scripts.pory"
MintakaCity_EventScript_AcolyteWest::
# 157 "data/maps/MintakaCity/scripts.pory"
	lockall
# 158 "data/maps/MintakaCity/scripts.pory"
	playbgm MUS_BW_PLASMA, FALSE
# 159 "data/maps/MintakaCity/scripts.pory"
	setspeaker SP_NAME_NONE
# 160 "data/maps/MintakaCity/scripts.pory"
	getplayerxy VAR_0x8004, VAR_0x8005
# 161 "data/maps/MintakaCity/scripts.pory"
	setobjectxyperm LOCALID_MINTAKA_ACOLYTE, 34, 29
# 162 "data/maps/MintakaCity/scripts.pory"
	setobjectxyperm LOCALID_MINTAKA_CARGO_WORKER, 35, 29
# 163 "data/maps/MintakaCity/scripts.pory"
	call MintakaCity_AcolyteSpawnAndCry
# 164 "data/maps/MintakaCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, MintakaCity_RunDown3
# 165 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 166 "data/maps/MintakaCity/scripts.pory"
	goto_if_eq VAR_0x8004, 24, MintakaCity_WestFrom24
# 167 "data/maps/MintakaCity/scripts.pory"
	goto_if_eq VAR_0x8004, 25, MintakaCity_WestFrom25
# 168 "data/maps/MintakaCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, MintakaCity_RunRight6
# 169 "data/maps/MintakaCity/scripts.pory"
	goto MintakaCity_WestArrived
# 170 "data/maps/MintakaCity/scripts.pory"
MintakaCity_WestFrom24:
# 171 "data/maps/MintakaCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, MintakaCity_RunRight8
# 172 "data/maps/MintakaCity/scripts.pory"
	goto MintakaCity_WestArrived
# 173 "data/maps/MintakaCity/scripts.pory"
MintakaCity_WestFrom25:
# 174 "data/maps/MintakaCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, MintakaCity_RunRight7
# 175 "data/maps/MintakaCity/scripts.pory"
MintakaCity_WestArrived:
# 176 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 177 "data/maps/MintakaCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
# 178 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 179 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_CargoHelp, MSGBOX_DEFAULT
# 180 "data/maps/MintakaCity/scripts.pory"
	applymovement LOCALID_MINTAKA_ACOLYTE, Common_Movement_FaceLeft
# 181 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 182 "data/maps/MintakaCity/scripts.pory"
	call MintakaCity_AcolyteBattle
# 183 "data/maps/MintakaCity/scripts.pory"
	applymovement LOCALID_MINTAKA_ACOLYTE, MintakaCity_WalkDown1
# 184 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 185 "data/maps/MintakaCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
# 186 "data/maps/MintakaCity/scripts.pory"
	applymovement LOCALID_MINTAKA_ACOLYTE, MintakaCity_WalkLeft3
# 187 "data/maps/MintakaCity/scripts.pory"
	waitmovement LOCALID_MINTAKA_ACOLYTE
# 188 "data/maps/MintakaCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceLeft
# 189 "data/maps/MintakaCity/scripts.pory"
	applymovement LOCALID_MINTAKA_ACOLYTE, MintakaCity_WestAcolyteExit
# 190 "data/maps/MintakaCity/scripts.pory"
	waitmovement LOCALID_MINTAKA_ACOLYTE
# 191 "data/maps/MintakaCity/scripts.pory"
	removeobject LOCALID_MINTAKA_ACOLYTE
# 192 "data/maps/MintakaCity/scripts.pory"
	fadedefaultbgm
# 193 "data/maps/MintakaCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceRight
# 194 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 195 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_CargoThanks, MSGBOX_DEFAULT
# 196 "data/maps/MintakaCity/scripts.pory"
	closemessage
# 197 "data/maps/MintakaCity/scripts.pory"
	applymovement LOCALID_MINTAKA_CARGO_WORKER, MintakaCity_WalkRight6
# 198 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 199 "data/maps/MintakaCity/scripts.pory"
	goto MintakaCity_AcolyteFinish
# 200 "data/maps/MintakaCity/scripts.pory"

# 201 "data/maps/MintakaCity/scripts.pory"
MintakaCity_EventScript_AcolyteNorth::
# 202 "data/maps/MintakaCity/scripts.pory"
	lockall
# 203 "data/maps/MintakaCity/scripts.pory"
	playbgm MUS_BW_PLASMA, FALSE
# 204 "data/maps/MintakaCity/scripts.pory"
	setspeaker SP_NAME_NONE
# 205 "data/maps/MintakaCity/scripts.pory"
	getplayerxy VAR_0x8004, VAR_0x8005
# 206 "data/maps/MintakaCity/scripts.pory"
	setobjectxyperm LOCALID_MINTAKA_ACOLYTE, 40, 17
# 207 "data/maps/MintakaCity/scripts.pory"
	setobjectxyperm LOCALID_MINTAKA_CARGO_WORKER, 41, 17
# 208 "data/maps/MintakaCity/scripts.pory"
	call MintakaCity_AcolyteSpawnAndCry
# 209 "data/maps/MintakaCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, MintakaCity_RunDown4
# 210 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 211 "data/maps/MintakaCity/scripts.pory"
	goto_if_eq VAR_0x8004, 38, MintakaCity_NorthFrom38
# 212 "data/maps/MintakaCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, MintakaCity_RunRight1
# 213 "data/maps/MintakaCity/scripts.pory"
	goto MintakaCity_NorthTurnDown
# 214 "data/maps/MintakaCity/scripts.pory"
MintakaCity_NorthFrom38:
# 215 "data/maps/MintakaCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, MintakaCity_RunRight2
# 216 "data/maps/MintakaCity/scripts.pory"
MintakaCity_NorthTurnDown:
# 217 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 218 "data/maps/MintakaCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, MintakaCity_RunDown2
# 219 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 220 "data/maps/MintakaCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_FaceDown
# 221 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 222 "data/maps/MintakaCity/scripts.pory"
	applymovement LOCALID_MINTAKA_CARGO_WORKER, Common_Movement_FaceUp
# 223 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 224 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_CargoHelp, MSGBOX_DEFAULT
# 225 "data/maps/MintakaCity/scripts.pory"
	applymovement LOCALID_MINTAKA_ACOLYTE, Common_Movement_FaceUp
# 226 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 227 "data/maps/MintakaCity/scripts.pory"
	call MintakaCity_AcolyteBattle
# 228 "data/maps/MintakaCity/scripts.pory"
	applymovement LOCALID_MINTAKA_ACOLYTE, MintakaCity_WalkDown7
# 229 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 230 "data/maps/MintakaCity/scripts.pory"
	removeobject LOCALID_MINTAKA_ACOLYTE
# 231 "data/maps/MintakaCity/scripts.pory"
	fadedefaultbgm
# 232 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_CargoThanks, MSGBOX_DEFAULT
# 233 "data/maps/MintakaCity/scripts.pory"
	closemessage
# 234 "data/maps/MintakaCity/scripts.pory"
	applymovement LOCALID_MINTAKA_CARGO_WORKER, MintakaCity_NorthWorkerExit
# 235 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 236 "data/maps/MintakaCity/scripts.pory"
	opendoor 47, 12
# 237 "data/maps/MintakaCity/scripts.pory"
	waitdooranim
# 238 "data/maps/MintakaCity/scripts.pory"
	applymovement LOCALID_MINTAKA_CARGO_WORKER, MintakaCity_WalkUp1
# 239 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 240 "data/maps/MintakaCity/scripts.pory"
	removeobject LOCALID_MINTAKA_CARGO_WORKER
# 241 "data/maps/MintakaCity/scripts.pory"
	closedoor 47, 12
# 242 "data/maps/MintakaCity/scripts.pory"
	waitdooranim
# 243 "data/maps/MintakaCity/scripts.pory"
	goto MintakaCity_AcolyteFinish
# 244 "data/maps/MintakaCity/scripts.pory"

# 245 "data/maps/MintakaCity/scripts.pory"
MintakaCity_AcolyteSpawnAndCry:
# 246 "data/maps/MintakaCity/scripts.pory"
	clearflag FLAG_HIDE_MINTAKA_ACOLYTE
# 247 "data/maps/MintakaCity/scripts.pory"
	clearflag FLAG_HIDE_MINTAKA_CARGO_WORKER
# 248 "data/maps/MintakaCity/scripts.pory"
	addobject LOCALID_MINTAKA_ACOLYTE
# 249 "data/maps/MintakaCity/scripts.pory"
	addobject LOCALID_MINTAKA_CARGO_WORKER
# 250 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_CargoCry, MSGBOX_DEFAULT
# 251 "data/maps/MintakaCity/scripts.pory"
	closemessage
# 252 "data/maps/MintakaCity/scripts.pory"
	@ Finish the recall before any scripted movement can interrupt it.
# 253 "data/maps/MintakaCity/scripts.pory"
	hidefollower
# 254 "data/maps/MintakaCity/scripts.pory"
	applymovement LOCALID_MINTAKA_ACOLYTE, Common_Movement_FaceRight
# 255 "data/maps/MintakaCity/scripts.pory"
	applymovement LOCALID_MINTAKA_CARGO_WORKER, Common_Movement_FaceLeft
# 256 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 257 "data/maps/MintakaCity/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_ExclamationMark
# 258 "data/maps/MintakaCity/scripts.pory"
	waitmovement 0
# 259 "data/maps/MintakaCity/scripts.pory"
	return
# 260 "data/maps/MintakaCity/scripts.pory"

# 261 "data/maps/MintakaCity/scripts.pory"
MintakaCity_AcolyteBattle:
# 262 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_AcolyteChallenge, MSGBOX_DEFAULT
# 263 "data/maps/MintakaCity/scripts.pory"
	closemessage
# 264 "data/maps/MintakaCity/scripts.pory"
	trainerbattle_no_intro TRAINER_MINTAKA_ACOLYTE, NULL
# 265 "data/maps/MintakaCity/scripts.pory"
	playbgm MUS_BW_PLASMA, FALSE
# 266 "data/maps/MintakaCity/scripts.pory"
	setspeaker SP_NAME_NONE
# 267 "data/maps/MintakaCity/scripts.pory"
	msgbox MintakaCity_Text_AcolyteThreat, MSGBOX_DEFAULT
# 268 "data/maps/MintakaCity/scripts.pory"
	closemessage
# 269 "data/maps/MintakaCity/scripts.pory"
	return
# 270 "data/maps/MintakaCity/scripts.pory"

# 271 "data/maps/MintakaCity/scripts.pory"
MintakaCity_AcolyteFinish:
# 272 "data/maps/MintakaCity/scripts.pory"
	removeobject LOCALID_MINTAKA_CARGO_WORKER
# 273 "data/maps/MintakaCity/scripts.pory"
	setflag FLAG_HIDE_MINTAKA_ACOLYTE
# 274 "data/maps/MintakaCity/scripts.pory"
	setflag FLAG_HIDE_MINTAKA_CARGO_WORKER
# 275 "data/maps/MintakaCity/scripts.pory"
	setvar VAR_MINTAKA_ACOLYTE_EVENT, 1
# 276 "data/maps/MintakaCity/scripts.pory"
	releaseall
# 277 "data/maps/MintakaCity/scripts.pory"
	end
# 278 "data/maps/MintakaCity/scripts.pory"

# 279 "data/maps/MintakaCity/scripts.pory"
MintakaCity_RunDown3:
# 280 "data/maps/MintakaCity/scripts.pory"
	player_run_down
# 281 "data/maps/MintakaCity/scripts.pory"
	player_run_down
# 282 "data/maps/MintakaCity/scripts.pory"
	player_run_down
# 283 "data/maps/MintakaCity/scripts.pory"
	step_end
# 284 "data/maps/MintakaCity/scripts.pory"

# 285 "data/maps/MintakaCity/scripts.pory"
MintakaCity_RunDown4:
# 286 "data/maps/MintakaCity/scripts.pory"
	player_run_down
# 287 "data/maps/MintakaCity/scripts.pory"
	player_run_down
# 288 "data/maps/MintakaCity/scripts.pory"
	player_run_down
# 289 "data/maps/MintakaCity/scripts.pory"
	player_run_down
# 290 "data/maps/MintakaCity/scripts.pory"
	step_end
# 291 "data/maps/MintakaCity/scripts.pory"

# 292 "data/maps/MintakaCity/scripts.pory"
MintakaCity_RunDown2:
# 293 "data/maps/MintakaCity/scripts.pory"
	player_run_down
# 294 "data/maps/MintakaCity/scripts.pory"
	player_run_down
# 295 "data/maps/MintakaCity/scripts.pory"
	step_end
# 296 "data/maps/MintakaCity/scripts.pory"

# 297 "data/maps/MintakaCity/scripts.pory"
MintakaCity_RunRight1:
# 298 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 299 "data/maps/MintakaCity/scripts.pory"
	step_end
# 300 "data/maps/MintakaCity/scripts.pory"

# 301 "data/maps/MintakaCity/scripts.pory"
MintakaCity_RunRight2:
# 302 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 303 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 304 "data/maps/MintakaCity/scripts.pory"
	step_end
# 305 "data/maps/MintakaCity/scripts.pory"

# 306 "data/maps/MintakaCity/scripts.pory"
MintakaCity_RunRight6:
# 307 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 308 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 309 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 310 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 311 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 312 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 313 "data/maps/MintakaCity/scripts.pory"
	step_end
# 314 "data/maps/MintakaCity/scripts.pory"

# 315 "data/maps/MintakaCity/scripts.pory"
MintakaCity_RunRight7:
# 316 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 317 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 318 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 319 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 320 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 321 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 322 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 323 "data/maps/MintakaCity/scripts.pory"
	step_end
# 324 "data/maps/MintakaCity/scripts.pory"

# 325 "data/maps/MintakaCity/scripts.pory"
MintakaCity_RunRight8:
# 326 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 327 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 328 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 329 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 330 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 331 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 332 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 333 "data/maps/MintakaCity/scripts.pory"
	player_run_right
# 334 "data/maps/MintakaCity/scripts.pory"
	step_end
# 335 "data/maps/MintakaCity/scripts.pory"

# 336 "data/maps/MintakaCity/scripts.pory"
MintakaCity_WalkDown1:
# 337 "data/maps/MintakaCity/scripts.pory"
	walk_down
# 338 "data/maps/MintakaCity/scripts.pory"
	step_end
# 339 "data/maps/MintakaCity/scripts.pory"

# 340 "data/maps/MintakaCity/scripts.pory"
MintakaCity_WalkLeft3:
# 341 "data/maps/MintakaCity/scripts.pory"
	walk_left
# 342 "data/maps/MintakaCity/scripts.pory"
	walk_left
# 343 "data/maps/MintakaCity/scripts.pory"
	walk_left
# 344 "data/maps/MintakaCity/scripts.pory"
	step_end
# 345 "data/maps/MintakaCity/scripts.pory"

# 346 "data/maps/MintakaCity/scripts.pory"
MintakaCity_WestAcolyteExit:
# 347 "data/maps/MintakaCity/scripts.pory"
	walk_left
# 348 "data/maps/MintakaCity/scripts.pory"
	walk_left
# 349 "data/maps/MintakaCity/scripts.pory"
	walk_left
# 350 "data/maps/MintakaCity/scripts.pory"
	walk_left
# 351 "data/maps/MintakaCity/scripts.pory"
	walk_left
# 352 "data/maps/MintakaCity/scripts.pory"
	walk_left
# 353 "data/maps/MintakaCity/scripts.pory"
	walk_down
# 354 "data/maps/MintakaCity/scripts.pory"
	walk_down
# 355 "data/maps/MintakaCity/scripts.pory"
	walk_down
# 356 "data/maps/MintakaCity/scripts.pory"
	walk_down
# 357 "data/maps/MintakaCity/scripts.pory"
	walk_down
# 358 "data/maps/MintakaCity/scripts.pory"
	walk_down
# 359 "data/maps/MintakaCity/scripts.pory"
	step_end
# 360 "data/maps/MintakaCity/scripts.pory"

# 361 "data/maps/MintakaCity/scripts.pory"
MintakaCity_WalkRight6:
# 362 "data/maps/MintakaCity/scripts.pory"
	walk_right
# 363 "data/maps/MintakaCity/scripts.pory"
	walk_right
# 364 "data/maps/MintakaCity/scripts.pory"
	walk_right
# 365 "data/maps/MintakaCity/scripts.pory"
	walk_right
# 366 "data/maps/MintakaCity/scripts.pory"
	walk_right
# 367 "data/maps/MintakaCity/scripts.pory"
	walk_right
# 368 "data/maps/MintakaCity/scripts.pory"
	step_end
# 369 "data/maps/MintakaCity/scripts.pory"

# 370 "data/maps/MintakaCity/scripts.pory"
MintakaCity_WalkDown7:
# 371 "data/maps/MintakaCity/scripts.pory"
	walk_down
# 372 "data/maps/MintakaCity/scripts.pory"
	walk_down
# 373 "data/maps/MintakaCity/scripts.pory"
	walk_down
# 374 "data/maps/MintakaCity/scripts.pory"
	walk_down
# 375 "data/maps/MintakaCity/scripts.pory"
	walk_down
# 376 "data/maps/MintakaCity/scripts.pory"
	walk_down
# 377 "data/maps/MintakaCity/scripts.pory"
	walk_down
# 378 "data/maps/MintakaCity/scripts.pory"
	step_end
# 379 "data/maps/MintakaCity/scripts.pory"

# 380 "data/maps/MintakaCity/scripts.pory"
MintakaCity_NorthWorkerExit:
# 381 "data/maps/MintakaCity/scripts.pory"
	walk_up
# 382 "data/maps/MintakaCity/scripts.pory"
	walk_up
# 383 "data/maps/MintakaCity/scripts.pory"
	walk_up
# 384 "data/maps/MintakaCity/scripts.pory"
	walk_up
# 385 "data/maps/MintakaCity/scripts.pory"
	walk_right
# 386 "data/maps/MintakaCity/scripts.pory"
	walk_right
# 387 "data/maps/MintakaCity/scripts.pory"
	walk_right
# 388 "data/maps/MintakaCity/scripts.pory"
	walk_right
# 389 "data/maps/MintakaCity/scripts.pory"
	walk_right
# 390 "data/maps/MintakaCity/scripts.pory"
	walk_right
# 391 "data/maps/MintakaCity/scripts.pory"
	step_end
# 392 "data/maps/MintakaCity/scripts.pory"

# 393 "data/maps/MintakaCity/scripts.pory"
MintakaCity_WalkUp1:
# 394 "data/maps/MintakaCity/scripts.pory"
	walk_up
# 395 "data/maps/MintakaCity/scripts.pory"
	step_end

MintakaCity_Text_Object1::
# 86 "data/maps/MintakaCity/scripts.pory"
	.string "You forgot your swimsuit? It’s okay,\n"
	.string "I’ll just buy you a new one.$"

MintakaCity_Text_Object2::
# 91 "data/maps/MintakaCity/scripts.pory"
	.string "Careful, kid. The warehouse can be\n"
	.string "dangerous. Especially if the guys in\l"
	.string "there are bored and itching for a fight.$"

MintakaCity_Text_Object3::
# 97 "data/maps/MintakaCity/scripts.pory"
	.string "Vigoo!$"

MintakaCity_Text_Object5::
# 101 "data/maps/MintakaCity/scripts.pory"
	.string "I love the cool breeze this city gets\n"
	.string "from the lake.$"

MintakaCity_Text_Object6::
# 106 "data/maps/MintakaCity/scripts.pory"
	.string "I’m not doing anything shady! This\n"
	.string "cargo is totally legit!$"

MintakaCity_Text_Object7::
# 111 "data/maps/MintakaCity/scripts.pory"
	.string "I’m going to be a Pokémon when I\n"
	.string "grow up!$"

MintakaCity_Text_Object8::
# 116 "data/maps/MintakaCity/scripts.pory"
	.string "Will you buy me an icecream too?\n"
	.string "And a soda? And…$"

MintakaCity_Text_Object9::
# 121 "data/maps/MintakaCity/scripts.pory"
	.string "From up here, you can watch the boats\n"
	.string "sail in and out of the harbour.$"

MintakaCity_Text_Object10::
# 126 "data/maps/MintakaCity/scripts.pory"
	.string "Lake Hyades is so big, it feels like a\n"
	.string "sea. The horizon seems to stretch on\l"
	.string "endlessly.$"

MintakaCity_Text_Object11::
# 132 "data/maps/MintakaCity/scripts.pory"
	.string "The water is really cold…$"

MintakaCity_Text_Object12::
# 136 "data/maps/MintakaCity/scripts.pory"
	.string "I love working so close to the water.$"

MintakaCity_Text_Object14::
# 140 "data/maps/MintakaCity/scripts.pory"
	.string "Come on, psyche yourself up, Mankey!\n"
	.string "We can take on this gym.$"

MintakaCity_Text_Object15::
# 145 "data/maps/MintakaCity/scripts.pory"
	.string "Man-keyyy!$"

MintakaCity_Text_Object16::
# 149 "data/maps/MintakaCity/scripts.pory"
	.string "Hey… You’re blocking my sun…$"

MintakaCity_Text_CargoCry::
# 398 "data/maps/MintakaCity/scripts.pory"
	.string "Help! Somebody with a Pokémon!\p"
	.string "Help me!$"

MintakaCity_Text_CargoHelp::
# 402 "data/maps/MintakaCity/scripts.pory"
	.string "Hey, are you a Pokémon trainer?\p"
	.string "This guy is a thief! Help me!$"

MintakaCity_Text_AcolyteChallenge::
# 406 "data/maps/MintakaCity/scripts.pory"
	.string "Stay out of this, kid!\p"
	.string "Oh, you think you're tough? Fine!$"

MintakaCity_Text_AcolyteThreat::
# 410 "data/maps/MintakaCity/scripts.pory"
	.string "Tch..The boss won't be happy about\n"
	.string "this...\p"
	.string "That's okay! It's only a minor setback.\p"
	.string "Kid, I don't know who you think you are,\n"
	.string "but today you've made an enemy of the\l"
	.string "Astral Path.\p"
	.string "Don't get in our way again. It won't go\n"
	.string "well for you.$"

MintakaCity_Text_CargoThanks::
# 414 "data/maps/MintakaCity/scripts.pory"
	.string "Thanks, kid. That guy was really weird.\n"
	.string "What is the Astral Path?\p"
	.string "He was trying to steal my keys to our\n"
	.string "cargo truck. There's a lot of valuable\l"
	.string "stuff in there.\p"
	.string "I work at the harbour warehouse. Hey,\n"
	.string "come see me in there and I'll give you a\l"
	.string "little reward. Later!$"
