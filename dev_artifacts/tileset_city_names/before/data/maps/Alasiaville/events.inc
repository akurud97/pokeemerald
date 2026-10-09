@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Alasiaville/map.json
@

	.align 2

Alasiaville_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_POKEFAN_M, 26, 11, 3, MOVEMENT_TYPE_FACE_RIGHT, 0, 0, TRAINER_TYPE_NONE, 0, Alasiaville_EventScript_VacationMan, 0
	object_event 2, OBJ_EVENT_GFX_LITTLE_GIRL, 15, 19, 0, MOVEMENT_TYPE_WANDER_AROUND, 1, 1, TRAINER_TYPE_NONE, 0, Alasiaville_EventScript_YoungStudent, 0
	object_event 3, OBJ_EVENT_GFX_ITEM_BALL, 25, 7, 0, MOVEMENT_TYPE_NONE, 0, 0, TRAINER_TYPE_NONE, ITEM_POTION, Common_EventScript_FindItem, FLAG_ITEM_ALASIAVILLE_POTION
	object_event 4, OBJ_EVENT_GFX_MAY_NORMAL, 11, 8, 0, MOVEMENT_TYPE_FACE_LEFT, 0, 0, TRAINER_TYPE_NONE, 0, NULL, FLAG_HIDE_ALASIAVILLE_APRIL

Alasiaville_MapWarps:
	warp_def 25, 19, 0, 1, MAP_PLAYER_HOUSE1F
	warp_def 11, 4, 0, 2, MAP_APRIL_HOUSE1F

Alasiaville_MapBGEvents:
	bg_sign_event 19, 10, 0, BG_EVENT_PLAYER_FACING_ANY, Alasiaville_EventScript_TownSign
	bg_sign_event 22, 19, 0, BG_EVENT_PLAYER_FACING_ANY, Alasiaville_EventScript_PlayerHouseSign

Alasiaville_MapEvents::
	map_events Alasiaville_ObjectEvents, Alasiaville_MapWarps, NULL, Alasiaville_MapBGEvents

