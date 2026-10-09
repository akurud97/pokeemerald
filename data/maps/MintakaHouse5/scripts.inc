# 1 "data/maps/MintakaHouse5/scripts.pory"

# 2 "data/maps/MintakaHouse5/scripts.pory"
MintakaHouse5_MapScripts::
# 3 "data/maps/MintakaHouse5/scripts.pory"
	.byte 0
# 4 "data/maps/MintakaHouse5/scripts.pory"

# 5 "data/maps/MintakaHouse5/scripts.pory"
MintakaHouse5_EventScript_Object1::
# 6 "data/maps/MintakaHouse5/scripts.pory"
	lock
# 7 "data/maps/MintakaHouse5/scripts.pory"
	faceplayer
# 8 "data/maps/MintakaHouse5/scripts.pory"
	goto_if_set FLAG_RECEIVED_MINTAKA_DAMP_ROCK, MintakaHouse5_EventScript_Object1Repeat
# 9 "data/maps/MintakaHouse5/scripts.pory"
	msgbox MintakaHouse5_Text_Object1Gift, MSGBOX_DEFAULT
# 10 "data/maps/MintakaHouse5/scripts.pory"
	giveitem ITEM_DAMP_ROCK
# 11 "data/maps/MintakaHouse5/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 12 "data/maps/MintakaHouse5/scripts.pory"
	setflag FLAG_RECEIVED_MINTAKA_DAMP_ROCK
# 13 "data/maps/MintakaHouse5/scripts.pory"
	release
# 14 "data/maps/MintakaHouse5/scripts.pory"
	end
# 15 "data/maps/MintakaHouse5/scripts.pory"

# 16 "data/maps/MintakaHouse5/scripts.pory"
MintakaHouse5_EventScript_Object1Repeat::
# 17 "data/maps/MintakaHouse5/scripts.pory"
	msgbox MintakaHouse5_Text_Object1Repeat, MSGBOX_DEFAULT
# 18 "data/maps/MintakaHouse5/scripts.pory"
	release
# 19 "data/maps/MintakaHouse5/scripts.pory"
	end
# 20 "data/maps/MintakaHouse5/scripts.pory"

# 21 "data/maps/MintakaHouse5/scripts.pory"
MintakaHouse5_Text_Object1Gift:
# 22 "data/maps/MintakaHouse5/scripts.pory"
	.string "I brought this home from the\n"
# 23 "data/maps/MintakaHouse5/scripts.pory"
	.string "beach thinking it might be a\n"
# 24 "data/maps/MintakaHouse5/scripts.pory"
	.string "fossil, but it’s just a plain old\n"
# 25 "data/maps/MintakaHouse5/scripts.pory"
	.string "rock. You can have it.$"
# 26 "data/maps/MintakaHouse5/scripts.pory"

# 27 "data/maps/MintakaHouse5/scripts.pory"
MintakaHouse5_Text_Object1Repeat:
# 28 "data/maps/MintakaHouse5/scripts.pory"
	.string "I heard there might be fossils in\n"
# 29 "data/maps/MintakaHouse5/scripts.pory"
	.string "cave systems along the shore.$"
