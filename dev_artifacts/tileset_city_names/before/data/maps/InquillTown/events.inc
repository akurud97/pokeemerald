@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/InquillTown/map.json
@

	.align 2

InquillTown_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_WOMAN_2, 15, 18, 3, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 1, 0, TRAINER_TYPE_NONE, 0, InquillTown_EventScript_Object1, 0
	object_event 2, OBJ_EVENT_GFX_HEX_MANIAC, 19, 10, 3, MOVEMENT_TYPE_WANDER_AROUND, 2, 2, TRAINER_TYPE_NONE, 0, InquillTown_EventScript_Object2, 0
	object_event 3, OBJ_EVENT_GFX_OLD_MAN, 27, 16, 3, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, InquillTown_EventScript_Object3, 0
	object_event 4, OBJ_EVENT_GFX_FAT_MAN, 7, 14, 3, MOVEMENT_TYPE_FACE_UP, 0, 0, TRAINER_TYPE_NONE, 0, InquillTown_EventScript_Object4, 0
	object_event 5, OBJ_EVENT_GFX_LITTLE_GIRL, 8, 28, 0, MOVEMENT_TYPE_WANDER_DOWN_AND_UP, 0, 3, TRAINER_TYPE_NONE, 0, InquillTown_EventScript_Object5, 0
	object_event 6, OBJ_EVENT_GFX_MART_EMPLOYEE, 20, 25, 0, MOVEMENT_TYPE_FACE_DOWN_UP_AND_LEFT, 0, 0, TRAINER_TYPE_NONE, 0, InquillTown_EventScript_Object6, 0
	object_event 7, OBJ_EVENT_GFX_BERRY_TREE, 4, 25, 3, MOVEMENT_TYPE_BERRY_TREE_GROWTH, 0, 0, TRAINER_TYPE_NONE, BERRY_TREE_ROUTE_103_CHERI_1, BerryTreeScript, 0
	object_event 8, OBJ_EVENT_GFX_BERRY_TREE, 4, 26, 3, MOVEMENT_TYPE_BERRY_TREE_GROWTH, 0, 0, TRAINER_TYPE_NONE, BERRY_TREE_ROUTE_103_CHERI_2, BerryTreeScript, 0
	object_event 9, OBJ_EVENT_GFX_BERRY_TREE, 4, 27, 3, MOVEMENT_TYPE_BERRY_TREE_GROWTH, 0, 0, TRAINER_TYPE_NONE, BERRY_TREE_ROUTE_104_CHERI_1, BerryTreeScript, 0

InquillTown_MapWarps:
	warp_def 9, 5, 0, 0, MAP_INQUILL_HOUSE1
	warp_def 33, 13, 0, 0, MAP_INQUILL_HOUSE2
	warp_def 4, 13, 0, 0, MAP_INQUILL_HOUSE3
	warp_def 13, 15, 0, 0, MAP_FLOWER_SHOP
	warp_def 18, 5, 0, 0, MAP_INQUILL_HOUSE4
	warp_def 5, 20, 0, 0, MAP_INQUILL_HOUSE5
	warp_def 22, 16, 0, 0, MAP_INQUILL_CENTER
	warp_def 13, 24, 0, 0, MAP_INQUILL_MART

InquillTown_MapBGEvents:
	bg_sign_event 11, 16, 0, BG_EVENT_PLAYER_FACING_ANY, NULL
	bg_sign_event 22, 8, 0, BG_EVENT_PLAYER_FACING_ANY, NULL
	bg_sign_event 17, 32, 0, BG_EVENT_PLAYER_FACING_ANY, NULL

InquillTown_MapEvents::
	map_events InquillTown_ObjectEvents, InquillTown_MapWarps, NULL, InquillTown_MapBGEvents

