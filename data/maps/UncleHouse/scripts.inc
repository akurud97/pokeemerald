# 1 "data/maps/UncleHouse/scripts.pory"

# 2 "data/maps/UncleHouse/scripts.pory"
.set LOCALID_UNCLE, LOCALID_UNCLE_HOUSE_UNCLE
# 3 "data/maps/UncleHouse/scripts.pory"

# 4 "data/maps/UncleHouse/scripts.pory"
UncleHouse_MapScripts::
# 5 "data/maps/UncleHouse/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, UncleHouse_OnFrame
# 6 "data/maps/UncleHouse/scripts.pory"
	.byte 0
# 7 "data/maps/UncleHouse/scripts.pory"

# 8 "data/maps/UncleHouse/scripts.pory"
UncleHouse_OnFrame:
# 9 "data/maps/UncleHouse/scripts.pory"
	map_script_2 VAR_ALASIA_INTRO_STATE, 7, UncleHouse_EventScript_FirstVisit
# 10 "data/maps/UncleHouse/scripts.pory"
	.2byte 0
# 11 "data/maps/UncleHouse/scripts.pory"

# 12 "data/maps/UncleHouse/scripts.pory"
UncleHouse_EventScript_FirstVisit::
# 13 "data/maps/UncleHouse/scripts.pory"
	lockall
# 14 "data/maps/UncleHouse/scripts.pory"
	setvar VAR_ALASIA_INTRO_STATE, 8
# 15 "data/maps/UncleHouse/scripts.pory"
	applymovement LOCALID_UNCLE, Common_Movement_WalkInPlaceFasterDown
# 16 "data/maps/UncleHouse/scripts.pory"
	waitmovement 0
# 17 "data/maps/UncleHouse/scripts.pory"
	applymovement LOCALID_UNCLE, Common_Movement_ExclamationMark
# 18 "data/maps/UncleHouse/scripts.pory"
	waitmovement 0
# 19 "data/maps/UncleHouse/scripts.pory"
	setspeaker SP_NAME_UNCLE
# 20 "data/maps/UncleHouse/scripts.pory"
	msgbox UncleHouse_Text_GoodToSeeYou, MSGBOX_DEFAULT
# 21 "data/maps/UncleHouse/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, UncleHouse_Movement_PlayerApproach
# 22 "data/maps/UncleHouse/scripts.pory"
	waitmovement 0
# 23 "data/maps/UncleHouse/scripts.pory"
	setspeaker SP_NAME_NONE
# 24 "data/maps/UncleHouse/scripts.pory"
	msgbox UncleHouse_Text_GavePackage, MSGBOX_DEFAULT
# 25 "data/maps/UncleHouse/scripts.pory"
	removeitem ITEM_PACKAGE
# 26 "data/maps/UncleHouse/scripts.pory"
	setspeaker SP_NAME_UNCLE
# 27 "data/maps/UncleHouse/scripts.pory"
	msgbox UncleHouse_Text_ThanksForPackage, MSGBOX_DEFAULT
# 28 "data/maps/UncleHouse/scripts.pory"
	applymovement LOCALID_UNCLE, UncleHouse_Movement_SearchForPokedex
# 29 "data/maps/UncleHouse/scripts.pory"
	waitmovement 0
# 30 "data/maps/UncleHouse/scripts.pory"
	msgbox UncleHouse_Text_FoundPokedex, MSGBOX_DEFAULT
# 31 "data/maps/UncleHouse/scripts.pory"
	applymovement LOCALID_UNCLE, UncleHouse_Movement_ReturnWithPokedex
# 32 "data/maps/UncleHouse/scripts.pory"
	waitmovement 0
# 33 "data/maps/UncleHouse/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, Common_Movement_WalkInPlaceFasterLeft
# 34 "data/maps/UncleHouse/scripts.pory"
	waitmovement 0
# 35 "data/maps/UncleHouse/scripts.pory"
	msgbox UncleHouse_Text_ExplainPokedex, MSGBOX_DEFAULT
# 36 "data/maps/UncleHouse/scripts.pory"
	setspeaker SP_NAME_NONE
# 37 "data/maps/UncleHouse/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 38 "data/maps/UncleHouse/scripts.pory"
	message UncleHouse_Text_ReceivedPokedex
# 39 "data/maps/UncleHouse/scripts.pory"
	waitmessage
# 40 "data/maps/UncleHouse/scripts.pory"
	waitfanfare
# 41 "data/maps/UncleHouse/scripts.pory"
	waitbuttonpress
# 42 "data/maps/UncleHouse/scripts.pory"
	setflag FLAG_SYS_POKEDEX_GET
# 43 "data/maps/UncleHouse/scripts.pory"
	special SetUnlockedPokedexFlags
# 44 "data/maps/UncleHouse/scripts.pory"
	setflag FLAG_RECEIVED_POKEDEX_FROM_BIRCH
# 45 "data/maps/UncleHouse/scripts.pory"
	setspeaker SP_NAME_UNCLE
