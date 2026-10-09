# 1 "data/maps/Route4/scripts.pory"

# 2 "data/maps/Route4/scripts.pory"
Route4_MapScripts::
# 3 "data/maps/Route4/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, Route4_OnLoad
# 4 "data/maps/Route4/scripts.pory"
	.byte 0
# 5 "data/maps/Route4/scripts.pory"

# 6 "data/maps/Route4/scripts.pory"
Route4_OnLoad:
# 7 "data/maps/Route4/scripts.pory"
	special InitRoute4SandPiles
# 8 "data/maps/Route4/scripts.pory"
	end
# 9 "data/maps/Route4/scripts.pory"

# 10 "data/maps/Route4/scripts.pory"
Route4_EventScript_SandPile::
# 11 "data/maps/Route4/scripts.pory"
	lockall
# 12 "data/maps/Route4/scripts.pory"
	specialvar VAR_RESULT, ChooseRoute4SandPileOutcome
# 13 "data/maps/Route4/scripts.pory"
	switch VAR_RESULT
# 14 "data/maps/Route4/scripts.pory"
	case 0, Route4_EventScript_EmptySandPile
# 15 "data/maps/Route4/scripts.pory"
	case 1, Route4_EventScript_SandPileItem
# 16 "data/maps/Route4/scripts.pory"
	case 2, Route4_EventScript_WiglettLevel6
# 17 "data/maps/Route4/scripts.pory"
	case 3, Route4_EventScript_WiglettLevel7
# 18 "data/maps/Route4/scripts.pory"
	releaseall
# 19 "data/maps/Route4/scripts.pory"
	end
# 20 "data/maps/Route4/scripts.pory"

# 21 "data/maps/Route4/scripts.pory"
Route4_EventScript_SandPileItem:
# 22 "data/maps/Route4/scripts.pory"
	giveitem VAR_0x8004
# 23 "data/maps/Route4/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Route4_EventScript_EndSandPileInteraction
# 24 "data/maps/Route4/scripts.pory"
	goto Route4_EventScript_RemoveSandPile
# 25 "data/maps/Route4/scripts.pory"

# 26 "data/maps/Route4/scripts.pory"
Route4_EventScript_EmptySandPile:
# 27 "data/maps/Route4/scripts.pory"
	msgbox Route4_Text_EmptySandPile, MSGBOX_DEFAULT
# 28 "data/maps/Route4/scripts.pory"
	goto Route4_EventScript_RemoveSandPile
# 29 "data/maps/Route4/scripts.pory"

# 30 "data/maps/Route4/scripts.pory"
Route4_EventScript_WiglettLevel6:
# 31 "data/maps/Route4/scripts.pory"
	setwildbattle SPECIES_WIGLETT, 6
# 32 "data/maps/Route4/scripts.pory"
	goto Route4_EventScript_StartWiglettBattle
# 33 "data/maps/Route4/scripts.pory"

# 34 "data/maps/Route4/scripts.pory"
Route4_EventScript_WiglettLevel7:
# 35 "data/maps/Route4/scripts.pory"
	setwildbattle SPECIES_WIGLETT, 7
# 36 "data/maps/Route4/scripts.pory"

# 37 "data/maps/Route4/scripts.pory"
Route4_EventScript_StartWiglettBattle:
# 38 "data/maps/Route4/scripts.pory"
	msgbox Route4_Text_WiglettInSand, MSGBOX_DEFAULT
# 39 "data/maps/Route4/scripts.pory"
	dowildbattle
# 40 "data/maps/Route4/scripts.pory"

# 41 "data/maps/Route4/scripts.pory"
Route4_EventScript_RemoveSandPile:
# 42 "data/maps/Route4/scripts.pory"
	specialvar VAR_RESULT, RemoveRoute4SandPile
# 43 "data/maps/Route4/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Route4_EventScript_EndSandPileInteraction
# 44 "data/maps/Route4/scripts.pory"
	waitstate
# 45 "data/maps/Route4/scripts.pory"
	releaseall
# 46 "data/maps/Route4/scripts.pory"
	end
# 47 "data/maps/Route4/scripts.pory"

# 48 "data/maps/Route4/scripts.pory"
Route4_EventScript_EndSandPileInteraction:
# 49 "data/maps/Route4/scripts.pory"
	releaseall
# 50 "data/maps/Route4/scripts.pory"
	end
# 51 "data/maps/Route4/scripts.pory"

# 52 "data/maps/Route4/scripts.pory"
Route4_Text_WiglettInSand:
# 53 "data/maps/Route4/scripts.pory"
	.string "There was a Pokémon hiding in\nthe sand!$"
# 54 "data/maps/Route4/scripts.pory"

