# 1 "data/maps/Boathouse/scripts.pory"

# 2 "data/maps/Boathouse/scripts.pory"
Boathouse_MapScripts::
# 3 "data/maps/Boathouse/scripts.pory"
	.byte 0
# 4 "data/maps/Boathouse/scripts.pory"

# 5 "data/maps/Boathouse/scripts.pory"
Boathouse_EventScript_Object1::
# 6 "data/maps/Boathouse/scripts.pory"
	lock
# 7 "data/maps/Boathouse/scripts.pory"
	faceplayer
# 8 "data/maps/Boathouse/scripts.pory"
	checkitem ITEM_FORAGING_POUCH
# 9 "data/maps/Boathouse/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, Boathouse_EventScript_CheckForagingPouch
# 10 "data/maps/Boathouse/scripts.pory"
	msgbox Boathouse_Text_Object1Intro, MSGBOX_DEFAULT
# 11 "data/maps/Boathouse/scripts.pory"
	giveitem ITEM_FORAGING_POUCH
# 12 "data/maps/Boathouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 13 "data/maps/Boathouse/scripts.pory"
	release
# 14 "data/maps/Boathouse/scripts.pory"
	end
# 15 "data/maps/Boathouse/scripts.pory"

# 16 "data/maps/Boathouse/scripts.pory"
Boathouse_EventScript_CheckForagingPouch::
# 17 "data/maps/Boathouse/scripts.pory"
	specialvar VAR_RESULT, CalculateForagingPouchSalvageValue
# 18 "data/maps/Boathouse/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Boathouse_EventScript_Object1NoItems
# 19 "data/maps/Boathouse/scripts.pory"
	buffernumberstring STR_VAR_1, VAR_0x8004
# 20 "data/maps/Boathouse/scripts.pory"
	msgbox Boathouse_Text_Object1Offer, MSGBOX_YESNO
# 21 "data/maps/Boathouse/scripts.pory"
	goto_if_eq VAR_RESULT, NO, Boathouse_EventScript_Object1Decline
# 22 "data/maps/Boathouse/scripts.pory"
	special SellForagingPouchItems
# 23 "data/maps/Boathouse/scripts.pory"
	msgbox Boathouse_Text_Object1Accept, MSGBOX_DEFAULT
# 24 "data/maps/Boathouse/scripts.pory"
	release
# 25 "data/maps/Boathouse/scripts.pory"
	end
# 26 "data/maps/Boathouse/scripts.pory"

# 27 "data/maps/Boathouse/scripts.pory"
Boathouse_EventScript_Object1NoItems::
# 28 "data/maps/Boathouse/scripts.pory"
	msgbox Boathouse_Text_Object1NoItems, MSGBOX_DEFAULT
# 29 "data/maps/Boathouse/scripts.pory"
	release
# 30 "data/maps/Boathouse/scripts.pory"
	end
# 31 "data/maps/Boathouse/scripts.pory"

# 32 "data/maps/Boathouse/scripts.pory"
Boathouse_EventScript_Object1Decline::
# 33 "data/maps/Boathouse/scripts.pory"
	msgbox Boathouse_Text_Object1Decline, MSGBOX_DEFAULT
# 34 "data/maps/Boathouse/scripts.pory"
	release
# 35 "data/maps/Boathouse/scripts.pory"
	end
# 36 "data/maps/Boathouse/scripts.pory"

# 37 "data/maps/Boathouse/scripts.pory"
Boathouse_EventScript_Object2::
# 38 "data/maps/Boathouse/scripts.pory"
	lock
# 39 "data/maps/Boathouse/scripts.pory"
	faceplayer
# 40 "data/maps/Boathouse/scripts.pory"
	msgbox Boathouse_Text_Object2, MSGBOX_DEFAULT
# 41 "data/maps/Boathouse/scripts.pory"
	pokemart Boathouse_Pokemart
# 42 "data/maps/Boathouse/scripts.pory"
	release
# 43 "data/maps/Boathouse/scripts.pory"
	end
# 44 "data/maps/Boathouse/scripts.pory"

# 45 "data/maps/Boathouse/scripts.pory"
	.align 2
