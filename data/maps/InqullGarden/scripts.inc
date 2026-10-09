# 1 "data/maps/InqullGarden/scripts.pory"

# 2 "data/maps/InqullGarden/scripts.pory"
InqullGarden_MapScripts::
# 3 "data/maps/InqullGarden/scripts.pory"
	.byte 0
# 4 "data/maps/InqullGarden/scripts.pory"

# 5 "data/maps/InqullGarden/scripts.pory"
InqullGarden_EventScript_Object1::
# 6 "data/maps/InqullGarden/scripts.pory"
	lock
# 7 "data/maps/InqullGarden/scripts.pory"
	faceplayer
# 8 "data/maps/InqullGarden/scripts.pory"
	goto_if_set FLAG_RECEIVED_MIRACLE_SEED, InqullGarden_EventScript_Object1Repeat
# 9 "data/maps/InqullGarden/scripts.pory"
	msgbox InqullGarden_Text_Object1Gift, MSGBOX_DEFAULT
# 10 "data/maps/InqullGarden/scripts.pory"
	giveitem ITEM_MIRACLE_SEED
# 11 "data/maps/InqullGarden/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 12 "data/maps/InqullGarden/scripts.pory"
	setflag FLAG_RECEIVED_MIRACLE_SEED
# 13 "data/maps/InqullGarden/scripts.pory"
	release
# 14 "data/maps/InqullGarden/scripts.pory"
	end
# 15 "data/maps/InqullGarden/scripts.pory"

# 16 "data/maps/InqullGarden/scripts.pory"
InqullGarden_EventScript_Object1Repeat::
# 17 "data/maps/InqullGarden/scripts.pory"
	msgbox InqullGarden_Text_Object1Repeat, MSGBOX_DEFAULT
# 18 "data/maps/InqullGarden/scripts.pory"
	release
# 19 "data/maps/InqullGarden/scripts.pory"
	end

InqullGarden_EventScript_Object2::
# 23 "data/maps/InqullGarden/scripts.pory"
	msgbox InqullGarden_Text_Object2, MSGBOX_NPC
	end


InqullGarden_Text_Object1Gift::
# 27 "data/maps/InqullGarden/scripts.pory"
	.string "Do you like my garden? Here, take\n"
	.string "this. Maybe you can grow some plants\l"
	.string "of your own.$"

InqullGarden_Text_Object1Repeat::
# 33 "data/maps/InqullGarden/scripts.pory"
	.string "I spend all day tending to my garden.$"

InqullGarden_Text_Object2::
# 37 "data/maps/InqullGarden/scripts.pory"
	.string "Lom-breee.$"