# 46 "data/maps/UncleHouse/scripts.pory"
	msgbox UncleHouse_Text_TakeTheseToo, MSGBOX_DEFAULT
# 47 "data/maps/UncleHouse/scripts.pory"
	setspeaker SP_NAME_NONE
# 48 "data/maps/UncleHouse/scripts.pory"
	giveitem ITEM_POKE_BALL, 5
# 49 "data/maps/UncleHouse/scripts.pory"
	setspeaker SP_NAME_UNCLE
# 50 "data/maps/UncleHouse/scripts.pory"
	msgbox UncleHouse_Text_AdventureAdvice, MSGBOX_DEFAULT
# 51 "data/maps/UncleHouse/scripts.pory"
	releaseall
# 52 "data/maps/UncleHouse/scripts.pory"
	end
# 53 "data/maps/UncleHouse/scripts.pory"

# 54 "data/maps/UncleHouse/scripts.pory"
UncleHouse_EventScript_Uncle::
# 55 "data/maps/UncleHouse/scripts.pory"
	lock
# 56 "data/maps/UncleHouse/scripts.pory"
	faceplayer
# 57 "data/maps/UncleHouse/scripts.pory"
	setspeaker SP_NAME_UNCLE
# 58 "data/maps/UncleHouse/scripts.pory"
	msgbox UncleHouse_Text_PostEvent, MSGBOX_DEFAULT
# 59 "data/maps/UncleHouse/scripts.pory"
	release
# 60 "data/maps/UncleHouse/scripts.pory"
	end
# 61 "data/maps/UncleHouse/scripts.pory"

# 62 "data/maps/UncleHouse/scripts.pory"
UncleHouse_Movement_PlayerApproach:
# 63 "data/maps/UncleHouse/scripts.pory"
	walk_up
# 64 "data/maps/UncleHouse/scripts.pory"
	walk_up
# 65 "data/maps/UncleHouse/scripts.pory"
	step_end
# 66 "data/maps/UncleHouse/scripts.pory"

# 67 "data/maps/UncleHouse/scripts.pory"
UncleHouse_Movement_SearchForPokedex:
# 68 "data/maps/UncleHouse/scripts.pory"
	walk_left
# 69 "data/maps/UncleHouse/scripts.pory"
	walk_left
# 70 "data/maps/UncleHouse/scripts.pory"
	walk_up
# 71 "data/maps/UncleHouse/scripts.pory"
	step_end
# 72 "data/maps/UncleHouse/scripts.pory"

# 73 "data/maps/UncleHouse/scripts.pory"
UncleHouse_Movement_ReturnWithPokedex:
# 74 "data/maps/UncleHouse/scripts.pory"
	walk_down
# 75 "data/maps/UncleHouse/scripts.pory"
	walk_down
# 76 "data/maps/UncleHouse/scripts.pory"
	walk_right
# 77 "data/maps/UncleHouse/scripts.pory"
	step_end
# 78 "data/maps/UncleHouse/scripts.pory"

# 79 "data/maps/UncleHouse/scripts.pory"
UncleHouse_Text_GoodToSeeYou:
# 80 "data/maps/UncleHouse/scripts.pory"
	.string "{PLAYER}! It’s good to see you.\p"
# 81 "data/maps/UncleHouse/scripts.pory"
	.string "What brings you here?$"
# 82 "data/maps/UncleHouse/scripts.pory"

# 83 "data/maps/UncleHouse/scripts.pory"
UncleHouse_Text_GavePackage:
# 84 "data/maps/UncleHouse/scripts.pory"
	.string "You gave your uncle his package.$"
# 85 "data/maps/UncleHouse/scripts.pory"

# 86 "data/maps/UncleHouse/scripts.pory"
UncleHouse_Text_ThanksForPackage:
# 87 "data/maps/UncleHouse/scripts.pory"
	.string "Hey, thanks a lot! I knew I forgot\n"
# 88 "data/maps/UncleHouse/scripts.pory"
	.string "something at your mom’s place.\p"
# 89 "data/maps/UncleHouse/scripts.pory"
	.string "It’s your summer vacation, right?\n"
# 90 "data/maps/UncleHouse/scripts.pory"
	.string "Why don’t you stay up here for a…\p"
# 91 "data/maps/UncleHouse/scripts.pory"
	.string "Hey… Is that a Poké Ball on your\n"
# 92 "data/maps/UncleHouse/scripts.pory"
	.string "belt?\p"
# 93 "data/maps/UncleHouse/scripts.pory"
	.string "No way! That’s so cool. Does your\n"
# 94 "data/maps/UncleHouse/scripts.pory"
	.string "mom know about this?\p"
# 95 "data/maps/UncleHouse/scripts.pory"
	.string "No? That Professor Sitka… Always so\n"
# 96 "data/maps/UncleHouse/scripts.pory"
	.string "eager to hand out Pokémon…\p"
# 97 "data/maps/UncleHouse/scripts.pory"
	.string "Listen, junior. I used to be a\n"
# 98 "data/maps/UncleHouse/scripts.pory"
	.string "Pokémon Trainer myself.\p"
