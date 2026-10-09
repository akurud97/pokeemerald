# 1 "data/maps/WarehouseF2/scripts.pory"

# 2 "data/maps/WarehouseF2/scripts.pory"
WarehouseF2_MapScripts::
# 3 "data/maps/WarehouseF2/scripts.pory"
	.byte 0
# 4 "data/maps/WarehouseF2/scripts.pory"

# 5 "data/maps/WarehouseF2/scripts.pory"
WarehouseF2_EventScript_CargoWorker::
# 6 "data/maps/WarehouseF2/scripts.pory"
	lock
# 7 "data/maps/WarehouseF2/scripts.pory"
	faceplayer
# 8 "data/maps/WarehouseF2/scripts.pory"
	goto_if_ne VAR_MINTAKA_ACOLYTE_EVENT, 1, WarehouseF2_EventScript_CargoWorkerBeforeRescue
# 9 "data/maps/WarehouseF2/scripts.pory"
	goto_if_set FLAG_RECEIVED_PICKAXE, WarehouseF2_EventScript_CargoWorkerAfterGift
# 10 "data/maps/WarehouseF2/scripts.pory"
	msgbox WarehouseF2_Text_CargoWorkerGiftIntro, MSGBOX_DEFAULT
# 11 "data/maps/WarehouseF2/scripts.pory"
	giveitem ITEM_PICKAXE
# 12 "data/maps/WarehouseF2/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 13 "data/maps/WarehouseF2/scripts.pory"
	setflag FLAG_RECEIVED_PICKAXE
# 14 "data/maps/WarehouseF2/scripts.pory"
	msgbox WarehouseF2_Text_CargoWorkerAfterGift, MSGBOX_DEFAULT
# 15 "data/maps/WarehouseF2/scripts.pory"
	release
# 16 "data/maps/WarehouseF2/scripts.pory"
	end
# 17 "data/maps/WarehouseF2/scripts.pory"

# 18 "data/maps/WarehouseF2/scripts.pory"
WarehouseF2_EventScript_CargoWorkerAfterGift::
# 19 "data/maps/WarehouseF2/scripts.pory"
	msgbox WarehouseF2_Text_CargoWorkerAfterGift, MSGBOX_DEFAULT
# 20 "data/maps/WarehouseF2/scripts.pory"
	release
# 21 "data/maps/WarehouseF2/scripts.pory"
	end
# 22 "data/maps/WarehouseF2/scripts.pory"

# 23 "data/maps/WarehouseF2/scripts.pory"
WarehouseF2_EventScript_CargoWorkerBeforeRescue::
# 24 "data/maps/WarehouseF2/scripts.pory"
	msgbox WarehouseF2_Text_CargoWorkerBeforeRescue, MSGBOX_DEFAULT
# 25 "data/maps/WarehouseF2/scripts.pory"
	release
# 26 "data/maps/WarehouseF2/scripts.pory"
	end

WarehouseF2_Text_CargoWorkerGiftIntro::
# 29 "data/maps/WarehouseF2/scripts.pory"
	.string "Hey, you’re the kid that saved me\n"
	.string "earlier! I appreciate it.\p"
	.string "We’d be out a lot of money if that\n"
	.string "thief had taken off with our cargo\p"
	.string "truck. Here, take this for your\n"
	.string "trouble.$"

WarehouseF2_Text_CargoWorkerAfterGift::
# 38 "data/maps/WarehouseF2/scripts.pory"
	.string "You can use that to smash rocks. Who\n"
	.string "knows, maybe it will come in handy for\l"
	.string "a Pokémon trainer like you.$"

WarehouseF2_Text_CargoWorkerBeforeRescue::
# 44 "data/maps/WarehouseF2/scripts.pory"
	.string "Sorry, kid. This area is for warehouse\n"
	.string "employees.$"
