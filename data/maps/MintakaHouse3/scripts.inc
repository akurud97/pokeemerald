# 1 "data/maps/MintakaHouse3/scripts.pory"

# 2 "data/maps/MintakaHouse3/scripts.pory"
MintakaHouse3_MapScripts::
# 3 "data/maps/MintakaHouse3/scripts.pory"
	.byte 0
# 4 "data/maps/MintakaHouse3/scripts.pory"

# 5 "data/maps/MintakaHouse3/scripts.pory"
MintakaHouse3_EventScript_Object3::
# 6 "data/maps/MintakaHouse3/scripts.pory"
	lock
# 7 "data/maps/MintakaHouse3/scripts.pory"
	faceplayer
# 8 "data/maps/MintakaHouse3/scripts.pory"
	goto_if_set FLAG_RECEIVED_MINTAKA_SEA_INCENSE, MintakaHouse3_EventScript_Object3Repeat
# 9 "data/maps/MintakaHouse3/scripts.pory"
	msgbox MintakaHouse3_Text_Object3Gift, MSGBOX_DEFAULT
# 10 "data/maps/MintakaHouse3/scripts.pory"
	giveitem ITEM_SEA_INCENSE
# 11 "data/maps/MintakaHouse3/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 12 "data/maps/MintakaHouse3/scripts.pory"
	setflag FLAG_RECEIVED_MINTAKA_SEA_INCENSE
# 13 "data/maps/MintakaHouse3/scripts.pory"
	release
# 14 "data/maps/MintakaHouse3/scripts.pory"
	end
# 15 "data/maps/MintakaHouse3/scripts.pory"

# 16 "data/maps/MintakaHouse3/scripts.pory"
MintakaHouse3_EventScript_Object3Repeat::
# 17 "data/maps/MintakaHouse3/scripts.pory"
	msgbox MintakaHouse3_Text_Object3Repeat, MSGBOX_DEFAULT
# 18 "data/maps/MintakaHouse3/scripts.pory"
	release
# 19 "data/maps/MintakaHouse3/scripts.pory"
	end

MintakaHouse3_EventScript_Object1::
# 23 "data/maps/MintakaHouse3/scripts.pory"
	msgbox MintakaHouse3_Text_Object1, MSGBOX_NPC
	end


MintakaHouse3_EventScript_Object2::
# 28 "data/maps/MintakaHouse3/scripts.pory"
	msgbox MintakaHouse3_Text_Object2, MSGBOX_NPC
	end


MintakaHouse3_Text_Object1::
# 32 "data/maps/MintakaHouse3/scripts.pory"
	.string "My dad is visiting from Castula City.\n"
	.string "I wish he would retire and settle back\l"
	.string "down here.$"

MintakaHouse3_Text_Object2::
# 38 "data/maps/MintakaHouse3/scripts.pory"
	.string "Make sure you spend some time\n"
	.string "relaxing on the beach while you’re in\l"
	.string "town.$"

MintakaHouse3_Text_Object3Gift::
# 44 "data/maps/MintakaHouse3/scripts.pory"
	.string "Ah, the scent of the lake air takes me\n"
	.string "back to my youth… Take this, and carry\l"
	.string "the memory with you.$"

MintakaHouse3_Text_Object3Repeat::
# 50 "data/maps/MintakaHouse3/scripts.pory"
	.string "Ah, the scent of the lake air takes me\n"
	.string "back to my youth…$"