# 99 "data/maps/UncleHouse/scripts.pory"
	.string "Hey, I wonder if I still have a…\n"
# 100 "data/maps/UncleHouse/scripts.pory"
	.string "Hold on a sec.$"
# 101 "data/maps/UncleHouse/scripts.pory"

# 102 "data/maps/UncleHouse/scripts.pory"
UncleHouse_Text_FoundPokedex:
# 103 "data/maps/UncleHouse/scripts.pory"
	.string "A-ha! I do still have one. And some\n"
# 104 "data/maps/UncleHouse/scripts.pory"
	.string "of these too…$"
# 105 "data/maps/UncleHouse/scripts.pory"

# 106 "data/maps/UncleHouse/scripts.pory"
UncleHouse_Text_ExplainPokedex:
# 107 "data/maps/UncleHouse/scripts.pory"
	.string "This is a Pokédex. I’m sure you\n"
# 108 "data/maps/UncleHouse/scripts.pory"
	.string "learned all about these in school.\p"
# 109 "data/maps/UncleHouse/scripts.pory"
	.string "I never got around to filling the\n"
# 110 "data/maps/UncleHouse/scripts.pory"
	.string "thing out…\p"
# 111 "data/maps/UncleHouse/scripts.pory"
	.string "Hey, take this, and do your uncle\n"
# 112 "data/maps/UncleHouse/scripts.pory"
	.string "proud, yeah?\p"
# 113 "data/maps/UncleHouse/scripts.pory"
	.string "Get out into the world and see as\n"
# 114 "data/maps/UncleHouse/scripts.pory"
	.string "many species of Pokémon as you can.$"
# 115 "data/maps/UncleHouse/scripts.pory"

# 116 "data/maps/UncleHouse/scripts.pory"
UncleHouse_Text_ReceivedPokedex:
# 117 "data/maps/UncleHouse/scripts.pory"
	.string "{PLAYER} received the Pokédex!$"
# 118 "data/maps/UncleHouse/scripts.pory"

# 119 "data/maps/UncleHouse/scripts.pory"
UncleHouse_Text_TakeTheseToo:
# 120 "data/maps/UncleHouse/scripts.pory"
	.string "Take these too.$"
# 121 "data/maps/UncleHouse/scripts.pory"

# 122 "data/maps/UncleHouse/scripts.pory"
UncleHouse_Text_AdventureAdvice:
# 123 "data/maps/UncleHouse/scripts.pory"
	.string "You’re lucky I still have this stuff\n"
# 124 "data/maps/UncleHouse/scripts.pory"
	.string "laying around. Go catch yourself\n"
# 125 "data/maps/UncleHouse/scripts.pory"
	.string "some Pokémon.\p"
# 126 "data/maps/UncleHouse/scripts.pory"
	.string "Maybe if you get strong enough, you\n"
# 127 "data/maps/UncleHouse/scripts.pory"
	.string "can take on the Gym challenge.\p"
# 128 "data/maps/UncleHouse/scripts.pory"
	.string "I don’t know if your mom will approve,\n"
# 129 "data/maps/UncleHouse/scripts.pory"
	.string "but you have my blessing.\p"
# 130 "data/maps/UncleHouse/scripts.pory"
	.string "By the way, speaking of, you should\n"
# 131 "data/maps/UncleHouse/scripts.pory"
	.string "probably go tell your mom what’s\n"
# 132 "data/maps/UncleHouse/scripts.pory"
	.string "going on.\p"
# 133 "data/maps/UncleHouse/scripts.pory"
	.string "Let her know you have a Pokémon, and\n"
# 134 "data/maps/UncleHouse/scripts.pory"
	.string "that you’re going to spend this\n"
# 135 "data/maps/UncleHouse/scripts.pory"
	.string "summer off on an adventure.\p"
# 136 "data/maps/UncleHouse/scripts.pory"
	.string "That is what you want to do, isn’t it?\n"
# 137 "data/maps/UncleHouse/scripts.pory"
	.string "I can see it in your eyes.\p"
# 138 "data/maps/UncleHouse/scripts.pory"
	.string "Alright, kid. Get out of here and hit\n"
# 139 "data/maps/UncleHouse/scripts.pory"
	.string "the road.\p"
# 140 "data/maps/UncleHouse/scripts.pory"
	.string "Come back to show me as you fill up\n"
# 141 "data/maps/UncleHouse/scripts.pory"
	.string "that old Pokédex. I ain’t going\n"
# 142 "data/maps/UncleHouse/scripts.pory"
	.string "anywhere.$"
# 143 "data/maps/UncleHouse/scripts.pory"

# 144 "data/maps/UncleHouse/scripts.pory"
UncleHouse_Text_PostEvent:
# 145 "data/maps/UncleHouse/scripts.pory"
	.string "I’m excited for you, kid. This was my\n"
# 146 "data/maps/UncleHouse/scripts.pory"
	.string "dream when I was your age. Give it\n"
# 147 "data/maps/UncleHouse/scripts.pory"
	.string "all you’ve got.$"
