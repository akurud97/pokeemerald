# 1 "data/maps/Route3/scripts.pory"

# 2 "data/maps/Route3/scripts.pory"
Route3_MapScripts::
# 3 "data/maps/Route3/scripts.pory"
	.byte 0
# 4 "data/maps/Route3/scripts.pory"

# 5 "data/maps/Route3/scripts.pory"
Route3_EventScript_Alex::
# 6 "data/maps/Route3/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE3_ALEX, Route3_Text_AlexIntro, Route3_Text_AlexDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route3_Text_AlexVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 7 "data/maps/Route3/scripts.pory"
	msgbox Route3_Text_AlexPostBattle, MSGBOX_AUTOCLOSE
# 8 "data/maps/Route3/scripts.pory"
	end
# 9 "data/maps/Route3/scripts.pory"

# 10 "data/maps/Route3/scripts.pory"
Route3_EventScript_Cherise::
# 11 "data/maps/Route3/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE3_CHERISE, Route3_Text_CheriseIntro, Route3_Text_CheriseDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route3_Text_CheriseVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 12 "data/maps/Route3/scripts.pory"
	msgbox Route3_Text_CherisePostBattle, MSGBOX_AUTOCLOSE
# 13 "data/maps/Route3/scripts.pory"
	end
# 14 "data/maps/Route3/scripts.pory"

# 15 "data/maps/Route3/scripts.pory"
Route3_EventScript_Zack::
# 16 "data/maps/Route3/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE3_ZACK, Route3_Text_ZackIntro, Route3_Text_ZackDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route3_Text_ZackVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 17 "data/maps/Route3/scripts.pory"
	msgbox Route3_Text_ZackPostBattle, MSGBOX_AUTOCLOSE
# 18 "data/maps/Route3/scripts.pory"
	end
# 19 "data/maps/Route3/scripts.pory"

# 20 "data/maps/Route3/scripts.pory"
Route3_EventScript_DaisyAndSummer::
# 21 "data/maps/Route3/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE3_DAISY_AND_SUMMER, Route3_Text_TwinsIntro, Route3_Text_TwinsDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route3_Text_TwinsVictory, Route3_Text_TwinsNeedTwoPokemon, TRUE, TRUE, FALSE, FALSE
# 22 "data/maps/Route3/scripts.pory"
	msgbox Route3_Text_TwinsPostBattle, MSGBOX_AUTOCLOSE
# 23 "data/maps/Route3/scripts.pory"
	end
# 24 "data/maps/Route3/scripts.pory"

# 25 "data/maps/Route3/scripts.pory"
Route3_EventScript_OldRodFisherman::
# 26 "data/maps/Route3/scripts.pory"
	lock
# 27 "data/maps/Route3/scripts.pory"
	setobjectmovementtype 1, MOVEMENT_TYPE_FACE_DOWN
# 28 "data/maps/Route3/scripts.pory"
	faceplayer
# 29 "data/maps/Route3/scripts.pory"
	goto_if_set FLAG_RECEIVED_OLD_ROD, Route3_EventScript_OldRodRepeat
# 30 "data/maps/Route3/scripts.pory"
	msgbox Route3_Text_OldRodGift, MSGBOX_DEFAULT
# 31 "data/maps/Route3/scripts.pory"
	giveitem ITEM_OLD_ROD
# 32 "data/maps/Route3/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 33 "data/maps/Route3/scripts.pory"
	setflag FLAG_RECEIVED_OLD_ROD
# 34 "data/maps/Route3/scripts.pory"
	release
# 35 "data/maps/Route3/scripts.pory"
	end
# 36 "data/maps/Route3/scripts.pory"

# 37 "data/maps/Route3/scripts.pory"
Route3_EventScript_OldRodRepeat::
# 38 "data/maps/Route3/scripts.pory"
	msgbox Route3_Text_OldRodRepeat, MSGBOX_DEFAULT
# 39 "data/maps/Route3/scripts.pory"
	release
# 40 "data/maps/Route3/scripts.pory"
	end
# 41 "data/maps/Route3/scripts.pory"

# 42 "data/maps/Route3/scripts.pory"
Route3_EventScript_TreeckoOwner::
# 43 "data/maps/Route3/scripts.pory"
	msgbox Route3_Text_TreeckoOwner, MSGBOX_NPC