# 46 "data/maps/Boathouse/scripts.pory"
Boathouse_Pokemart:
# 47 "data/maps/Boathouse/scripts.pory"
	.2byte ITEM_SODA_POP
# 48 "data/maps/Boathouse/scripts.pory"
	.2byte ITEM_NONE
# 49 "data/maps/Boathouse/scripts.pory"
	release
# 50 "data/maps/Boathouse/scripts.pory"
	end
# 51 "data/maps/Boathouse/scripts.pory"

# 52 "data/maps/Boathouse/scripts.pory"
Boathouse_EventScript_Object3::
# 53 "data/maps/Boathouse/scripts.pory"
	msgbox Boathouse_Text_Object3, MSGBOX_NPC
# 54 "data/maps/Boathouse/scripts.pory"
	end
# 55 "data/maps/Boathouse/scripts.pory"

# 56 "data/maps/Boathouse/scripts.pory"
Boathouse_Text_Object1Intro:
# 57 "data/maps/Boathouse/scripts.pory"
	.string "Hello! If you find items on the beach,\n"
# 58 "data/maps/Boathouse/scripts.pory"
	.string "you can bring them here and we’ll pay\n"
# 59 "data/maps/Boathouse/scripts.pory"
	.string "you to salvage them.\p"
# 60 "data/maps/Boathouse/scripts.pory"
	.string "Here, take this pouch so you don’t take\n"
# 61 "data/maps/Boathouse/scripts.pory"
	.string "up too much space in your bag.$"
# 62 "data/maps/Boathouse/scripts.pory"

# 63 "data/maps/Boathouse/scripts.pory"
Boathouse_Text_Object1NoItems:
# 64 "data/maps/Boathouse/scripts.pory"
	.string "Hello! Come see me if you find anything\n"
# 65 "data/maps/Boathouse/scripts.pory"
	.string "interesting on the beach! We'll buy it\n"
# 66 "data/maps/Boathouse/scripts.pory"
	.string "from you to salvage.$"
# 67 "data/maps/Boathouse/scripts.pory"

# 68 "data/maps/Boathouse/scripts.pory"
Boathouse_Text_Object1Offer:
# 69 "data/maps/Boathouse/scripts.pory"
	.string "Hello! It looks like your Foraging Pouch\n"
# 70 "data/maps/Boathouse/scripts.pory"
	.string "is full. Would you like to sell what\n"
# 71 "data/maps/Boathouse/scripts.pory"
	.string "you’ve found?\n"
# 72 "data/maps/Boathouse/scripts.pory"
	.string "We can offer you ¥{STR_VAR_1} for those\n"
# 73 "data/maps/Boathouse/scripts.pory"
	.string "items.$"
# 74 "data/maps/Boathouse/scripts.pory"

# 75 "data/maps/Boathouse/scripts.pory"
Boathouse_Text_Object1Decline:
# 76 "data/maps/Boathouse/scripts.pory"
	.string "Okay! Come see us if you want to sell\n"
# 77 "data/maps/Boathouse/scripts.pory"
	.string "what you’ve foraged.$"
# 78 "data/maps/Boathouse/scripts.pory"

# 79 "data/maps/Boathouse/scripts.pory"
Boathouse_Text_Object1Accept:
# 80 "data/maps/Boathouse/scripts.pory"
	.string "Great! Come back here if you find\n"
# 81 "data/maps/Boathouse/scripts.pory"
	.string "anything else on the beach that can be\n"
# 82 "data/maps/Boathouse/scripts.pory"
	.string "salvaged.$"
# 83 "data/maps/Boathouse/scripts.pory"

# 84 "data/maps/Boathouse/scripts.pory"
Boathouse_Text_Object2:
# 85 "data/maps/Boathouse/scripts.pory"
	.string "Hey kid. Wanna buy a soda?$"
# 86 "data/maps/Boathouse/scripts.pory"

# 87 "data/maps/Boathouse/scripts.pory"
Boathouse_Text_Object3:
# 88 "data/maps/Boathouse/scripts.pory"
	.string "A soda pop is so refreshing after being\n"
# 89 "data/maps/Boathouse/scripts.pory"
	.string "on the beach!$"
