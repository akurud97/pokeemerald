# 1 "data/maps/MintakaGym/scripts.pory"

# 2 "data/maps/MintakaGym/scripts.pory"
MintakaGym_MapScripts::
# 3 "data/maps/MintakaGym/scripts.pory"
	map_script MAP_SCRIPT_ON_LOAD, MintakaGym_OnLoad
# 4 "data/maps/MintakaGym/scripts.pory"
	.byte 0
# 5 "data/maps/MintakaGym/scripts.pory"

# 6 "data/maps/MintakaGym/scripts.pory"
MintakaGym_OnLoad:
# 7 "data/maps/MintakaGym/scripts.pory"
	call_if_set FLAG_MINTAKA_GYM_FLYING_BIRD_PUZZLE, MintakaGym_EventScript_SetFlyingBirdSolved
# 8 "data/maps/MintakaGym/scripts.pory"
	call_if_set FLAG_MINTAKA_GYM_FOREST_BIRD_PUZZLE, MintakaGym_EventScript_SetForestBirdSolved
# 9 "data/maps/MintakaGym/scripts.pory"
	call_if_set FLAG_MINTAKA_GYM_DUCK_BOAT_PUZZLE, MintakaGym_EventScript_SetDuckBoatSolved
# 10 "data/maps/MintakaGym/scripts.pory"
	goto_if_unset FLAG_MINTAKA_GYM_FLYING_BIRD_PUZZLE, MintakaGym_EventScript_OnLoadEnd
# 11 "data/maps/MintakaGym/scripts.pory"
	goto_if_unset FLAG_MINTAKA_GYM_FOREST_BIRD_PUZZLE, MintakaGym_EventScript_OnLoadEnd
# 12 "data/maps/MintakaGym/scripts.pory"
	goto_if_unset FLAG_MINTAKA_GYM_DUCK_BOAT_PUZZLE, MintakaGym_EventScript_OnLoadEnd
# 13 "data/maps/MintakaGym/scripts.pory"
	call MintakaGym_EventScript_SetDoorOpen
# 14 "data/maps/MintakaGym/scripts.pory"

# 15 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_OnLoadEnd:
# 16 "data/maps/MintakaGym/scripts.pory"
	end
# 17 "data/maps/MintakaGym/scripts.pory"

# 18 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_Hailey::
# 19 "data/maps/MintakaGym/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_MINTAKA_GYM_HAILEY, MintakaGym_Text_HaileyIntro, MintakaGym_Text_HaileyDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, MintakaGym_Text_HaileyVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 20 "data/maps/MintakaGym/scripts.pory"
	msgbox MintakaGym_Text_HaileyPostBattle, MSGBOX_AUTOCLOSE
# 21 "data/maps/MintakaGym/scripts.pory"
	end
# 22 "data/maps/MintakaGym/scripts.pory"

# 23 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_Sawyer::
# 24 "data/maps/MintakaGym/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_MINTAKA_GYM_SAWYER, MintakaGym_Text_SawyerIntro, MintakaGym_Text_SawyerDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, MintakaGym_Text_SawyerVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 25 "data/maps/MintakaGym/scripts.pory"
	msgbox MintakaGym_Text_SawyerPostBattle, MSGBOX_AUTOCLOSE
# 26 "data/maps/MintakaGym/scripts.pory"
	end
# 27 "data/maps/MintakaGym/scripts.pory"

# 28 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_GymGuide::
# 29 "data/maps/MintakaGym/scripts.pory"
	lock
# 30 "data/maps/MintakaGym/scripts.pory"
	faceplayer
# 31 "data/maps/MintakaGym/scripts.pory"
	setspeaker SP_NAME_NONE
# 32 "data/maps/MintakaGym/scripts.pory"
	goto_if_set FLAG_DEFEATED_MINTAKA_GYM, MintakaGym_EventScript_GymGuideAfterLuca
