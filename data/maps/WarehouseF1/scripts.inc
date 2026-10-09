# 1 "data/maps/WarehouseF1/scripts.pory"

# 2 "data/maps/WarehouseF1/scripts.pory"
WarehouseF1_MapScripts::
# 3 "data/maps/WarehouseF1/scripts.pory"
	.byte 0
# 4 "data/maps/WarehouseF1/scripts.pory"

# 5 "data/maps/WarehouseF1/scripts.pory"
WarehouseF1_EventScript_Jeremy::
# 6 "data/maps/WarehouseF1/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_WAREHOUSE_JEREMY, WarehouseF1_Text_JeremyIntro, WarehouseF1_Text_JeremyDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, WarehouseF1_Text_JeremyVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 7 "data/maps/WarehouseF1/scripts.pory"
	msgbox WarehouseF1_Text_JeremyPostBattle, MSGBOX_AUTOCLOSE
# 8 "data/maps/WarehouseF1/scripts.pory"
	end
# 9 "data/maps/WarehouseF1/scripts.pory"

# 10 "data/maps/WarehouseF1/scripts.pory"
WarehouseF1_EventScript_Steven::
# 11 "data/maps/WarehouseF1/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_WAREHOUSE_STEVEN, WarehouseF1_Text_StevenIntro, WarehouseF1_Text_StevenDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, WarehouseF1_Text_StevenVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 12 "data/maps/WarehouseF1/scripts.pory"
	msgbox WarehouseF1_Text_StevenPostBattle, MSGBOX_AUTOCLOSE
# 13 "data/maps/WarehouseF1/scripts.pory"
	end

WarehouseF1_Text_JeremyIntro::
# 16 "data/maps/WarehouseF1/scripts.pory"
	.string "Hey! What’s a kid doing in here?$"

WarehouseF1_Text_JeremyDefeat::
# 20 "data/maps/WarehouseF1/scripts.pory"
	.string "Haha! That was fun.$"

WarehouseF1_Text_JeremyVictory::
# 24 "data/maps/WarehouseF1/scripts.pory"
	.string "Haha! That was fun.$"

WarehouseF1_Text_JeremyPostBattle::
# 28 "data/maps/WarehouseF1/scripts.pory"
	.string "You can hang out in here, just don’t\n"
	.string "touch anything.$"

WarehouseF1_Text_StevenIntro::
# 33 "data/maps/WarehouseF1/scripts.pory"
	.string "I’ve been working all day. I guess I\n"
	.string "could take a break to battle!$"

WarehouseF1_Text_StevenDefeat::
# 38 "data/maps/WarehouseF1/scripts.pory"
	.string "At least I was on the clock for that.$"

WarehouseF1_Text_StevenVictory::
# 42 "data/maps/WarehouseF1/scripts.pory"
	.string "That’s what they pay me for!$"

WarehouseF1_Text_StevenPostBattle::
# 46 "data/maps/WarehouseF1/scripts.pory"
	.string "We do hard work in here. It’s nice to\n"
	.string "unwind with a Pokémon battle.$"
