# 1 "data/maps/TrainerSchool/scripts.pory"

# 2 "data/maps/TrainerSchool/scripts.pory"
TrainerSchool_MapScripts::
# 3 "data/maps/TrainerSchool/scripts.pory"
	.byte 0

TrainerSchool_EventScript_Starter1::
# 7 "data/maps/TrainerSchool/scripts.pory"
	lockall
# 8 "data/maps/TrainerSchool/scripts.pory"
	showmonpic SPECIES_TOTODILE, 10, 3
# 9 "data/maps/TrainerSchool/scripts.pory"
	msgbox TrainerSchool_EventScript_Starter1_Text_0, MSGBOX_YESNO
# 10 "data/maps/TrainerSchool/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq TrainerSchool_EventScript_Starter1_2
TrainerSchool_EventScript_Starter1_1:
# 24 "data/maps/TrainerSchool/scripts.pory"
	waitmessage
# 25 "data/maps/TrainerSchool/scripts.pory"
	releaseall
	end

TrainerSchool_EventScript_Starter1_2:
# 11 "data/maps/TrainerSchool/scripts.pory"
	givemon SPECIES_TOTODILE, 5, ITEM_POKE_BALL
# 12 "data/maps/TrainerSchool/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq TrainerSchool_EventScript_Starter1_4
# 20 "data/maps/TrainerSchool/scripts.pory"
	hidemonpic
# 21 "data/maps/TrainerSchool/scripts.pory"
	msgbox TrainerSchool_NotChosen
	goto TrainerSchool_EventScript_Starter1_1

TrainerSchool_EventScript_Starter1_4:
# 13 "data/maps/TrainerSchool/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 14 "data/maps/TrainerSchool/scripts.pory"
	msgbox TrainerSchool_EventScript_Starter1_Text_1
# 15 "data/maps/TrainerSchool/scripts.pory"
	removeobject 1
# 16 "data/maps/TrainerSchool/scripts.pory"
	setflag VAR_UNUSED_0x40F7
# 17 "data/maps/TrainerSchool/scripts.pory"
	call NicknamePartyMon
	goto TrainerSchool_EventScript_Starter1_1


TrainerSchool_EventScript_Starter2::
# 30 "data/maps/TrainerSchool/scripts.pory"
	lockall
# 31 "data/maps/TrainerSchool/scripts.pory"
	showmonpic SPECIES_CHIKORITA, 10, 3
# 32 "data/maps/TrainerSchool/scripts.pory"
	msgbox TrainerSchool_EventScript_Starter2_Text_0, MSGBOX_YESNO
# 33 "data/maps/TrainerSchool/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq TrainerSchool_EventScript_Starter2_2
TrainerSchool_EventScript_Starter2_1:
# 47 "data/maps/TrainerSchool/scripts.pory"
	waitmessage
# 48 "data/maps/TrainerSchool/scripts.pory"
	releaseall
	end

TrainerSchool_EventScript_Starter2_2:
# 34 "data/maps/TrainerSchool/scripts.pory"
	givemon SPECIES_CHIKORITA, 5, ITEM_POKE_BALL
# 35 "data/maps/TrainerSchool/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq TrainerSchool_EventScript_Starter2_4
# 43 "data/maps/TrainerSchool/scripts.pory"
	hidemonpic
# 44 "data/maps/TrainerSchool/scripts.pory"
	msgbox TrainerSchool_NotChosen
	goto TrainerSchool_EventScript_Starter2_1

TrainerSchool_EventScript_Starter2_4:
# 36 "data/maps/TrainerSchool/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 37 "data/maps/TrainerSchool/scripts.pory"
	msgbox TrainerSchool_EventScript_Starter2_Text_1
# 38 "data/maps/TrainerSchool/scripts.pory"
	removeobject 2
# 39 "data/maps/TrainerSchool/scripts.pory"
	setflag VAR_UNUSED_0x40F7
# 40 "data/maps/TrainerSchool/scripts.pory"
	call NicknamePartyMon
	goto TrainerSchool_EventScript_Starter2_1