# 33 "data/maps/MintakaGym/scripts.pory"
	msgbox MintakaGym_Text_GymGuideAdvice, MSGBOX_DEFAULT
# 34 "data/maps/MintakaGym/scripts.pory"
	release
# 35 "data/maps/MintakaGym/scripts.pory"
	end
# 36 "data/maps/MintakaGym/scripts.pory"

# 37 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_GymGuideAfterLuca:
# 38 "data/maps/MintakaGym/scripts.pory"
	msgbox MintakaGym_Text_GymGuideAfterLuca, MSGBOX_DEFAULT
# 39 "data/maps/MintakaGym/scripts.pory"
	release
# 40 "data/maps/MintakaGym/scripts.pory"
	end
# 41 "data/maps/MintakaGym/scripts.pory"

# 42 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_Luca::
# 43 "data/maps/MintakaGym/scripts.pory"
	goto_if_set FLAG_DEFEATED_MINTAKA_GYM, MintakaGym_EventScript_LucaDefeated
# 44 "data/maps/MintakaGym/scripts.pory"
	setspeaker SP_NAME_NONE
# 45 "data/maps/MintakaGym/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_MINTAKA_GYM_LEADER_LUCA, MintakaGym_Text_LucaIntro, MintakaGym_Text_LucaDefeat, MintakaGym_EventScript_LucaWon, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, MintakaGym_Text_LucaVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 46 "data/maps/MintakaGym/scripts.pory"
	end
# 47 "data/maps/MintakaGym/scripts.pory"

# 48 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_LucaWon::
# 49 "data/maps/MintakaGym/scripts.pory"
	setflag FLAG_DEFEATED_MINTAKA_GYM
# 50 "data/maps/MintakaGym/scripts.pory"
	setflag FLAG_ARIA_BADGE_GET
# 51 "data/maps/MintakaGym/scripts.pory"
	setspeaker SP_NAME_LUCA
# 52 "data/maps/MintakaGym/scripts.pory"
	msgbox MintakaGym_Text_LucaEarnedAriaBadge, MSGBOX_DEFAULT
# 53 "data/maps/MintakaGym/scripts.pory"
	setspeaker SP_NAME_NONE
# 54 "data/maps/MintakaGym/scripts.pory"
	message MintakaGym_Text_ReceivedAriaBadge
# 55 "data/maps/MintakaGym/scripts.pory"
	waitmessage
# 56 "data/maps/MintakaGym/scripts.pory"
	call Common_EventScript_PlayGymBadgeFanfare
# 57 "data/maps/MintakaGym/scripts.pory"
	setspeaker SP_NAME_LUCA
# 58 "data/maps/MintakaGym/scripts.pory"
	msgbox MintakaGym_Text_LucaTakeRoost, MSGBOX_DEFAULT
# 59 "data/maps/MintakaGym/scripts.pory"
	goto MintakaGym_EventScript_GiveRoost
# 60 "data/maps/MintakaGym/scripts.pory"

# 61 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_LucaDefeated:
# 62 "data/maps/MintakaGym/scripts.pory"
	goto_if_unset FLAG_RECEIVED_TM_ROOST, MintakaGym_EventScript_RetryRoost
# 63 "data/maps/MintakaGym/scripts.pory"
	setspeaker SP_NAME_LUCA
# 64 "data/maps/MintakaGym/scripts.pory"
	msgbox MintakaGym_Text_LucaPostBattle, MSGBOX_DEFAULT
# 65 "data/maps/MintakaGym/scripts.pory"
	release
# 66 "data/maps/MintakaGym/scripts.pory"
	end
# 67 "data/maps/MintakaGym/scripts.pory"

# 68 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_RetryRoost:
# 69 "data/maps/MintakaGym/scripts.pory"
	setspeaker SP_NAME_LUCA
# 70 "data/maps/MintakaGym/scripts.pory"
	msgbox MintakaGym_Text_LucaRetryRoost, MSGBOX_DEFAULT
