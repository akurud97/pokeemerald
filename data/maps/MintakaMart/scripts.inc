# 1 "data/maps/MintakaMart/scripts.pory"

# 2 "data/maps/MintakaMart/scripts.pory"
MintakaMart_MapScripts::
# 3 "data/maps/MintakaMart/scripts.pory"
	.byte 0
# 4 "data/maps/MintakaMart/scripts.pory"

# 5 "data/maps/MintakaMart/scripts.pory"
MintakaMart_EventScript_Clerk::
# 6 "data/maps/MintakaMart/scripts.pory"
	lock
# 7 "data/maps/MintakaMart/scripts.pory"
	faceplayer
# 8 "data/maps/MintakaMart/scripts.pory"
	message gText_HowMayIServeYou
# 9 "data/maps/MintakaMart/scripts.pory"
	waitmessage
# 10 "data/maps/MintakaMart/scripts.pory"
	pokemart MintakaMart_Pokemart
# 11 "data/maps/MintakaMart/scripts.pory"
	msgbox gText_PleaseComeAgain, MSGBOX_DEFAULT
# 12 "data/maps/MintakaMart/scripts.pory"
	release
# 13 "data/maps/MintakaMart/scripts.pory"
	end
# 14 "data/maps/MintakaMart/scripts.pory"

# 15 "data/maps/MintakaMart/scripts.pory"
	.align 2
# 16 "data/maps/MintakaMart/scripts.pory"
MintakaMart_Pokemart:
# 17 "data/maps/MintakaMart/scripts.pory"
	.2byte ITEM_POKE_BALL
# 18 "data/maps/MintakaMart/scripts.pory"
	.2byte ITEM_POTION
# 19 "data/maps/MintakaMart/scripts.pory"
	.2byte ITEM_ANTIDOTE
# 20 "data/maps/MintakaMart/scripts.pory"
	.2byte ITEM_PARALYZE_HEAL
# 21 "data/maps/MintakaMart/scripts.pory"
	.2byte ITEM_AWAKENING
# 22 "data/maps/MintakaMart/scripts.pory"
	.2byte ITEM_ESCAPE_ROPE
# 23 "data/maps/MintakaMart/scripts.pory"
	.2byte ITEM_REPEL
# 24 "data/maps/MintakaMart/scripts.pory"
	.2byte ITEM_NONE
# 25 "data/maps/MintakaMart/scripts.pory"
	release
# 26 "data/maps/MintakaMart/scripts.pory"
	end

MintakaMart_EventScript_Object2::
# 30 "data/maps/MintakaMart/scripts.pory"
	lock
# 31 "data/maps/MintakaMart/scripts.pory"
	msgbox MintakaMart_Text_Object2, MSGBOX_DEFAULT
# 32 "data/maps/MintakaMart/scripts.pory"
	release
	end


MintakaMart_EventScript_Object3::
# 37 "data/maps/MintakaMart/scripts.pory"
	msgbox MintakaMart_Text_Object3, MSGBOX_NPC
	end


MintakaMart_Text_Object2::
# 41 "data/maps/MintakaMart/scripts.pory"
	.string "Hmm… I wonder if these would heal a\n"
	.string "person’s injuries too…$"

MintakaMart_Text_Object3::
# 46 "data/maps/MintakaMart/scripts.pory"
	.string "There’s some really good deals in here.$"