# 55 "data/maps/Route4/scripts.pory"
Route4_Text_EmptySandPile:
# 56 "data/maps/Route4/scripts.pory"
	.string "It's just an empty pile of sand.$"
# 57 "data/maps/Route4/scripts.pory"

# 58 "data/maps/Route4/scripts.pory"
Route4_EventScript_Gabriel::
# 59 "data/maps/Route4/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE4_GABRIEL, Route4_Text_GabrielIntro, Route4_Text_GabrielDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route4_Text_GabrielVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 60 "data/maps/Route4/scripts.pory"
	msgbox Route4_Text_GabrielPostBattle, MSGBOX_AUTOCLOSE
# 61 "data/maps/Route4/scripts.pory"
	end
# 62 "data/maps/Route4/scripts.pory"

# 63 "data/maps/Route4/scripts.pory"
Route4_EventScript_Oliver::
# 64 "data/maps/Route4/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE4_OLIVER, Route4_Text_OliverIntro, Route4_Text_OliverDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route4_Text_OliverVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 65 "data/maps/Route4/scripts.pory"
	msgbox Route4_Text_OliverPostBattle, MSGBOX_AUTOCLOSE
# 66 "data/maps/Route4/scripts.pory"
	end
# 67 "data/maps/Route4/scripts.pory"

# 68 "data/maps/Route4/scripts.pory"
Route4_EventScript_JackAndMia::
# 69 "data/maps/Route4/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE4_JACK_AND_MIA, Route4_Text_JackAndMiaIntro, Route4_Text_JackAndMiaDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route4_Text_JackAndMiaVictory, Route4_Text_JackAndMiaNeedTwoPokemon, TRUE, TRUE, FALSE, FALSE
# 70 "data/maps/Route4/scripts.pory"
	msgbox Route4_Text_JackAndMiaPostBattle, MSGBOX_AUTOCLOSE
# 71 "data/maps/Route4/scripts.pory"
	end
# 72 "data/maps/Route4/scripts.pory"

# 73 "data/maps/Route4/scripts.pory"
Route4_EventScript_Liam::
# 74 "data/maps/Route4/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE4_LIAM, Route4_Text_LiamIntro, Route4_Text_LiamDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route4_Text_LiamVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 75 "data/maps/Route4/scripts.pory"
	msgbox Route4_Text_LiamPostBattle, MSGBOX_AUTOCLOSE
# 76 "data/maps/Route4/scripts.pory"
	end
# 77 "data/maps/Route4/scripts.pory"

# 78 "data/maps/Route4/scripts.pory"
Route4_EventScript_Amy::
# 79 "data/maps/Route4/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE4_AMY, Route4_Text_AmyIntro, Route4_Text_AmyDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route4_Text_AmyVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 80 "data/maps/Route4/scripts.pory"
	msgbox Route4_Text_AmyPostBattle, MSGBOX_AUTOCLOSE
# 81 "data/maps/Route4/scripts.pory"
	end
# 82 "data/maps/Route4/scripts.pory"

# 83 "data/maps/Route4/scripts.pory"
Route4_EventScript_AnnaAndNicole::
# 84 "data/maps/Route4/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE4_ANNA_AND_NICOLE, Route4_Text_AnnaAndNicoleIntro, Route4_Text_AnnaAndNicoleDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route4_Text_AnnaAndNicoleVictory, Route4_Text_AnnaAndNicoleNeedTwoPokemon, TRUE, TRUE, FALSE, FALSE
# 85 "data/maps/Route4/scripts.pory"
	msgbox Route4_Text_AnnaAndNicolePostBattle, MSGBOX_AUTOCLOSE
# 86 "data/maps/Route4/scripts.pory"
	end
# 87 "data/maps/Route4/scripts.pory"

# 88 "data/maps/Route4/scripts.pory"
Route4_EventScript_Elijah::
# 89 "data/maps/Route4/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE4_ELIJAH, Route4_Text_ElijahIntro, Route4_Text_ElijahDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route4_Text_ElijahVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 90 "data/maps/Route4/scripts.pory"
	msgbox Route4_Text_ElijahPostBattle, MSGBOX_AUTOCLOSE
# 91 "data/maps/Route4/scripts.pory"
	end
# 92 "data/maps/Route4/scripts.pory"

# 93 "data/maps/Route4/scripts.pory"
Route4_EventScript_Isaac::
# 94 "data/maps/Route4/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE4_ISAAC, Route4_Text_IsaacIntro, Route4_Text_IsaacDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route4_Text_IsaacVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 95 "data/maps/Route4/scripts.pory"
	msgbox Route4_Text_IsaacPostBattle, MSGBOX_AUTOCLOSE