# 71 "data/maps/MintakaGym/scripts.pory"

# 72 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_GiveRoost:
# 73 "data/maps/MintakaGym/scripts.pory"
	setspeaker SP_NAME_NONE
# 74 "data/maps/MintakaGym/scripts.pory"
	giveitem ITEM_TM_ROOST
# 75 "data/maps/MintakaGym/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 76 "data/maps/MintakaGym/scripts.pory"
	setflag FLAG_RECEIVED_TM_ROOST
# 77 "data/maps/MintakaGym/scripts.pory"
	release
# 78 "data/maps/MintakaGym/scripts.pory"
	end
# 79 "data/maps/MintakaGym/scripts.pory"

# 80 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_FlyingBirdPuzzle::
# 81 "data/maps/MintakaGym/scripts.pory"
	goto_if_set FLAG_MINTAKA_GYM_FLYING_BIRD_PUZZLE, MintakaGym_EventScript_End
# 82 "data/maps/MintakaGym/scripts.pory"
	lockall
# 83 "data/maps/MintakaGym/scripts.pory"
	setvar VAR_0x8004, SLIDING_PUZZLE_FLYING_BIRD
# 84 "data/maps/MintakaGym/scripts.pory"
	setvar VAR_0x8005, FALSE
# 85 "data/maps/MintakaGym/scripts.pory"
	special DoSlidingPuzzle
# 86 "data/maps/MintakaGym/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MintakaGym_EventScript_CancelPuzzle
# 87 "data/maps/MintakaGym/scripts.pory"
	setflag FLAG_MINTAKA_GYM_FLYING_BIRD_PUZZLE
# 88 "data/maps/MintakaGym/scripts.pory"
	call MintakaGym_EventScript_SetFlyingBirdSolved
# 89 "data/maps/MintakaGym/scripts.pory"
	goto MintakaGym_EventScript_FinishPuzzle
# 90 "data/maps/MintakaGym/scripts.pory"

# 91 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_ForestBirdPuzzle::
# 92 "data/maps/MintakaGym/scripts.pory"
	goto_if_set FLAG_MINTAKA_GYM_FOREST_BIRD_PUZZLE, MintakaGym_EventScript_End
# 93 "data/maps/MintakaGym/scripts.pory"
	lockall
# 94 "data/maps/MintakaGym/scripts.pory"
	setvar VAR_0x8004, SLIDING_PUZZLE_FOREST_BIRD
# 95 "data/maps/MintakaGym/scripts.pory"
	setvar VAR_0x8005, FALSE
# 96 "data/maps/MintakaGym/scripts.pory"
	special DoSlidingPuzzle
# 97 "data/maps/MintakaGym/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MintakaGym_EventScript_CancelPuzzle
# 98 "data/maps/MintakaGym/scripts.pory"
	setflag FLAG_MINTAKA_GYM_FOREST_BIRD_PUZZLE
# 99 "data/maps/MintakaGym/scripts.pory"
	call MintakaGym_EventScript_SetForestBirdSolved
# 100 "data/maps/MintakaGym/scripts.pory"
	goto MintakaGym_EventScript_FinishPuzzle
# 101 "data/maps/MintakaGym/scripts.pory"

# 102 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_DuckBoatPuzzle::
# 103 "data/maps/MintakaGym/scripts.pory"
	goto_if_set FLAG_MINTAKA_GYM_DUCK_BOAT_PUZZLE, MintakaGym_EventScript_End
# 104 "data/maps/MintakaGym/scripts.pory"
	lockall
# 105 "data/maps/MintakaGym/scripts.pory"
	setvar VAR_0x8004, SLIDING_PUZZLE_DUCK_BOAT
# 106 "data/maps/MintakaGym/scripts.pory"
	setvar VAR_0x8005, FALSE
# 107 "data/maps/MintakaGym/scripts.pory"
	special DoSlidingPuzzle
