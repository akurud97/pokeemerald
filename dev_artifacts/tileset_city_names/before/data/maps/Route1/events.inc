@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route1/map.json
@

	.align 2

Route1_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_LASS, 32, 5, 0, MOVEMENT_TYPE_NONE, 0, 0, TRAINER_TYPE_NORMAL, 2, Route1_EventScript_Evelyn, 0
	object_event 2, OBJ_EVENT_GFX_ITEM_BALL, 51, 6, 0, MOVEMENT_TYPE_NONE, 0, 0, TRAINER_TYPE_NONE, ITEM_ETHER, Common_EventScript_FindItem, FLAG_ITEM_ROUTE1_ETHER
	object_event 3, OBJ_EVENT_GFX_SCHOOL_KID_M, 8, 13, 0, MOVEMENT_TYPE_FACE_RIGHT, 0, 0, TRAINER_TYPE_NORMAL, 3, Route1_EventScript_Landon, 0
	object_event 4, OBJ_EVENT_GFX_LORELEI, 19, 15, 0, MOVEMENT_TYPE_FACE_DOWN, 0, 0, TRAINER_TYPE_NONE, 0, NULL, FLAG_HIDE_ROUTE1_PROFESSOR_SITKA
	object_event 5, OBJ_EVENT_GFX_MAY_NORMAL, 19, 22, 0, MOVEMENT_TYPE_FACE_UP, 0, 0, TRAINER_TYPE_NONE, 0, NULL, FLAG_HIDE_ROUTE1_APRIL

Route1_MapWarps:
	warp_def 19, 15, 0, 1, MAP_SITKA_LAB
	warp_def 59, 10, 0, 0, MAP_UNCLE_HOUSE

Route1_MapBGEvents:
	bg_sign_event 21, 16, 0, BG_EVENT_PLAYER_FACING_ANY, Route1_EventScript_SitkaLabSign

Route1_MapEvents::
	map_events Route1_ObjectEvents, Route1_MapWarps, NULL, Route1_MapBGEvents

