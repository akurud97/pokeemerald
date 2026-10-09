# 1 "data/maps/PlayerHouse1F/scripts.pory"

# 2 "data/maps/PlayerHouse1F/scripts.pory"
.set LOCALID_MOM, LOCALID_PLAYER_HOUSE_MOM
# 3 "data/maps/PlayerHouse1F/scripts.pory"

# 4 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_MapScripts::
# 5 "data/maps/PlayerHouse1F/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, PlayerHouse1F_OnFrame
# 6 "data/maps/PlayerHouse1F/scripts.pory"
	.byte 0
# 7 "data/maps/PlayerHouse1F/scripts.pory"

# 8 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_OnFrame:
# 9 "data/maps/PlayerHouse1F/scripts.pory"
	map_script_2 VAR_ALASIA_INTRO_STATE, 2, PlayerHouse1F_EventScript_MomIntro
# 10 "data/maps/PlayerHouse1F/scripts.pory"
	map_script_2 VAR_ALASIA_INTRO_STATE, 8, PlayerHouse1F_EventScript_MomAdventurePermission
# 11 "data/maps/PlayerHouse1F/scripts.pory"
	.2byte 0
# 12 "data/maps/PlayerHouse1F/scripts.pory"

# 13 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_EventScript_MomIntro::
# 14 "data/maps/PlayerHouse1F/scripts.pory"
	lockall
# 15 "data/maps/PlayerHouse1F/scripts.pory"
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterDown
# 16 "data/maps/PlayerHouse1F/scripts.pory"
	waitmovement 0
# 17 "data/maps/PlayerHouse1F/scripts.pory"
	setspeaker SP_NAME_MOM
# 18 "data/maps/PlayerHouse1F/scripts.pory"
	msgbox PlayerHouse1F_Text_LastDayOfSchool, MSGBOX_DEFAULT
# 19 "data/maps/PlayerHouse1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, PlayerHouse1F_Movement_PlayerApproachMom
# 20 "data/maps/PlayerHouse1F/scripts.pory"
	waitmovement 0
# 21 "data/maps/PlayerHouse1F/scripts.pory"
	msgbox PlayerHouse1F_Text_CookiesAndFriendName, MSGBOX_DEFAULT
# 22 "data/maps/PlayerHouse1F/scripts.pory"
	multichoice 0, 0, MULTI_APRIL_NAME, FALSE
# 23 "data/maps/PlayerHouse1F/scripts.pory"
	goto_if_eq VAR_RESULT, 0, PlayerHouse1F_EventScript_EnterAprilName
# 24 "data/maps/PlayerHouse1F/scripts.pory"
	special SetAprilNameFromChoice
# 25 "data/maps/PlayerHouse1F/scripts.pory"
	goto PlayerHouse1F_EventScript_AprilNameChosen
# 26 "data/maps/PlayerHouse1F/scripts.pory"

# 27 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_EventScript_EnterAprilName::
# 28 "data/maps/PlayerHouse1F/scripts.pory"
	special StartAprilNamingScreen
# 29 "data/maps/PlayerHouse1F/scripts.pory"

# 30 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_EventScript_AprilNameChosen::
# 31 "data/maps/PlayerHouse1F/scripts.pory"
	special BufferAprilName
# 32 "data/maps/PlayerHouse1F/scripts.pory"
	setflag FLAG_APRIL_NAMED
# 33 "data/maps/PlayerHouse1F/scripts.pory"
	setspeaker SP_NAME_MOM
# 34 "data/maps/PlayerHouse1F/scripts.pory"
	msgbox PlayerHouse1F_Text_ThatsRight, MSGBOX_DEFAULT
# 35 "data/maps/PlayerHouse1F/scripts.pory"
	msgbox PlayerHouse1F_Text_UnclesPackage, MSGBOX_DEFAULT
# 36 "data/maps/PlayerHouse1F/scripts.pory"
	setspeaker SP_NAME_NONE
# 37 "data/maps/PlayerHouse1F/scripts.pory"
	giveitem ITEM_PACKAGE
# 38 "data/maps/PlayerHouse1F/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, PlayerHouse1F_EventScript_ResetMom
# 39 "data/maps/PlayerHouse1F/scripts.pory"
	setflag FLAG_ALASIAVILLE_TALKED_TO_MOM
# 40 "data/maps/PlayerHouse1F/scripts.pory"
	setvar VAR_ALASIA_INTRO_STATE, 3
# 41 "data/maps/PlayerHouse1F/scripts.pory"

# 42 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_EventScript_ResetMom::
# 43 "data/maps/PlayerHouse1F/scripts.pory"
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterRight
# 44 "data/maps/PlayerHouse1F/scripts.pory"
	waitmovement 0