# 108 "data/maps/MintakaGym/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, MintakaGym_EventScript_CancelPuzzle
# 109 "data/maps/MintakaGym/scripts.pory"
	setflag FLAG_MINTAKA_GYM_DUCK_BOAT_PUZZLE
# 110 "data/maps/MintakaGym/scripts.pory"
	call MintakaGym_EventScript_SetDuckBoatSolved
# 111 "data/maps/MintakaGym/scripts.pory"

# 112 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_FinishPuzzle:
# 113 "data/maps/MintakaGym/scripts.pory"
	goto_if_unset FLAG_MINTAKA_GYM_FLYING_BIRD_PUZZLE, MintakaGym_EventScript_PuzzleClickedIntoPlace
# 114 "data/maps/MintakaGym/scripts.pory"
	goto_if_unset FLAG_MINTAKA_GYM_FOREST_BIRD_PUZZLE, MintakaGym_EventScript_PuzzleClickedIntoPlace
# 115 "data/maps/MintakaGym/scripts.pory"
	goto_if_unset FLAG_MINTAKA_GYM_DUCK_BOAT_PUZZLE, MintakaGym_EventScript_PuzzleClickedIntoPlace
# 116 "data/maps/MintakaGym/scripts.pory"
	call MintakaGym_EventScript_SetDoorOpen
# 117 "data/maps/MintakaGym/scripts.pory"
	special DrawWholeMapView
# 118 "data/maps/MintakaGym/scripts.pory"
	setspeaker SP_NAME_NONE
# 119 "data/maps/MintakaGym/scripts.pory"
	msgbox MintakaGym_Text_DoorOpening, MSGBOX_DEFAULT
# 120 "data/maps/MintakaGym/scripts.pory"
	releaseall
# 121 "data/maps/MintakaGym/scripts.pory"
	end
# 122 "data/maps/MintakaGym/scripts.pory"

# 123 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_PuzzleClickedIntoPlace:
# 124 "data/maps/MintakaGym/scripts.pory"
	special DrawWholeMapView
# 125 "data/maps/MintakaGym/scripts.pory"
	setspeaker SP_NAME_NONE
# 126 "data/maps/MintakaGym/scripts.pory"
	msgbox MintakaGym_Text_ClickIntoPlace, MSGBOX_DEFAULT
# 127 "data/maps/MintakaGym/scripts.pory"
	releaseall
# 128 "data/maps/MintakaGym/scripts.pory"
	end
# 129 "data/maps/MintakaGym/scripts.pory"

# 130 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_CancelPuzzle:
# 131 "data/maps/MintakaGym/scripts.pory"
	releaseall
# 132 "data/maps/MintakaGym/scripts.pory"
	end
# 133 "data/maps/MintakaGym/scripts.pory"

# 134 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_End:
# 135 "data/maps/MintakaGym/scripts.pory"
	end
# 136 "data/maps/MintakaGym/scripts.pory"

# 137 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_SetFlyingBirdSolved:
# 138 "data/maps/MintakaGym/scripts.pory"
	setmetatile 7, 29, METATILE_LilycoveMuseum_Painting0_Left, TRUE
# 139 "data/maps/MintakaGym/scripts.pory"
	setmetatile 8, 29, METATILE_LilycoveMuseum_Painting0_Right, TRUE
# 140 "data/maps/MintakaGym/scripts.pory"
	return
# 141 "data/maps/MintakaGym/scripts.pory"

# 142 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_SetForestBirdSolved:
# 143 "data/maps/MintakaGym/scripts.pory"
	setmetatile 2, 25, METATILE_LilycoveMuseum_Painting1_Left, TRUE
# 144 "data/maps/MintakaGym/scripts.pory"
	setmetatile 3, 25, METATILE_LilycoveMuseum_Painting1_Right, TRUE
# 145 "data/maps/MintakaGym/scripts.pory"
	return
# 146 "data/maps/MintakaGym/scripts.pory"

