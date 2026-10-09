# 1 "data/maps/Route6/scripts.pory"

# 2 "data/maps/Route6/scripts.pory"
Route6_MapScripts::
# 3 "data/maps/Route6/scripts.pory"
    .byte 0
# 4 "data/maps/Route6/scripts.pory"

# 5 "data/maps/Route6/scripts.pory"
Route6_EventScript_CyclingRoadGate::
# 6 "data/maps/Route6/scripts.pory"
    lockall
# 7 "data/maps/Route6/scripts.pory"
    specialvar VAR_RESULT, GetPlayerFacingDirection
# 8 "data/maps/Route6/scripts.pory"
    goto_if_eq VAR_RESULT, DIR_SOUTH, Route6_EventScript_LeaveCyclingRoad
# 9 "data/maps/Route6/scripts.pory"
    specialvar VAR_RESULT, GetPlayerAvatarBike
# 10 "data/maps/Route6/scripts.pory"
    goto_if_eq VAR_RESULT, 0, Route6_EventScript_NoBike
# 11 "data/maps/Route6/scripts.pory"
    setflag FLAG_SYS_CYCLING_ROAD
# 12 "data/maps/Route6/scripts.pory"
    releaseall
# 13 "data/maps/Route6/scripts.pory"
    end
# 14 "data/maps/Route6/scripts.pory"

# 15 "data/maps/Route6/scripts.pory"
Route6_EventScript_LeaveCyclingRoad::
# 16 "data/maps/Route6/scripts.pory"
    clearflag FLAG_SYS_CYCLING_ROAD
# 17 "data/maps/Route6/scripts.pory"
    releaseall
# 18 "data/maps/Route6/scripts.pory"
    end
# 19 "data/maps/Route6/scripts.pory"

# 20 "data/maps/Route6/scripts.pory"
Route6_EventScript_NoBike::
# 21 "data/maps/Route6/scripts.pory"
    msgbox Route6_Text_CyclingRoadRequiresBicycle, MSGBOX_DEFAULT
# 22 "data/maps/Route6/scripts.pory"
    closemessage
# 23 "data/maps/Route6/scripts.pory"
    applymovement OBJ_EVENT_ID_PLAYER, Route6_Movement_PushPlayerSouth
# 24 "data/maps/Route6/scripts.pory"
    waitmovement 0
# 25 "data/maps/Route6/scripts.pory"
    releaseall
# 26 "data/maps/Route6/scripts.pory"
    end
# 27 "data/maps/Route6/scripts.pory"

# 28 "data/maps/Route6/scripts.pory"
Route6_Movement_PushPlayerSouth:
# 29 "data/maps/Route6/scripts.pory"
    walk_down
# 30 "data/maps/Route6/scripts.pory"
    step_end
# 31 "data/maps/Route6/scripts.pory"

# 32 "data/maps/Route6/scripts.pory"
Route6_Text_CyclingRoadRequiresBicycle:
# 33 "data/maps/Route6/scripts.pory"
    .string "Cycling Road is dangerous without\n"
# 34 "data/maps/Route6/scripts.pory"
    .string "a bicycle.$"
