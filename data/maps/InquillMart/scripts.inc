# 1 "data/maps/InquillMart/scripts.pory"

# 2 "data/maps/InquillMart/scripts.pory"
InquillMart_MapScripts::
# 3 "data/maps/InquillMart/scripts.pory"
	.byte 0
# 4 "data/maps/InquillMart/scripts.pory"

# 5 "data/maps/InquillMart/scripts.pory"
InquillMart_EventScript_Clerk::
# 6 "data/maps/InquillMart/scripts.pory"
	lock
# 7 "data/maps/InquillMart/scripts.pory"
	faceplayer
# 8 "data/maps/InquillMart/scripts.pory"
	message gText_HowMayIServeYou
# 9 "data/maps/InquillMart/scripts.pory"
	waitmessage
# 10 "data/maps/InquillMart/scripts.pory"
	pokemart InquillMart_Pokemart
# 11 "data/maps/InquillMart/scripts.pory"
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
# 12 "data/maps/InquillMart/scripts.pory"
	release
# 13 "data/maps/InquillMart/scripts.pory"
	end
# 14 "data/maps/InquillMart/scripts.pory"

# 15 "data/maps/InquillMart/scripts.pory"
	.align 2
# 16 "data/maps/InquillMart/scripts.pory"
InquillMart_Pokemart:
# 17 "data/maps/InquillMart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 18 "data/maps/InquillMart/scripts.pory"
	.2byte ITEM_POTION
# 19 "data/maps/InquillMart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 20 "data/maps/InquillMart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 21 "data/maps/InquillMart/scripts.pory"
	.2byte ITEM_AWAKENING
# 22 "data/maps/InquillMart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 23 "data/maps/InquillMart/scripts.pory"
	.2byte ITEM_REPEL
# 24 "data/maps/InquillMart/scripts.pory"
	.2byte ITEM_NONE
# 25 "data/maps/InquillMart/scripts.pory"
	release
# 26 "data/maps/InquillMart/scripts.pory"
	end

InquillMart_EventScript_Object2::
# 30 "data/maps/InquillMart/scripts.pory"
	msgbox InquillMart_Text_Object2, MSGBOX_NPC
	end


InquillMart_Text_Object2::
# 34 "data/maps/InquillMart/scripts.pory"
	.string "Inquill might be a quiet town, but to\n"
	.string "me it’s the big city. So much variety…$"