# 147 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_SetDuckBoatSolved:
# 148 "data/maps/MintakaGym/scripts.pory"
	setmetatile 12, 25, METATILE_LilycoveMuseum_Painting2_Left, TRUE
# 149 "data/maps/MintakaGym/scripts.pory"
	setmetatile 13, 25, METATILE_LilycoveMuseum_Painting2_Right, TRUE
# 150 "data/maps/MintakaGym/scripts.pory"
	return
# 151 "data/maps/MintakaGym/scripts.pory"

# 152 "data/maps/MintakaGym/scripts.pory"
MintakaGym_EventScript_SetDoorOpen:
# 153 "data/maps/MintakaGym/scripts.pory"
	setmetatile 7, 19, METATILE_LilycoveMuseum_MintakaGym_DoorWall, TRUE
# 154 "data/maps/MintakaGym/scripts.pory"
	setmetatile 8, 19, METATILE_LilycoveMuseum_MintakaGym_DoorWall, TRUE
# 155 "data/maps/MintakaGym/scripts.pory"
	setmetatile 7, 20, METATILE_LilycoveMuseum_MintakaGym_DoorWarp, FALSE
# 156 "data/maps/MintakaGym/scripts.pory"
	setmetatile 8, 20, METATILE_LilycoveMuseum_MintakaGym_DoorWarp, FALSE
# 157 "data/maps/MintakaGym/scripts.pory"
	return
# 158 "data/maps/MintakaGym/scripts.pory"

# 159 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_ClickIntoPlace:
# 160 "data/maps/MintakaGym/scripts.pory"
	.string "You hear something click into place.$"
# 161 "data/maps/MintakaGym/scripts.pory"

# 162 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_DoorOpening:
# 163 "data/maps/MintakaGym/scripts.pory"
	.string "You hear a door opening.$"
# 164 "data/maps/MintakaGym/scripts.pory"

# 165 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_HaileyIntro:
# 166 "data/maps/MintakaGym/scripts.pory"
	.string "I want to fly high like a bird!$"
# 167 "data/maps/MintakaGym/scripts.pory"

# 168 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_HaileyDefeat:
# 169 "data/maps/MintakaGym/scripts.pory"
	.string "You grounded me…$"
# 170 "data/maps/MintakaGym/scripts.pory"

# 171 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_HaileyVictory:
# 172 "data/maps/MintakaGym/scripts.pory"
	.string "I’m soaring!$"
# 173 "data/maps/MintakaGym/scripts.pory"

# 174 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_HaileyPostBattle:
# 175 "data/maps/MintakaGym/scripts.pory"
	.string "I want to feel the wind in my hair…$"
# 176 "data/maps/MintakaGym/scripts.pory"

# 177 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_SawyerIntro:
# 178 "data/maps/MintakaGym/scripts.pory"
	.string "You came to challenge the Gym?\n"
# 179 "data/maps/MintakaGym/scripts.pory"
	.string "You’ll have to face me first!$"
# 180 "data/maps/MintakaGym/scripts.pory"

# 181 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_SawyerDefeat:
# 182 "data/maps/MintakaGym/scripts.pory"
	.string "You won’t beat Luca!$"
# 183 "data/maps/MintakaGym/scripts.pory"

# 184 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_SawyerVictory:
# 185 "data/maps/MintakaGym/scripts.pory"
	.string "Come back when you’re stronger.$"
# 186 "data/maps/MintakaGym/scripts.pory"

# 187 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_SawyerPostBattle:
# 188 "data/maps/MintakaGym/scripts.pory"
	.string "My daddy has a better art\n"
# 189 "data/maps/MintakaGym/scripts.pory"
	.string "collection than this.$"
# 190 "data/maps/MintakaGym/scripts.pory"

# 191 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_GymGuideAdvice:
# 192 "data/maps/MintakaGym/scripts.pory"
	.string "Hey, a new challenger! This Gym uses\n"