# 96 "data/maps/Route4/scripts.pory"
	end
# 97 "data/maps/Route4/scripts.pory"

# 98 "data/maps/Route4/scripts.pory"
Route4_Text_GabrielIntro:
# 99 "data/maps/Route4/scripts.pory"
	.string "I found this Pokémon hiding in the\nsand. Look!$"
# 100 "data/maps/Route4/scripts.pory"

# 101 "data/maps/Route4/scripts.pory"
Route4_Text_GabrielDefeat:
# 102 "data/maps/Route4/scripts.pory"
	.string "Where did you find your Pokémon?$"
# 103 "data/maps/Route4/scripts.pory"

# 104 "data/maps/Route4/scripts.pory"
Route4_Text_GabrielVictory:
# 105 "data/maps/Route4/scripts.pory"
	.string "Come battle me again!$"
# 106 "data/maps/Route4/scripts.pory"

# 107 "data/maps/Route4/scripts.pory"
Route4_Text_GabrielPostBattle:
# 108 "data/maps/Route4/scripts.pory"
	.string "You never know where you’ll find\nPokémon. Look everywhere!$"
# 109 "data/maps/Route4/scripts.pory"

# 110 "data/maps/Route4/scripts.pory"
Route4_Text_OliverIntro:
# 111 "data/maps/Route4/scripts.pory"
	.string "I’ve been cooped up on a boat for so\nlong. I’m itching for a battle!$"
# 112 "data/maps/Route4/scripts.pory"

# 113 "data/maps/Route4/scripts.pory"
Route4_Text_OliverDefeat:
# 114 "data/maps/Route4/scripts.pory"
	.string "My skills are rusty from being away.$"
# 115 "data/maps/Route4/scripts.pory"

# 116 "data/maps/Route4/scripts.pory"
Route4_Text_OliverVictory:
# 117 "data/maps/Route4/scripts.pory"
	.string "Still got it!$"
# 118 "data/maps/Route4/scripts.pory"

# 119 "data/maps/Route4/scripts.pory"
Route4_Text_OliverPostBattle:
# 120 "data/maps/Route4/scripts.pory"
	.string "You can navigate from this lake all\nthe way to the ocean through a\nseries of rivers and canals. It’s a\nlong trip.$"
# 121 "data/maps/Route4/scripts.pory"

# 122 "data/maps/Route4/scripts.pory"
Route4_Text_JackAndMiaIntro:
# 123 "data/maps/Route4/scripts.pory"
	.string "The water is so cold!\nA Pokémon battle will warm us up!$"
# 124 "data/maps/Route4/scripts.pory"

# 125 "data/maps/Route4/scripts.pory"
Route4_Text_JackAndMiaDefeat:
# 126 "data/maps/Route4/scripts.pory"
	.string "Brr…\nThat was heated!$"
# 127 "data/maps/Route4/scripts.pory"

# 128 "data/maps/Route4/scripts.pory"
Route4_Text_JackAndMiaVictory:
# 129 "data/maps/Route4/scripts.pory"
	.string "Haha!\nGo cool off!$"
# 130 "data/maps/Route4/scripts.pory"

# 131 "data/maps/Route4/scripts.pory"
Route4_Text_JackAndMiaNeedTwoPokemon:
# 132 "data/maps/Route4/scripts.pory"
	.string "You need two Pokémon to battle us!$"
# 133 "data/maps/Route4/scripts.pory"

# 134 "data/maps/Route4/scripts.pory"
Route4_Text_JackAndMiaPostBattle:
# 135 "data/maps/Route4/scripts.pory"
	.string "The lake gets cold because it’s so\nbig.\nCome on bro, let’s go back in the\nwater.$"
# 136 "data/maps/Route4/scripts.pory"

# 137 "data/maps/Route4/scripts.pory"
Route4_Text_LiamIntro:
# 138 "data/maps/Route4/scripts.pory"
	.string "My dad owns a boat! If you beat me,\nmaybe I’ll let you see it.$"
# 139 "data/maps/Route4/scripts.pory"

# 140 "data/maps/Route4/scripts.pory"
Route4_Text_LiamDefeat:
# 141 "data/maps/Route4/scripts.pory"
	.string "Guess I need to put my money where\nmy mouth is.$"
# 142 "data/maps/Route4/scripts.pory"

# 143 "data/maps/Route4/scripts.pory"
Route4_Text_LiamVictory:
# 144 "data/maps/Route4/scripts.pory"
	.string "Ha! You should have bought stronger\nPokémon.$"
# 145 "data/maps/Route4/scripts.pory"

# 146 "data/maps/Route4/scripts.pory"
Route4_Text_LiamPostBattle:
# 147 "data/maps/Route4/scripts.pory"
	.string "See that big boat over there? That’s\nmy dad’s.$"
