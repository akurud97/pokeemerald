# 1 "data/maps/Route2/scripts.pory"

# 2 "data/maps/Route2/scripts.pory"
Route2_MapScripts::
# 3 "data/maps/Route2/scripts.pory"
	.byte 0
# 4 "data/maps/Route2/scripts.pory"

# 5 "data/maps/Route2/scripts.pory"
Route2_EventScript_Emma::
# 6 "data/maps/Route2/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE2_EMMA, Route2_Text_EmmaIntro, Route2_Text_EmmaDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route2_Text_EmmaVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 7 "data/maps/Route2/scripts.pory"
	goto_if_set FLAG_SYS_DEXNAV_GET, Route2_EventScript_EmmaDexNavUnlocked
# 8 "data/maps/Route2/scripts.pory"
	msgbox Route2_Text_EmmaDexNavTutorial, MSGBOX_AUTOCLOSE
# 9 "data/maps/Route2/scripts.pory"
	setvar VAR_DEXNAV_SPECIES, SPECIES_NONE
# 10 "data/maps/Route2/scripts.pory"
	setvar VAR_DEXNAV_STEP_COUNTER, 0
# 11 "data/maps/Route2/scripts.pory"
	setflag FLAG_SYS_DEXNAV_GET
# 12 "data/maps/Route2/scripts.pory"
	setflag FLAG_SYS_DEXNAV_DETECTOR_MODE
# 13 "data/maps/Route2/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 14 "data/maps/Route2/scripts.pory"
	message Route2_Text_DexNavEnabled
# 15 "data/maps/Route2/scripts.pory"
	waitmessage
# 16 "data/maps/Route2/scripts.pory"
	waitfanfare
# 17 "data/maps/Route2/scripts.pory"
	waitbuttonpress
# 18 "data/maps/Route2/scripts.pory"
	closemessage
# 19 "data/maps/Route2/scripts.pory"
	end
# 20 "data/maps/Route2/scripts.pory"

# 21 "data/maps/Route2/scripts.pory"
Route2_EventScript_EmmaDexNavUnlocked::
# 22 "data/maps/Route2/scripts.pory"
	msgbox Route2_Text_EmmaPostBattle, MSGBOX_AUTOCLOSE
# 23 "data/maps/Route2/scripts.pory"
	end
# 24 "data/maps/Route2/scripts.pory"

# 25 "data/maps/Route2/scripts.pory"
Route2_EventScript_Eli::
# 26 "data/maps/Route2/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE2_ELI, Route2_Text_EliIntro, Route2_Text_EliDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route2_Text_EliVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 27 "data/maps/Route2/scripts.pory"
	msgbox Route2_Text_EliPostBattle, MSGBOX_AUTOCLOSE
# 28 "data/maps/Route2/scripts.pory"
	end
# 29 "data/maps/Route2/scripts.pory"

# 30 "data/maps/Route2/scripts.pory"
Route2_EventScript_Chloe::
# 31 "data/maps/Route2/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE2_CHLOE, Route2_Text_ChloeIntro, Route2_Text_ChloeDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route2_Text_ChloeVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 32 "data/maps/Route2/scripts.pory"
	msgbox Route2_Text_ChloePostBattle, MSGBOX_AUTOCLOSE
# 33 "data/maps/Route2/scripts.pory"
	end
# 34 "data/maps/Route2/scripts.pory"

# 35 "data/maps/Route2/scripts.pory"
Route2_EventScript_Max::
# 36 "data/maps/Route2/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_ROUTE2_MAX, Route2_Text_MaxIntro, Route2_Text_MaxDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, Route2_Text_MaxVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 37 "data/maps/Route2/scripts.pory"
	msgbox Route2_Text_MaxPostBattle, MSGBOX_AUTOCLOSE
# 38 "data/maps/Route2/scripts.pory"
	end

Route2_Text_EmmaIntro::
# 41 "data/maps/Route2/scripts.pory"
	.string "My Azurill is super strong!$"

Route2_Text_EmmaDefeat::
# 45 "data/maps/Route2/scripts.pory"
	.string "I guess Azurill still needs some\n"
	.string "training…$"

Route2_Text_EmmaVictory::
# 50 "data/maps/Route2/scripts.pory"
	.string "Told you my Azurill was strong!$"

Route2_Text_EmmaPostBattle::
# 54 "data/maps/Route2/scripts.pory"
	.string "I'm going to use Dexnav to look for\n"
	.string "all kinds of Pokémon!$"

Route2_Text_EmmaDexNavTutorial::
# 59 "data/maps/Route2/scripts.pory"
	.string "Hey, do you know about the Dexnav\n"
	.string "feature of your Pokédex? You can use\l"
	.string "it to find rare Pokémon that don't\l"
	.string "normally come out! That's how I caught\l"
	.string "my Azurill. Here, I'll help you\l"
	.string "activate it.$"

Route2_Text_DexNavEnabled::
# 68 "data/maps/Route2/scripts.pory"
	.string "Your DexNav has been enabled.\n"
	.string "Use it from the Start Menu.$"

Route2_Text_EliIntro::
# 73 "data/maps/Route2/scripts.pory"
	.string "Get out of the way! I’m looking for\n"
	.string "rare bugs!$"

Route2_Text_EliDefeat::
# 78 "data/maps/Route2/scripts.pory"
	.string "I shouldn’t have picked a fight..$"

Route2_Text_EliVictory::
# 82 "data/maps/Route2/scripts.pory"
	.string "That’s what you get for distracting\n"
	.string "me!$"

Route2_Text_EliPostBattle::
# 87 "data/maps/Route2/scripts.pory"
	.string "Let me know if you see any bug\n"
	.string "Pokémon around here.$"

Route2_Text_ChloeIntro::
# 92 "data/maps/Route2/scripts.pory"
	.string "I love cute Pokémon! I want to see\n"
	.string "your cute Pokémon!$"

Route2_Text_ChloeDefeat::
# 97 "data/maps/Route2/scripts.pory"
	.string "Your Pokémon are cute and strong!$"

Route2_Text_ChloeVictory::
# 101 "data/maps/Route2/scripts.pory"
	.string "My Pokémon are cuter than yours.$"

Route2_Text_ChloePostBattle::
# 105 "data/maps/Route2/scripts.pory"
	.string "There are so many cute Pokémon!\n"
	.string "I want to catch them all!$"

Route2_Text_MaxIntro::
# 110 "data/maps/Route2/scripts.pory"
	.string "I’m bored. Battle me!$"

Route2_Text_MaxDefeat::
# 114 "data/maps/Route2/scripts.pory"
	.string "Even losing a battle can be fun…\n"
	.string "I guess.$"

Route2_Text_MaxVictory::
# 119 "data/maps/Route2/scripts.pory"
	.string "Yeah! That was fun!$"

Route2_Text_MaxPostBattle::
# 123 "data/maps/Route2/scripts.pory"
	.string "Inquill Town is so boring. I want to\n"
	.string "go on an adventure!$"