# 45 "data/maps/PlayerHouse1F/scripts.pory"
	releaseall
# 46 "data/maps/PlayerHouse1F/scripts.pory"
	end
# 47 "data/maps/PlayerHouse1F/scripts.pory"

# 48 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_EventScript_Mom::
# 49 "data/maps/PlayerHouse1F/scripts.pory"
	lock
# 50 "data/maps/PlayerHouse1F/scripts.pory"
	faceplayer
# 51 "data/maps/PlayerHouse1F/scripts.pory"
	setspeaker SP_NAME_MOM
# 52 "data/maps/PlayerHouse1F/scripts.pory"
	goto_if_ge VAR_ALASIA_INTRO_STATE, 9, PlayerHouse1F_EventScript_MomAdventureCheckIn
# 53 "data/maps/PlayerHouse1F/scripts.pory"
	msgbox PlayerHouse1F_Text_UnclesHouseReminder, MSGBOX_DEFAULT
# 54 "data/maps/PlayerHouse1F/scripts.pory"
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterRight
# 55 "data/maps/PlayerHouse1F/scripts.pory"
	waitmovement 0
# 56 "data/maps/PlayerHouse1F/scripts.pory"
	release
# 57 "data/maps/PlayerHouse1F/scripts.pory"
	end
# 58 "data/maps/PlayerHouse1F/scripts.pory"

# 59 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_EventScript_MomAdventureCheckIn::
# 60 "data/maps/PlayerHouse1F/scripts.pory"
	msgbox PlayerHouse1F_Text_AdventureCheckIn, MSGBOX_DEFAULT
# 61 "data/maps/PlayerHouse1F/scripts.pory"
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterRight
# 62 "data/maps/PlayerHouse1F/scripts.pory"
	waitmovement 0
# 63 "data/maps/PlayerHouse1F/scripts.pory"
	release
# 64 "data/maps/PlayerHouse1F/scripts.pory"
	end
# 65 "data/maps/PlayerHouse1F/scripts.pory"

# 66 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_EventScript_MomAdventurePermission::
# 67 "data/maps/PlayerHouse1F/scripts.pory"
	lockall
# 68 "data/maps/PlayerHouse1F/scripts.pory"
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterDown
# 69 "data/maps/PlayerHouse1F/scripts.pory"
	waitmovement 0
# 70 "data/maps/PlayerHouse1F/scripts.pory"
	setspeaker SP_NAME_MOM
# 71 "data/maps/PlayerHouse1F/scripts.pory"
	msgbox PlayerHouse1F_Text_BackSoSoon, MSGBOX_DEFAULT
# 72 "data/maps/PlayerHouse1F/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, PlayerHouse1F_Movement_PlayerApproachMom
# 73 "data/maps/PlayerHouse1F/scripts.pory"
	waitmovement 0
# 74 "data/maps/PlayerHouse1F/scripts.pory"
	msgbox PlayerHouse1F_Text_YouHaveAPokemon, MSGBOX_DEFAULT
# 75 "data/maps/PlayerHouse1F/scripts.pory"
	msgbox PlayerHouse1F_Text_GoodToGetOutdoors, MSGBOX_DEFAULT
# 76 "data/maps/PlayerHouse1F/scripts.pory"
	msgbox PlayerHouse1F_Text_UnclesOldEquipment, MSGBOX_DEFAULT
# 77 "data/maps/PlayerHouse1F/scripts.pory"
	msgbox PlayerHouse1F_Text_InquillGym, MSGBOX_DEFAULT
# 78 "data/maps/PlayerHouse1F/scripts.pory"
	msgbox PlayerHouse1F_Text_ExcitedForYou, MSGBOX_DEFAULT
# 79 "data/maps/PlayerHouse1F/scripts.pory"
	msgbox PlayerHouse1F_Text_TakeThese, MSGBOX_DEFAULT
# 80 "data/maps/PlayerHouse1F/scripts.pory"
	setspeaker SP_NAME_NONE
# 81 "data/maps/PlayerHouse1F/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 82 "data/maps/PlayerHouse1F/scripts.pory"
	message PlayerHouse1F_Text_ReceivedRunningShoes
# 83 "data/maps/PlayerHouse1F/scripts.pory"
	waitmessage
# 84 "data/maps/PlayerHouse1F/scripts.pory"
	waitfanfare
# 85 "data/maps/PlayerHouse1F/scripts.pory"
	waitbuttonpress
# 86 "data/maps/PlayerHouse1F/scripts.pory"
	setflag FLAG_RECEIVED_RUNNING_SHOES