# 44 "data/maps/Route3/scripts.pory"
	end
# 45 "data/maps/Route3/scripts.pory"

# 46 "data/maps/Route3/scripts.pory"
Route3_EventScript_Treecko::
# 47 "data/maps/Route3/scripts.pory"
	msgbox Route3_Text_Treecko, MSGBOX_NPC
# 48 "data/maps/Route3/scripts.pory"
	end
# 49 "data/maps/Route3/scripts.pory"

# 50 "data/maps/Route3/scripts.pory"
Route3_EventScript_Sign::
# 51 "data/maps/Route3/scripts.pory"
	msgbox Route3_Text_Sign, MSGBOX_SIGN
# 52 "data/maps/Route3/scripts.pory"
	end

Route3_Text_AlexIntro::
# 55 "data/maps/Route3/scripts.pory"
	.string "Our breeding facility takes care of\n"
	.string "rare Pokémon! Check them out!$"

Route3_Text_AlexDefeat::
# 60 "data/maps/Route3/scripts.pory"
	.string "I guess we need to be more selective\n"
	.string "in our breeding.$"

Route3_Text_AlexVictory::
# 65 "data/maps/Route3/scripts.pory"
	.string "We breed for the best!$"

Route3_Text_AlexPostBattle::
# 69 "data/maps/Route3/scripts.pory"
	.string "Go talk to our owner. Maybe you could\n"
	.string "own a rare Pokémon like this yourself.$"

Route3_Text_CheriseIntro::
# 74 "data/maps/Route3/scripts.pory"
	.string "That tunnel was so cramped. Help my\n"
	.string "Budew stretch out!$"

Route3_Text_CheriseDefeat::
# 79 "data/maps/Route3/scripts.pory"
	.string "Are you headed for Mintaka City?\n"
	.string "You’ll have to go through these\l"
	.string "tunnels.$"

Route3_Text_CheriseVictory::
# 85 "data/maps/Route3/scripts.pory"
	.string "Let’s go, Budew!$"

Route3_Text_CherisePostBattle::
# 89 "data/maps/Route3/scripts.pory"
	.string "It smelled so damp and musty in that\n"
	.string "tunnel. I’m happy to be out in the\l"
	.string "open again.$"

Route3_Text_ZackIntro::
# 95 "data/maps/Route3/scripts.pory"
	.string "My Pokémon are the coolest!$"

Route3_Text_ZackDefeat::
# 99 "data/maps/Route3/scripts.pory"
	.string "Okay…your Pokémon are pretty cool too.$"

Route3_Text_ZackVictory::
# 103 "data/maps/Route3/scripts.pory"
	.string "You’re not very cool.$"

Route3_Text_ZackPostBattle::
# 107 "data/maps/Route3/scripts.pory"
	.string "Do you think I’m cool?$"

Route3_Text_TwinsIntro::
# 111 "data/maps/Route3/scripts.pory"
	.string "Hi! Will you play with us?$"

Route3_Text_TwinsDefeat::
# 115 "data/maps/Route3/scripts.pory"
	.string "We lost…$"

Route3_Text_TwinsVictory::
# 119 "data/maps/Route3/scripts.pory"
	.string "Thanks for playing!$"

Route3_Text_TwinsNeedTwoPokemon::
# 123 "data/maps/Route3/scripts.pory"
	.string "You need two Pokémon to play with us!$"

Route3_Text_TwinsPostBattle::
# 127 "data/maps/Route3/scripts.pory"
	.string "We like to play in the tunnel.$"

Route3_Text_OldRodGift::
# 131 "data/maps/Route3/scripts.pory"
	.string "This pond is great for fishing. Want\n"
	.string "to try it out? Here, I got an extra.$"

Route3_Text_OldRodRepeat::
# 136 "data/maps/Route3/scripts.pory"
	.string "How’s the fishing going?$"

Route3_Text_TreeckoOwner::
# 140 "data/maps/Route3/scripts.pory"
	.string "I’m so excited to take my Treecko\n"
	.string "home!$"

Route3_Text_Treecko::
# 145 "data/maps/Route3/scripts.pory"
	.string "Tree-treeck!$"

Route3_Text_Sign::
# 149 "data/maps/Route3/scripts.pory"
	.string "{UP_ARROW} Pokémon Breeders\n"
	.string "{RIGHT_ARROW} Moss Tunnels$"