# 193 "data/maps/MintakaGym/scripts.pory"
	.string "Flying-type Pokémon. Take a look at\l"
# 194 "data/maps/MintakaGym/scripts.pory"
	.string "the artwork around the Gym before you\l"
# 195 "data/maps/MintakaGym/scripts.pory"
	.string "take on the Leader.$"
# 196 "data/maps/MintakaGym/scripts.pory"

# 197 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_GymGuideAfterLuca:
# 198 "data/maps/MintakaGym/scripts.pory"
	.string "I’ve never seen Luca defeated like\n"
# 199 "data/maps/MintakaGym/scripts.pory"
	.string "that! Looks like we’ve got a new champ\l"
# 200 "data/maps/MintakaGym/scripts.pory"
	.string "in the making.$"
# 201 "data/maps/MintakaGym/scripts.pory"

# 202 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_LucaIntro:
# 203 "data/maps/MintakaGym/scripts.pory"
	.string "So, you’re taking on the Gym\n"
# 204 "data/maps/MintakaGym/scripts.pory"
	.string "challenge? I’m Luca, the Gym Leader\l"
# 205 "data/maps/MintakaGym/scripts.pory"
	.string "of Mintaka City.\p"
# 206 "data/maps/MintakaGym/scripts.pory"
	.string "My Pokémon have mastered the art\n"
# 207 "data/maps/MintakaGym/scripts.pory"
	.string "form of flying. Let’s see what\l"
# 208 "data/maps/MintakaGym/scripts.pory"
	.string "you’ve got.$"
# 209 "data/maps/MintakaGym/scripts.pory"

# 210 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_LucaDefeat:
# 211 "data/maps/MintakaGym/scripts.pory"
	.string "That was excellent! The battlefield\n"
# 212 "data/maps/MintakaGym/scripts.pory"
	.string "is your canvas.$"
# 213 "data/maps/MintakaGym/scripts.pory"

# 214 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_LucaVictory:
# 215 "data/maps/MintakaGym/scripts.pory"
	.string "That may have been my masterpiece.$"
# 216 "data/maps/MintakaGym/scripts.pory"

# 217 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_LucaEarnedAriaBadge:
# 218 "data/maps/MintakaGym/scripts.pory"
	.string "You fight with real artistry. You’ve\n"
# 219 "data/maps/MintakaGym/scripts.pory"
	.string "earned the Aria Badge.$"
# 220 "data/maps/MintakaGym/scripts.pory"

# 221 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_ReceivedAriaBadge:
# 222 "data/maps/MintakaGym/scripts.pory"
	.string "{PLAYER} received the ARIA BADGE\n"
# 223 "data/maps/MintakaGym/scripts.pory"
	.string "from LUCA.$"
# 224 "data/maps/MintakaGym/scripts.pory"

# 225 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_LucaTakeRoost:
# 226 "data/maps/MintakaGym/scripts.pory"
	.string "Take this too. The TM contains Roost.\n"
# 227 "data/maps/MintakaGym/scripts.pory"
	.string "It lets your Flying-type Pokémon take\l"
# 228 "data/maps/MintakaGym/scripts.pory"
	.string "a rest.$"
# 229 "data/maps/MintakaGym/scripts.pory"

# 230 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_LucaRetryRoost:
# 231 "data/maps/MintakaGym/scripts.pory"
	.string "Don’t forget the TM I wanted to give\n"
# 232 "data/maps/MintakaGym/scripts.pory"
	.string "you. Make some room in your Bag.$"
# 233 "data/maps/MintakaGym/scripts.pory"

# 234 "data/maps/MintakaGym/scripts.pory"
MintakaGym_Text_LucaPostBattle:
# 235 "data/maps/MintakaGym/scripts.pory"
	.string "You fight with real artistry. Good luck\n"
# 236 "data/maps/MintakaGym/scripts.pory"
	.string "on the rest of your Gym challenge.$"