# 87 "data/maps/PlayerHouse1F/scripts.pory"
	setflag FLAG_SYS_B_DASH
# 88 "data/maps/PlayerHouse1F/scripts.pory"
	setspeaker SP_NAME_MOM
# 89 "data/maps/PlayerHouse1F/scripts.pory"
	msgbox PlayerHouse1F_Text_DontForgetToVisit, MSGBOX_DEFAULT
# 90 "data/maps/PlayerHouse1F/scripts.pory"
	setvar VAR_ALASIA_INTRO_STATE, 9
# 91 "data/maps/PlayerHouse1F/scripts.pory"
	applymovement LOCALID_MOM, Common_Movement_WalkInPlaceFasterRight
# 92 "data/maps/PlayerHouse1F/scripts.pory"
	waitmovement 0
# 93 "data/maps/PlayerHouse1F/scripts.pory"
	releaseall
# 94 "data/maps/PlayerHouse1F/scripts.pory"
	end
# 95 "data/maps/PlayerHouse1F/scripts.pory"

# 96 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Movement_PlayerApproachMom:
# 97 "data/maps/PlayerHouse1F/scripts.pory"
	walk_up
# 98 "data/maps/PlayerHouse1F/scripts.pory"
	walk_up
# 99 "data/maps/PlayerHouse1F/scripts.pory"
	step_end
# 100 "data/maps/PlayerHouse1F/scripts.pory"

# 101 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Text_LastDayOfSchool:
# 102 "data/maps/PlayerHouse1F/scripts.pory"
	.string "Oh, honey! How was your last day\n"
# 103 "data/maps/PlayerHouse1F/scripts.pory"
	.string "of school?$"
# 104 "data/maps/PlayerHouse1F/scripts.pory"

# 105 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Text_CookiesAndFriendName:
# 106 "data/maps/PlayerHouse1F/scripts.pory"
	.string "I made cookies to celebrate. You\n"
# 107 "data/maps/PlayerHouse1F/scripts.pory"
	.string "should tell your friend to come by,\l"
# 108 "data/maps/PlayerHouse1F/scripts.pory"
	.string "oh…what was her name again?$"
# 109 "data/maps/PlayerHouse1F/scripts.pory"

# 110 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Text_ThatsRight:
# 111 "data/maps/PlayerHouse1F/scripts.pory"
	.string "That’s right, {STR_VAR_1}! I’m too\n"
# 112 "data/maps/PlayerHouse1F/scripts.pory"
	.string "forgetful.$"
# 113 "data/maps/PlayerHouse1F/scripts.pory"

# 114 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Text_UnclesPackage:
# 115 "data/maps/PlayerHouse1F/scripts.pory"
	.string "By the way, your uncle came by\n"
# 116 "data/maps/PlayerHouse1F/scripts.pory"
	.string "earlier and forgot this here. Do you\l"
# 117 "data/maps/PlayerHouse1F/scripts.pory"
	.string "think you could take it to him when\l"
# 118 "data/maps/PlayerHouse1F/scripts.pory"
	.string "you get a chance?\p"
# 119 "data/maps/PlayerHouse1F/scripts.pory"
	.string "I’m sure he would be excited to\n"
# 120 "data/maps/PlayerHouse1F/scripts.pory"
	.string "hear about your school year too. You\l"
# 121 "data/maps/PlayerHouse1F/scripts.pory"
	.string "remember where he lives, don’t you?\p"
# 122 "data/maps/PlayerHouse1F/scripts.pory"
	.string "Up in his cottage at the end of\n"
# 123 "data/maps/PlayerHouse1F/scripts.pory"
	.string "Route 1, on the north end of the\l"
# 124 "data/maps/PlayerHouse1F/scripts.pory"
	.string "lake.$"
# 125 "data/maps/PlayerHouse1F/scripts.pory"

# 126 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Text_UnclesHouseReminder:
# 127 "data/maps/PlayerHouse1F/scripts.pory"
	.string "Your uncle’s house is just at the\n"
# 128 "data/maps/PlayerHouse1F/scripts.pory"
	.string "end of Route 1, to the north. It’s\l"
# 129 "data/maps/PlayerHouse1F/scripts.pory"
	.string "a nice lakefront house.\p"
# 130 "data/maps/PlayerHouse1F/scripts.pory"
	.string "It will be a fun start to your\n"
# 131 "data/maps/PlayerHouse1F/scripts.pory"
	.string "summer vacation!$"
# 132 "data/maps/PlayerHouse1F/scripts.pory"

