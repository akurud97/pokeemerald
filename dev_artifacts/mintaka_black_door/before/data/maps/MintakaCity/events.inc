@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/MintakaCity/map.json
@

	.align 2

MintakaCity_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_RICH_BOY, 22, 30, 3, MOVEMENT_TYPE_FACE_RIGHT, 0, 0, TRAINER_TYPE_NONE, 0, MintakaCity_EventScript_Object1, 0
	object_event 2, OBJ_EVENT_GFX_SAILOR, 50, 13, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 1, TRAINER_TYPE_NONE, 0, MintakaCity_EventScript_Object2, 0
	object_event 3, OBJ_EVENT_GFX_TRUCK, 53, 14, 3, MOVEMENT_TYPE_NONE, 0, 0, TRAINER_TYPE_NONE, 0, NULL, 0
	object_event 4, OBJ_EVENT_GFX_WOMAN_3, 19, 17, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 2, TRAINER_TYPE_NONE, 0, MintakaCity_EventScript_Object5, 0
	object_event 5, OBJ_EVENT_GFX_AQUA_MEMBER_F, 46, 20, 3, MOVEMENT_TYPE_FACE_RIGHT, 0, 1, TRAINER_TYPE_NONE, 0, MintakaCity_EventScript_Object6, 0
	object_event 6, OBJ_EVENT_GFX_LITTLE_BOY, 41, 7, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, MintakaCity_EventScript_Object7, 0
	object_event 7, OBJ_EVENT_GFX_GIRL_2, 23, 30, 3, MOVEMENT_TYPE_FACE_LEFT, 0, 0, TRAINER_TYPE_NONE, 0, MintakaCity_EventScript_Object8, 0
	object_event 8, OBJ_EVENT_GFX_EXPERT_F, 32, 11, 3, MOVEMENT_TYPE_WANDER_DOWN_AND_UP, 0, 2, TRAINER_TYPE_NONE, 0, MintakaCity_EventScript_Object9, 0
	object_event 9, OBJ_EVENT_GFX_SCOTT, 36, 36, 0, MOVEMENT_TYPE_FACE_RIGHT, 1, 2, TRAINER_TYPE_NONE, 0, MintakaCity_EventScript_Object10, 0
	object_event 10, OBJ_EVENT_GFX_TUBER_M, 24, 36, 3, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, MintakaCity_EventScript_Object11, 0
	object_event 11, OBJ_EVENT_GFX_SS_TIDAL, 55, 8, 0, MOVEMENT_TYPE_FACE_LEFT, 0, 0, TRAINER_TYPE_NONE, 0, NULL, 0
	object_event 12, OBJ_EVENT_GFX_GIRL_3, 22, 7, 0, MOVEMENT_TYPE_FACE_LEFT, 0, 0, TRAINER_TYPE_NONE, 0, MintakaCity_EventScript_Object14, 0
	object_event 13, OBJ_EVENT_GFX_SPECIES(MANKEY), 21, 7, 0, MOVEMENT_TYPE_WALK_IN_PLACE_RIGHT, 0, 0, TRAINER_TYPE_NONE, 0, MintakaCity_EventScript_Object15, 0
	object_event 14, OBJ_EVENT_GFX_POKEFAN_M, 32, 40, 0, MOVEMENT_TYPE_NONE, 0, 0, TRAINER_TYPE_NONE, 0, MintakaCity_EventScript_Object16, 0
	object_event 15, OBJ_EVENT_GFX_ACOLYTE_M, 34, 29, 3, MOVEMENT_TYPE_FACE_RIGHT, 0, 0, TRAINER_TYPE_NONE, 0, NULL, FLAG_HIDE_MINTAKA_ACOLYTE
	object_event 16, OBJ_EVENT_GFX_WALLY, 35, 29, 3, MOVEMENT_TYPE_FACE_LEFT, 0, 0, TRAINER_TYPE_NONE, 0, NULL, FLAG_HIDE_MINTAKA_CARGO_WORKER

MintakaCity_MapWarps:
	warp_def 47, 12, 0, 0, MAP_WAREHOUSE_F1
	warp_def 35, 5, 0, 0, MAP_MINTAKA_HOUSE4
	warp_def 25, 21, 0, 0, MAP_MINTAKA_HOUSE3
	warp_def 16, 7, 0, 0, MAP_MINTAKA_HOUSE1
	warp_def 22, 14, 0, 0, MAP_MINTAKA_HOUSE2
	warp_def 14, 14, 0, 0, MAP_MINTAKA_CENTER
	warp_def 27, 14, 0, 0, MAP_MINTAKA_MART
	warp_def 26, 7, 0, 0, MAP_MINTAKA_GYM
	warp_def 35, 23, 0, 0, MAP_MINTAKA_HOUSE5
	warp_def 32, 35, 0, 1, MAP_BOATHOUSE

MintakaCity_MapCoordEvents:
	coord_event 24, 26, 0, VAR_MINTAKA_ACOLYTE_EVENT, 0, MintakaCity_EventScript_AcolyteWest
	coord_event 25, 26, 0, VAR_MINTAKA_ACOLYTE_EVENT, 0, MintakaCity_EventScript_AcolyteWest
	coord_event 26, 26, 0, VAR_MINTAKA_ACOLYTE_EVENT, 0, MintakaCity_EventScript_AcolyteWest
	coord_event 38, 9, 0, VAR_MINTAKA_ACOLYTE_EVENT, 0, MintakaCity_EventScript_AcolyteNorth
	coord_event 39, 9, 0, VAR_MINTAKA_ACOLYTE_EVENT, 0, MintakaCity_EventScript_AcolyteNorth

MintakaCity_MapBGEvents:
	bg_sign_event 9, 10, 0, BG_EVENT_PLAYER_FACING_ANY, NULL
	bg_sign_event 29, 7, 0, BG_EVENT_PLAYER_FACING_ANY, NULL
	bg_sign_event 42, 12, 0, BG_EVENT_PLAYER_FACING_ANY, NULL
	bg_sign_event 29, 35, 0, BG_EVENT_PLAYER_FACING_ANY, NULL

MintakaCity_MapEvents::
	map_events MintakaCity_ObjectEvents, MintakaCity_MapWarps, MintakaCity_MapCoordEvents, MintakaCity_MapBGEvents