TrainerSchool_EventScript_Starter3::
# 53 "data/maps/TrainerSchool/scripts.pory"
	lockall
# 54 "data/maps/TrainerSchool/scripts.pory"
	showmonpic SPECIES_CYNDAQUIL, 10, 3
# 55 "data/maps/TrainerSchool/scripts.pory"
	msgbox TrainerSchool_EventScript_Starter3_Text_0, MSGBOX_YESNO
# 56 "data/maps/TrainerSchool/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq TrainerSchool_EventScript_Starter3_2
TrainerSchool_EventScript_Starter3_1:
# 70 "data/maps/TrainerSchool/scripts.pory"
	waitmessage
# 71 "data/maps/TrainerSchool/scripts.pory"
	releaseall
	end

TrainerSchool_EventScript_Starter3_2:
# 57 "data/maps/TrainerSchool/scripts.pory"
	givemon SPECIES_CYNDAQUIL, 5, ITEM_POKE_BALL
# 58 "data/maps/TrainerSchool/scripts.pory"
	compare VAR_RESULT, MON_GIVEN_TO_PARTY
	goto_if_eq TrainerSchool_EventScript_Starter3_4
# 66 "data/maps/TrainerSchool/scripts.pory"
	hidemonpic
# 67 "data/maps/TrainerSchool/scripts.pory"
	msgbox TrainerSchool_NotChosen
	goto TrainerSchool_EventScript_Starter3_1

TrainerSchool_EventScript_Starter3_4:
# 59 "data/maps/TrainerSchool/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 60 "data/maps/TrainerSchool/scripts.pory"
	msgbox TrainerSchool_EventScript_Starter3_Text_1
# 61 "data/maps/TrainerSchool/scripts.pory"
	removeobject 3
# 62 "data/maps/TrainerSchool/scripts.pory"
	setflag VAR_UNUSED_0x40F7
# 63 "data/maps/TrainerSchool/scripts.pory"
	call NicknamePartyMon
	goto TrainerSchool_EventScript_Starter3_1


NicknamePartyMon::
# 78 "data/maps/TrainerSchool/scripts.pory"
	msgbox NicknamePartyMon_Text_0, MSGBOX_YESNO
# 79 "data/maps/TrainerSchool/scripts.pory"
	hidemonpic
# 80 "data/maps/TrainerSchool/scripts.pory"
	compare VAR_RESULT, YES
	goto_if_eq NicknamePartyMon_1
	return

NicknamePartyMon_1:
# 81 "data/maps/TrainerSchool/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 82 "data/maps/TrainerSchool/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
	return


TrainerSchool_EventScript_Starter1_Text_0:
# 9 "data/maps/TrainerSchool/scripts.pory"
	.string "Do you want to choose Totodile?$"

TrainerSchool_EventScript_Starter1_Text_1:
# 14 "data/maps/TrainerSchool/scripts.pory"
	.string "Received Totodile!$"

TrainerSchool_EventScript_Starter2_Text_0:
# 32 "data/maps/TrainerSchool/scripts.pory"
	.string "Do you want to choose Chikorita?$"

TrainerSchool_EventScript_Starter2_Text_1:
# 37 "data/maps/TrainerSchool/scripts.pory"
	.string "Received Chikorita!$"

TrainerSchool_EventScript_Starter3_Text_0:
# 55 "data/maps/TrainerSchool/scripts.pory"
	.string "Do you want to choose Cyndaquil?$"

TrainerSchool_EventScript_Starter3_Text_1:
# 60 "data/maps/TrainerSchool/scripts.pory"
	.string "Received Cyndaquil!$"

NicknamePartyMon_Text_0:
# 78 "data/maps/TrainerSchool/scripts.pory"
	.string "Give it a nickname?$"

TrainerSchool_NotChosen::
# 85 "data/maps/TrainerSchool/scripts.pory"
	.string "You did not choose this Pokemon.$"