# 133 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Text_BackSoSoon:
# 134 "data/maps/PlayerHouse1F/scripts.pory"
	.string "Hi honey. Back so soon? I thought\n"
# 135 "data/maps/PlayerHouse1F/scripts.pory"
	.string "you’d spend some time at your\l"
# 136 "data/maps/PlayerHouse1F/scripts.pory"
	.string "uncle’s cottage.$"
# 137 "data/maps/PlayerHouse1F/scripts.pory"

# 138 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Text_YouHaveAPokemon:
# 139 "data/maps/PlayerHouse1F/scripts.pory"
	.string "What is that? Oh my…a Pokémon?\n"
# 140 "data/maps/PlayerHouse1F/scripts.pory"
	.string "Did Professor Sitka give you that?\l"
# 141 "data/maps/PlayerHouse1F/scripts.pory"
	.string "That woman…$"
# 142 "data/maps/PlayerHouse1F/scripts.pory"

# 143 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Text_GoodToGetOutdoors:
# 144 "data/maps/PlayerHouse1F/scripts.pory"
	.string "Well, you are of age. And I suppose\n"
# 145 "data/maps/PlayerHouse1F/scripts.pory"
	.string "it would be good for you to get\l"
# 146 "data/maps/PlayerHouse1F/scripts.pory"
	.string "outdoors this summer.$"
# 147 "data/maps/PlayerHouse1F/scripts.pory"

# 148 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Text_UnclesOldEquipment:
# 149 "data/maps/PlayerHouse1F/scripts.pory"
	.string "I bet your uncle gave you some of\n"
# 150 "data/maps/PlayerHouse1F/scripts.pory"
	.string "his old equipment too. He’s always\l"
# 151 "data/maps/PlayerHouse1F/scripts.pory"
	.string "reminiscing about his old dream to\l"
# 152 "data/maps/PlayerHouse1F/scripts.pory"
	.string "face the gym challenge.$"
# 153 "data/maps/PlayerHouse1F/scripts.pory"

# 154 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Text_InquillGym:
# 155 "data/maps/PlayerHouse1F/scripts.pory"
	.string "So, are you going to do it? There’s\n"
# 156 "data/maps/PlayerHouse1F/scripts.pory"
	.string "a gym just south of here in Inquill\l"
# 157 "data/maps/PlayerHouse1F/scripts.pory"
	.string "Town, that would be a good place to\l"
# 158 "data/maps/PlayerHouse1F/scripts.pory"
	.string "get some practice battling.$"
# 159 "data/maps/PlayerHouse1F/scripts.pory"

# 160 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Text_ExcitedForYou:
# 161 "data/maps/PlayerHouse1F/scripts.pory"
	.string "What, why the shocked face? Did you\n"
# 162 "data/maps/PlayerHouse1F/scripts.pory"
	.string "think I wouldn’t let you? I’m\l"
# 163 "data/maps/PlayerHouse1F/scripts.pory"
	.string "excited for you!$"
# 164 "data/maps/PlayerHouse1F/scripts.pory"

# 165 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Text_TakeThese:
# 166 "data/maps/PlayerHouse1F/scripts.pory"
	.string "Here, before you go, take these.$"
# 167 "data/maps/PlayerHouse1F/scripts.pory"

# 168 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Text_ReceivedRunningShoes:
# 169 "data/maps/PlayerHouse1F/scripts.pory"
	.string "{PLAYER} received the Running Shoes!$"
# 170 "data/maps/PlayerHouse1F/scripts.pory"

# 171 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Text_DontForgetToVisit:
# 172 "data/maps/PlayerHouse1F/scripts.pory"
	.string "Oh, and don’t forget to stop in now\n"
# 173 "data/maps/PlayerHouse1F/scripts.pory"
	.string "and then to say hi to me. I’ll miss\l"
# 174 "data/maps/PlayerHouse1F/scripts.pory"
	.string "you.$"
# 175 "data/maps/PlayerHouse1F/scripts.pory"

# 176 "data/maps/PlayerHouse1F/scripts.pory"
PlayerHouse1F_Text_AdventureCheckIn:
# 177 "data/maps/PlayerHouse1F/scripts.pory"
	.string "{PLAYER}! How is your adventure\n"
# 178 "data/maps/PlayerHouse1F/scripts.pory"
	.string "going, dear?\p"
# 179 "data/maps/PlayerHouse1F/scripts.pory"
	.string "Your bed downstairs will always be\n"
# 180 "data/maps/PlayerHouse1F/scripts.pory"
	.string "made and ready for you if you need\l"
# 181 "data/maps/PlayerHouse1F/scripts.pory"
	.string "a rest.$"