# 148 "data/maps/Route4/scripts.pory"

# 149 "data/maps/Route4/scripts.pory"
Route4_Text_AmyIntro:
# 150 "data/maps/Route4/scripts.pory"
	.string "Can you keep up the pace with me?$"
# 151 "data/maps/Route4/scripts.pory"

# 152 "data/maps/Route4/scripts.pory"
Route4_Text_AmyDefeat:
# 153 "data/maps/Route4/scripts.pory"
	.string "Phew…You outpaced me.$"
# 154 "data/maps/Route4/scripts.pory"

# 155 "data/maps/Route4/scripts.pory"
Route4_Text_AmyVictory:
# 156 "data/maps/Route4/scripts.pory"
	.string "You’re too slow!$"
# 157 "data/maps/Route4/scripts.pory"

# 158 "data/maps/Route4/scripts.pory"
Route4_Text_AmyPostBattle:
# 159 "data/maps/Route4/scripts.pory"
	.string "The trails along the lakefront are a\ngreat place to go running.$"
# 160 "data/maps/Route4/scripts.pory"

# 161 "data/maps/Route4/scripts.pory"
Route4_Text_AnnaAndNicoleIntro:
# 162 "data/maps/Route4/scripts.pory"
	.string "Here comes a trainer! Show him what\nI’ve taught you!\nI’ll do my best!$"
# 163 "data/maps/Route4/scripts.pory"

# 164 "data/maps/Route4/scripts.pory"
Route4_Text_AnnaAndNicoleDefeat:
# 165 "data/maps/Route4/scripts.pory"
	.string "Maybe we need a few more lessons…\nI just followed your lead…$"
# 166 "data/maps/Route4/scripts.pory"

# 167 "data/maps/Route4/scripts.pory"
Route4_Text_AnnaAndNicoleVictory:
# 168 "data/maps/Route4/scripts.pory"
	.string "That’s all thanks to my coaching!\nI want some of the credit…$"
# 169 "data/maps/Route4/scripts.pory"

# 170 "data/maps/Route4/scripts.pory"
Route4_Text_AnnaAndNicoleNeedTwoPokemon:
# 171 "data/maps/Route4/scripts.pory"
	.string "You need two Pokémon to battle us!$"
# 172 "data/maps/Route4/scripts.pory"

# 173 "data/maps/Route4/scripts.pory"
Route4_Text_AnnaAndNicolePostBattle:
# 174 "data/maps/Route4/scripts.pory"
	.string "We’ll call that a lesson in losing\ngracefully.\nI think I need a new mentor.$"
# 175 "data/maps/Route4/scripts.pory"

# 176 "data/maps/Route4/scripts.pory"
Route4_Text_ElijahIntro:
# 177 "data/maps/Route4/scripts.pory"
	.string "Hey, a trainer! Let’s jam!$"
# 178 "data/maps/Route4/scripts.pory"

# 179 "data/maps/Route4/scripts.pory"
Route4_Text_ElijahDefeat:
# 180 "data/maps/Route4/scripts.pory"
	.string "My tempo was off.$"
# 181 "data/maps/Route4/scripts.pory"

# 182 "data/maps/Route4/scripts.pory"
Route4_Text_ElijahVictory:
# 183 "data/maps/Route4/scripts.pory"
	.string "Your tempo’s off.$"
# 184 "data/maps/Route4/scripts.pory"

# 185 "data/maps/Route4/scripts.pory"
Route4_Text_ElijahPostBattle:
# 186 "data/maps/Route4/scripts.pory"
	.string "The rhythm of the waves is my\nmetronome.$"
# 187 "data/maps/Route4/scripts.pory"

# 188 "data/maps/Route4/scripts.pory"
Route4_Text_IsaacIntro:
# 189 "data/maps/Route4/scripts.pory"
	.string "Hey! You broke my concentration.$"
# 190 "data/maps/Route4/scripts.pory"

# 191 "data/maps/Route4/scripts.pory"
Route4_Text_IsaacDefeat:
# 192 "data/maps/Route4/scripts.pory"
	.string "Sigh…Nothing’s biting anyway.$"
# 193 "data/maps/Route4/scripts.pory"

# 194 "data/maps/Route4/scripts.pory"
Route4_Text_IsaacVictory:
# 195 "data/maps/Route4/scripts.pory"
	.string "That’s what you get.$"
# 196 "data/maps/Route4/scripts.pory"

# 197 "data/maps/Route4/scripts.pory"
Route4_Text_IsaacPostBattle:
# 198 "data/maps/Route4/scripts.pory"
	.string "Fishing takes a lot of patience. A\nlot.$"
