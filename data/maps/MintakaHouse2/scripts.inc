# 1 "data/maps/MintakaHouse2/scripts.pory"

# 2 "data/maps/MintakaHouse2/scripts.pory"
MintakaHouse2_MapScripts::
# 3 "data/maps/MintakaHouse2/scripts.pory"
	.byte 0

MintakaHouse2_EventScript_Object1::
# 7 "data/maps/MintakaHouse2/scripts.pory"
	msgbox MintakaHouse2_Text_Object1, MSGBOX_NPC
	end


MintakaHouse2_EventScript_Object2::
# 12 "data/maps/MintakaHouse2/scripts.pory"
	msgbox MintakaHouse2_Text_Object2, MSGBOX_NPC
	end


MintakaHouse2_EventScript_Object3::
# 17 "data/maps/MintakaHouse2/scripts.pory"
	lock
# 18 "data/maps/MintakaHouse2/scripts.pory"
	msgbox MintakaHouse2_Text_Object3, MSGBOX_DEFAULT
# 19 "data/maps/MintakaHouse2/scripts.pory"
	release
	end


MintakaHouse2_Text_Object1::
# 23 "data/maps/MintakaHouse2/scripts.pory"
	.string "I’ve been on a ship for weeks. It’s\n"
	.string "great to be back home with my family.$"

MintakaHouse2_Text_Object2::
# 28 "data/maps/MintakaHouse2/scripts.pory"
	.string "It’s hard having my husband away for\n"
	.string "long periods, but he provides for us.$"

MintakaHouse2_Text_Object3::
# 33 "data/maps/MintakaHouse2/scripts.pory"
	.string "Daddy! Tell me more stories!$"
