@
@ DO NOT MODIFY THIS FILE! It is auto-generated from data/maps/Route8/map.json
@

	.align 2

Route8_ObjectEvents:
	object_event 1, OBJ_EVENT_GFX_SPECIES(MR_MIME), 44, 23, 1, MOVEMENT_TYPE_WALK_IN_PLACE_DOWN, 0, 0, TRAINER_TYPE_NORMAL, 3, Route108_EventScript_Jerome, 0
	object_event 2, OBJ_EVENT_GFX_RUNNING_TRIATHLETE_M, 22, 25, 1, MOVEMENT_TYPE_WALK_SEQUENCE_RIGHT_UP_LEFT_DOWN, 6, 1, TRAINER_TYPE_NORMAL, 3, Route108_EventScript_Tara, 0
	object_event 3, OBJ_EVENT_GFX_WOMAN_2, 22, 16, 1, MOVEMENT_TYPE_FACE_DOWN_AND_RIGHT, 0, 0, TRAINER_TYPE_NORMAL, 5, Route108_EventScript_Matthew, 0
	object_event 4, OBJ_EVENT_GFX_GUARD, 10, 26, 1, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 5, Route108_EventScript_Missy, 0
	object_event 5, OBJ_EVENT_GFX_PSYCHIC_M, 36, 21, 3, MOVEMENT_TYPE_FACE_DOWN, 1, 1, TRAINER_TYPE_NORMAL, 1, Route108_EventScript_Cory, 0
	object_event 6, OBJ_EVENT_GFX_ITEM_BALL, 53, 14, 0, MOVEMENT_TYPE_NONE, 0, 0, TRAINER_TYPE_NONE, 0, NULL, 0
	object_event 7, OBJ_EVENT_GFX_ITEM_BALL, 37, 17, 0, MOVEMENT_TYPE_NONE, 0, 0, TRAINER_TYPE_NONE, 0, NULL, 0
	object_event 8, OBJ_EVENT_GFX_BOY_1, 52, 25, 0, MOVEMENT_TYPE_WANDER_LEFT_AND_RIGHT, 2, 0, TRAINER_TYPE_NONE, 0, Route8_EventScript_BridgeWarning, 0
	object_event 9, OBJ_EVENT_GFX_CAMPER, 55, 17, 0, MOVEMENT_TYPE_FACE_LEFT, 0, 0, TRAINER_TYPE_NONE, 0, NULL, 0
	object_event 10, OBJ_EVENT_GFX_TRUCK, 38, 21, 0, MOVEMENT_TYPE_NONE, 0, 0, TRAINER_TYPE_NONE, 0, NULL, 0
	object_event 11, OBJ_EVENT_GFX_FISHERMAN, 40, 29, 0, MOVEMENT_TYPE_FACE_RIGHT, 0, 0, TRAINER_TYPE_NONE, 0, NULL, 0
	object_event 12, 0, 45, 24, 0, MOVEMENT_TYPE_INVISIBLE, 0, 0, TRAINER_TYPE_NONE, 0, Route8_EventScript_PokemonBarrier, 0
	object_event 13, 0, 45, 23, 0, MOVEMENT_TYPE_INVISIBLE, 0, 0, TRAINER_TYPE_NONE, 0, Route8_EventScript_PokemonBarrier, 0
	object_event 14, 0, 43, 24, 0, MOVEMENT_TYPE_INVISIBLE, 0, 0, TRAINER_TYPE_NONE, 0, Route8_EventScript_PokemonBarrier, 0
	object_event 15, 0, 43, 23, 0, MOVEMENT_TYPE_INVISIBLE, 0, 0, TRAINER_TYPE_NONE, 0, Route8_EventScript_PokemonBarrier, 0
	object_event 16, 0, 43, 22, 0, MOVEMENT_TYPE_INVISIBLE, 0, 0, TRAINER_TYPE_NONE, 0, Route8_EventScript_PokemonBarrier, 0
	object_event 17, 0, 45, 22, 0, MOVEMENT_TYPE_INVISIBLE, 0, 0, TRAINER_TYPE_NONE, 0, Route8_EventScript_PokemonBarrier, 0
	object_event 18, 0, 43, 25, 0, MOVEMENT_TYPE_INVISIBLE, 0, 0, TRAINER_TYPE_NONE, 0, Route8_EventScript_PokemonBarrier, 0
	object_event 19, 0, 45, 25, 0, MOVEMENT_TYPE_INVISIBLE, 0, 0, TRAINER_TYPE_NONE, 0, Route8_EventScript_PokemonBarrier, 0

Route8_MapWarps:
	warp_def 54, 11, 0, 0, MAP_HYADES_ROUTE8

Route8_MapEvents::
	map_events Route8_ObjectEvents, Route8_MapWarps, NULL, NULL

