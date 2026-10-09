# 1 "data/maps/SitkaLab/scripts.pory"

# 2 "data/maps/SitkaLab/scripts.pory"
.set LOCALID_SITKA, LOCALID_SITKA_LAB_PROFESSOR
# 3 "data/maps/SitkaLab/scripts.pory"
.set LOCALID_SPHEAL, LOCALID_SITKA_LAB_SPHEAL
# 4 "data/maps/SitkaLab/scripts.pory"
.set LOCALID_SANDILE, LOCALID_SITKA_LAB_SANDILE
# 5 "data/maps/SitkaLab/scripts.pory"
.set LOCALID_MAREEP, LOCALID_SITKA_LAB_MAREEP
# 6 "data/maps/SitkaLab/scripts.pory"
.set LOCALID_APRIL, LOCALID_SITKA_LAB_APRIL
# 7 "data/maps/SitkaLab/scripts.pory"

# 8 "data/maps/SitkaLab/scripts.pory"
SitkaLab_MapScripts::
# 9 "data/maps/SitkaLab/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, SitkaLab_OnTransition
# 10 "data/maps/SitkaLab/scripts.pory"
	map_script MAP_SCRIPT_ON_FRAME_TABLE, SitkaLab_OnFrame
# 11 "data/maps/SitkaLab/scripts.pory"
	.byte 0
# 12 "data/maps/SitkaLab/scripts.pory"

# 13 "data/maps/SitkaLab/scripts.pory"
SitkaLab_OnTransition:
# 14 "data/maps/SitkaLab/scripts.pory"
	call_if_eq VAR_ALASIA_INTRO_STATE, 4, SitkaLab_EventScript_PrepareArrival
# 15 "data/maps/SitkaLab/scripts.pory"
	call_if_ge VAR_ALASIA_INTRO_STATE, 7, SitkaLab_EventScript_HideAprilAfterBattle
# 16 "data/maps/SitkaLab/scripts.pory"
	end
# 17 "data/maps/SitkaLab/scripts.pory"

# 18 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_PrepareArrival:
# 19 "data/maps/SitkaLab/scripts.pory"
	setflag FLAG_HIDE_SITKA_LAB_APRIL
# 20 "data/maps/SitkaLab/scripts.pory"
	return
# 21 "data/maps/SitkaLab/scripts.pory"

# 22 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_HideAprilAfterBattle:
# 23 "data/maps/SitkaLab/scripts.pory"
	setflag FLAG_HIDE_SITKA_LAB_APRIL
# 24 "data/maps/SitkaLab/scripts.pory"
	return
# 25 "data/maps/SitkaLab/scripts.pory"

# 26 "data/maps/SitkaLab/scripts.pory"
SitkaLab_OnFrame:
# 27 "data/maps/SitkaLab/scripts.pory"
	map_script_2 VAR_ALASIA_INTRO_STATE, 4, SitkaLab_EventScript_Arrival
# 28 "data/maps/SitkaLab/scripts.pory"
	.2byte 0
# 29 "data/maps/SitkaLab/scripts.pory"

# 30 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_Arrival::
# 31 "data/maps/SitkaLab/scripts.pory"
	lockall
# 32 "data/maps/SitkaLab/scripts.pory"
	applymovement OBJ_EVENT_ID_PLAYER, SitkaLab_Movement_PlayerApproach
# 33 "data/maps/SitkaLab/scripts.pory"
	waitmovement 0
# 34 "data/maps/SitkaLab/scripts.pory"
	setobjectxyperm LOCALID_APRIL, 5, 10
# 35 "data/maps/SitkaLab/scripts.pory"
	clearflag FLAG_HIDE_SITKA_LAB_APRIL
# 36 "data/maps/SitkaLab/scripts.pory"
	addobject LOCALID_APRIL
# 37 "data/maps/SitkaLab/scripts.pory"
	opendoor 5, 10
# 38 "data/maps/SitkaLab/scripts.pory"
	waitdooranim
# 39 "data/maps/SitkaLab/scripts.pory"
	applymovement LOCALID_APRIL, SitkaLab_Movement_AprilEnter
# 40 "data/maps/SitkaLab/scripts.pory"
	waitmovement 0
# 41 "data/maps/SitkaLab/scripts.pory"
	closedoor 5, 10
# 42 "data/maps/SitkaLab/scripts.pory"
	waitdooranim
# 43 "data/maps/SitkaLab/scripts.pory"
	applymovement LOCALID_APRIL, Common_Movement_ExclamationMark
# 44 "data/maps/SitkaLab/scripts.pory"
	waitmovement 0
# 45 "data/maps/SitkaLab/scripts.pory"
	applymovement LOCALID_APRIL, SitkaLab_Movement_AprilRunToPokemon
# 46 "data/maps/SitkaLab/scripts.pory"
	waitmovement 0
# 47 "data/maps/SitkaLab/scripts.pory"
	special BufferAprilName
# 48 "data/maps/SitkaLab/scripts.pory"
	setspeaker SitkaLab_Text_AprilSpeakerName
# 49 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_NoWayAreThese, MSGBOX_DEFAULT
# 50 "data/maps/SitkaLab/scripts.pory"
	setspeaker SP_NAME_PROFESSOR_SITKA
# 51 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_TheyArePokemon, MSGBOX_DEFAULT
# 52 "data/maps/SitkaLab/scripts.pory"
	special BufferPlayerSubjectPronoun
# 53 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_GrassWasDangerous, MSGBOX_DEFAULT
# 54 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_GiveYouPokemon, MSGBOX_DEFAULT
# 55 "data/maps/SitkaLab/scripts.pory"
	special BufferAprilName
# 56 "data/maps/SitkaLab/scripts.pory"
	setspeaker SitkaLab_Text_AprilSpeakerName
# 57 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_AprilSoCool, MSGBOX_DEFAULT
# 58 "data/maps/SitkaLab/scripts.pory"
	setspeaker SP_NAME_PROFESSOR_SITKA
# 59 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ChooseFromTable, MSGBOX_DEFAULT
# 60 "data/maps/SitkaLab/scripts.pory"
	applymovement LOCALID_APRIL, SitkaLab_Movement_AprilWaitByTable
# 61 "data/maps/SitkaLab/scripts.pory"
	waitmovement 0
# 62 "data/maps/SitkaLab/scripts.pory"
	setvar VAR_ALASIA_INTRO_STATE, 5
# 63 "data/maps/SitkaLab/scripts.pory"
	releaseall
# 64 "data/maps/SitkaLab/scripts.pory"
	end
# 65 "data/maps/SitkaLab/scripts.pory"

# 66 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_BlockWarp::
# 67 "data/maps/SitkaLab/scripts.pory"
	lockall
# 68 "data/maps/SitkaLab/scripts.pory"
	special BufferAprilName
# 69 "data/maps/SitkaLab/scripts.pory"
	setspeaker SitkaLab_Text_AprilSpeakerName
# 70 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_PickAPokemonReminder, MSGBOX_DEFAULT
# 71 "data/maps/SitkaLab/scripts.pory"
	releaseall
# 72 "data/maps/SitkaLab/scripts.pory"
	end
# 73 "data/maps/SitkaLab/scripts.pory"

# 74 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_Professor::
# 75 "data/maps/SitkaLab/scripts.pory"
	lock
# 76 "data/maps/SitkaLab/scripts.pory"
	faceplayer
# 77 "data/maps/SitkaLab/scripts.pory"
	setspeaker SP_NAME_PROFESSOR_SITKA
# 78 "data/maps/SitkaLab/scripts.pory"
	goto_if_eq VAR_ALASIA_INTRO_STATE, 5, SitkaLab_EventScript_ProfessorChooseReminder
# 79 "data/maps/SitkaLab/scripts.pory"
	goto_if_ge VAR_ALASIA_INTRO_STATE, 7, SitkaLab_EventScript_ProfessorCheckPartyHealth
# 80 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ProfessorAfterStarter, MSGBOX_DEFAULT
# 81 "data/maps/SitkaLab/scripts.pory"
	release
# 82 "data/maps/SitkaLab/scripts.pory"
	end
# 83 "data/maps/SitkaLab/scripts.pory"

# 84 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_ProfessorCheckPartyHealth::
# 85 "data/maps/SitkaLab/scripts.pory"
	specialvar VAR_RESULT, DoesPlayerPartyNeedHealing
# 86 "data/maps/SitkaLab/scripts.pory"
	goto_if_eq VAR_RESULT, TRUE, SitkaLab_EventScript_ProfessorHealParty
# 87 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ProfessorPartyHealthy, MSGBOX_DEFAULT
# 88 "data/maps/SitkaLab/scripts.pory"
	release
# 89 "data/maps/SitkaLab/scripts.pory"
	end
# 90 "data/maps/SitkaLab/scripts.pory"

# 91 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_ProfessorHealParty::
# 92 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ProfessorPartyTired, MSGBOX_DEFAULT
# 93 "data/maps/SitkaLab/scripts.pory"
	closemessage
# 94 "data/maps/SitkaLab/scripts.pory"
	fadescreen FADE_TO_BLACK
# 95 "data/maps/SitkaLab/scripts.pory"
	special HealPlayerParty
# 96 "data/maps/SitkaLab/scripts.pory"
	playfanfare MUS_HEAL
# 97 "data/maps/SitkaLab/scripts.pory"
	waitfanfare
# 98 "data/maps/SitkaLab/scripts.pory"
	fadescreen FADE_FROM_BLACK
# 99 "data/maps/SitkaLab/scripts.pory"
	release
# 100 "data/maps/SitkaLab/scripts.pory"
	end
# 101 "data/maps/SitkaLab/scripts.pory"

# 102 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_ProfessorChooseReminder::
# 103 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ChooseFromTable, MSGBOX_DEFAULT
# 104 "data/maps/SitkaLab/scripts.pory"
	release
# 105 "data/maps/SitkaLab/scripts.pory"
	end
# 106 "data/maps/SitkaLab/scripts.pory"

# 107 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_April::
# 108 "data/maps/SitkaLab/scripts.pory"
	lock
# 109 "data/maps/SitkaLab/scripts.pory"
	faceplayer
# 110 "data/maps/SitkaLab/scripts.pory"
	special BufferAprilName
# 111 "data/maps/SitkaLab/scripts.pory"
	setspeaker SitkaLab_Text_AprilSpeakerName
# 112 "data/maps/SitkaLab/scripts.pory"
	goto_if_eq VAR_ALASIA_INTRO_STATE, 5, SitkaLab_EventScript_AprilChooseReminder
# 113 "data/maps/SitkaLab/scripts.pory"
	goto_if_eq VAR_STARTER_MON, 0, SitkaLab_EventScript_AprilComplimentsSpheal
# 114 "data/maps/SitkaLab/scripts.pory"
	goto_if_eq VAR_STARTER_MON, 1, SitkaLab_EventScript_AprilComplimentsSandile
# 115 "data/maps/SitkaLab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_MAREEP
# 116 "data/maps/SitkaLab/scripts.pory"
	goto SitkaLab_EventScript_AprilComplimentsStarter
# 117 "data/maps/SitkaLab/scripts.pory"

# 118 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_AprilComplimentsSpheal::
# 119 "data/maps/SitkaLab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_SPHEAL
# 120 "data/maps/SitkaLab/scripts.pory"
	goto SitkaLab_EventScript_AprilComplimentsStarter
# 121 "data/maps/SitkaLab/scripts.pory"

# 122 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_AprilComplimentsSandile::
# 123 "data/maps/SitkaLab/scripts.pory"
	bufferspeciesname STR_VAR_2, SPECIES_SANDILE
# 124 "data/maps/SitkaLab/scripts.pory"

# 125 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_AprilComplimentsStarter::
# 126 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_AprilAfterStarter, MSGBOX_DEFAULT
# 127 "data/maps/SitkaLab/scripts.pory"
	release
# 128 "data/maps/SitkaLab/scripts.pory"
	end
# 129 "data/maps/SitkaLab/scripts.pory"

# 130 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_AprilChooseReminder::
# 131 "data/maps/SitkaLab/scripts.pory"
	special BufferAprilName
# 132 "data/maps/SitkaLab/scripts.pory"
	setspeaker SitkaLab_Text_AprilSpeakerName
# 133 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_PickAPokemonReminder, MSGBOX_DEFAULT
# 134 "data/maps/SitkaLab/scripts.pory"
	release
# 135 "data/maps/SitkaLab/scripts.pory"
	end
# 136 "data/maps/SitkaLab/scripts.pory"

# 137 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_ChooseSpheal::
# 138 "data/maps/SitkaLab/scripts.pory"
	lockall
# 139 "data/maps/SitkaLab/scripts.pory"
	goto_if_ne VAR_ALASIA_INTRO_STATE, 5, SitkaLab_EventScript_RemainingPokemon
# 140 "data/maps/SitkaLab/scripts.pory"
	showmonpic SPECIES_SPHEAL, 10, 3
# 141 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ChooseSpheal, MSGBOX_YESNO
# 142 "data/maps/SitkaLab/scripts.pory"
	hidemonpic
# 143 "data/maps/SitkaLab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, SitkaLab_EventScript_TakeSpheal
# 144 "data/maps/SitkaLab/scripts.pory"
	releaseall
# 145 "data/maps/SitkaLab/scripts.pory"
	end
# 146 "data/maps/SitkaLab/scripts.pory"

# 147 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_TakeSpheal::
# 148 "data/maps/SitkaLab/scripts.pory"
	setvar VAR_STARTER_MON, 0
# 149 "data/maps/SitkaLab/scripts.pory"
	givemon SPECIES_SPHEAL, 5, nature=NATURE_RANDOM, abilityNum=0, gender=MON_GENDER_RANDOM, shinyMode=SHINY_MODE_RANDOM
# 150 "data/maps/SitkaLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 151 "data/maps/SitkaLab/scripts.pory"
	setflag FLAG_HIDE_SITKA_LAB_SPHEAL
# 152 "data/maps/SitkaLab/scripts.pory"
	removeobject LOCALID_SPHEAL
# 153 "data/maps/SitkaLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 154 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ReceivedSpheal, MSGBOX_DEFAULT
# 155 "data/maps/SitkaLab/scripts.pory"
	waitfanfare
# 156 "data/maps/SitkaLab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_SPHEAL
# 157 "data/maps/SitkaLab/scripts.pory"
	goto SitkaLab_EventScript_OfferStarterNickname
# 158 "data/maps/SitkaLab/scripts.pory"

# 159 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_ChooseSandile::
# 160 "data/maps/SitkaLab/scripts.pory"
	lockall
# 161 "data/maps/SitkaLab/scripts.pory"
	goto_if_ne VAR_ALASIA_INTRO_STATE, 5, SitkaLab_EventScript_RemainingPokemon
# 162 "data/maps/SitkaLab/scripts.pory"
	showmonpic SPECIES_SANDILE, 10, 3
# 163 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ChooseSandile, MSGBOX_YESNO
# 164 "data/maps/SitkaLab/scripts.pory"
	hidemonpic
# 165 "data/maps/SitkaLab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, SitkaLab_EventScript_TakeSandile
# 166 "data/maps/SitkaLab/scripts.pory"
	releaseall
# 167 "data/maps/SitkaLab/scripts.pory"
	end
# 168 "data/maps/SitkaLab/scripts.pory"

# 169 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_TakeSandile::
# 170 "data/maps/SitkaLab/scripts.pory"
	setvar VAR_STARTER_MON, 1
# 171 "data/maps/SitkaLab/scripts.pory"
	givemon SPECIES_SANDILE, 5, nature=NATURE_RANDOM, abilityNum=0, gender=MON_GENDER_RANDOM, shinyMode=SHINY_MODE_RANDOM
# 172 "data/maps/SitkaLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 173 "data/maps/SitkaLab/scripts.pory"
	setflag FLAG_HIDE_SITKA_LAB_SANDILE
# 174 "data/maps/SitkaLab/scripts.pory"
	removeobject LOCALID_SANDILE
# 175 "data/maps/SitkaLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 176 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ReceivedSandile, MSGBOX_DEFAULT
# 177 "data/maps/SitkaLab/scripts.pory"
	waitfanfare
# 178 "data/maps/SitkaLab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_SANDILE
# 179 "data/maps/SitkaLab/scripts.pory"
	goto SitkaLab_EventScript_OfferStarterNickname
# 180 "data/maps/SitkaLab/scripts.pory"

# 181 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_ChooseMareep::
# 182 "data/maps/SitkaLab/scripts.pory"
	lockall
# 183 "data/maps/SitkaLab/scripts.pory"
	goto_if_ne VAR_ALASIA_INTRO_STATE, 5, SitkaLab_EventScript_RemainingPokemon
# 184 "data/maps/SitkaLab/scripts.pory"
	showmonpic SPECIES_MAREEP, 10, 3
# 185 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ChooseMareep, MSGBOX_YESNO
# 186 "data/maps/SitkaLab/scripts.pory"
	hidemonpic
# 187 "data/maps/SitkaLab/scripts.pory"
	goto_if_eq VAR_RESULT, YES, SitkaLab_EventScript_TakeMareep
# 188 "data/maps/SitkaLab/scripts.pory"
	releaseall
# 189 "data/maps/SitkaLab/scripts.pory"
	end
# 190 "data/maps/SitkaLab/scripts.pory"

# 191 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_TakeMareep::
# 192 "data/maps/SitkaLab/scripts.pory"
	setvar VAR_STARTER_MON, 2
# 193 "data/maps/SitkaLab/scripts.pory"
	givemon SPECIES_MAREEP, 5, nature=NATURE_RANDOM, abilityNum=0, gender=MON_GENDER_RANDOM, shinyMode=SHINY_MODE_RANDOM
# 194 "data/maps/SitkaLab/scripts.pory"
	setflag FLAG_SYS_POKEMON_GET
# 195 "data/maps/SitkaLab/scripts.pory"
	setflag FLAG_HIDE_SITKA_LAB_MAREEP
# 196 "data/maps/SitkaLab/scripts.pory"
	removeobject LOCALID_MAREEP
# 197 "data/maps/SitkaLab/scripts.pory"
	playfanfare MUS_OBTAIN_ITEM
# 198 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ReceivedMareep, MSGBOX_DEFAULT
# 199 "data/maps/SitkaLab/scripts.pory"
	waitfanfare
# 200 "data/maps/SitkaLab/scripts.pory"
	bufferspeciesname STR_VAR_1, SPECIES_MAREEP
# 201 "data/maps/SitkaLab/scripts.pory"

# 202 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_OfferStarterNickname::
# 203 "data/maps/SitkaLab/scripts.pory"
	msgbox gText_NicknameThisPokemon, MSGBOX_YESNO
# 204 "data/maps/SitkaLab/scripts.pory"
	goto_if_eq VAR_RESULT, NO, SitkaLab_EventScript_AfterPlayerChooses
# 205 "data/maps/SitkaLab/scripts.pory"
	call Common_EventScript_GetGiftMonPartySlot
# 206 "data/maps/SitkaLab/scripts.pory"
	call Common_EventScript_NameReceivedPartyMon
# 207 "data/maps/SitkaLab/scripts.pory"
	goto SitkaLab_EventScript_AfterPlayerChooses
# 208 "data/maps/SitkaLab/scripts.pory"

# 209 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_RemainingPokemon::
# 210 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_RemainingPokemon, MSGBOX_DEFAULT
# 211 "data/maps/SitkaLab/scripts.pory"
	releaseall
# 212 "data/maps/SitkaLab/scripts.pory"
	end
# 213 "data/maps/SitkaLab/scripts.pory"

# 214 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_AfterPlayerChooses::
# 215 "data/maps/SitkaLab/scripts.pory"
	special BufferAprilName
# 216 "data/maps/SitkaLab/scripts.pory"
	setspeaker SitkaLab_Text_AprilSpeakerName
# 217 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_AprilNotFair, MSGBOX_DEFAULT
# 218 "data/maps/SitkaLab/scripts.pory"
	setspeaker SP_NAME_PROFESSOR_SITKA
# 219 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ProfessorHmm, MSGBOX_DEFAULT
# 220 "data/maps/SitkaLab/scripts.pory"
	applymovement LOCALID_SITKA, Common_Movement_WalkInPlaceFasterUp
# 221 "data/maps/SitkaLab/scripts.pory"
	waitmovement 0
# 222 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ProfessorWhatTheHeck, MSGBOX_DEFAULT
# 223 "data/maps/SitkaLab/scripts.pory"
	applymovement LOCALID_SITKA, Common_Movement_WalkInPlaceFasterDown
# 224 "data/maps/SitkaLab/scripts.pory"
	waitmovement 0
# 225 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ProfessorOffersApril, MSGBOX_DEFAULT
# 226 "data/maps/SitkaLab/scripts.pory"
	special BufferAprilName
# 227 "data/maps/SitkaLab/scripts.pory"
	setspeaker SitkaLab_Text_AprilSpeakerName
# 228 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_AprilSerious, MSGBOX_DEFAULT
# 229 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_AprilChooses, MSGBOX_DEFAULT
# 230 "data/maps/SitkaLab/scripts.pory"
	goto_if_eq VAR_STARTER_MON, 0, SitkaLab_EventScript_AprilTakesMareep
# 231 "data/maps/SitkaLab/scripts.pory"
	goto_if_eq VAR_STARTER_MON, 1, SitkaLab_EventScript_AprilTakesSpheal
# 232 "data/maps/SitkaLab/scripts.pory"

# 233 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_AprilTakesSandile::
# 234 "data/maps/SitkaLab/scripts.pory"
	applymovement LOCALID_APRIL, SitkaLab_Movement_AprilChooseSandile
# 235 "data/maps/SitkaLab/scripts.pory"
	waitmovement 0
# 236 "data/maps/SitkaLab/scripts.pory"
	setvar VAR_APRIL_STARTER, SPECIES_SANDILE
# 237 "data/maps/SitkaLab/scripts.pory"
	setflag FLAG_HIDE_SITKA_LAB_SANDILE
# 238 "data/maps/SitkaLab/scripts.pory"
	removeobject LOCALID_SANDILE
# 239 "data/maps/SitkaLab/scripts.pory"
	goto SitkaLab_EventScript_StarterLecture
# 240 "data/maps/SitkaLab/scripts.pory"

# 241 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_AprilTakesMareep::
# 242 "data/maps/SitkaLab/scripts.pory"
	applymovement LOCALID_APRIL, SitkaLab_Movement_AprilChooseMareep
# 243 "data/maps/SitkaLab/scripts.pory"
	waitmovement 0
# 244 "data/maps/SitkaLab/scripts.pory"
	setvar VAR_APRIL_STARTER, SPECIES_MAREEP
# 245 "data/maps/SitkaLab/scripts.pory"
	setflag FLAG_HIDE_SITKA_LAB_MAREEP
# 246 "data/maps/SitkaLab/scripts.pory"
	removeobject LOCALID_MAREEP
# 247 "data/maps/SitkaLab/scripts.pory"
	goto SitkaLab_EventScript_StarterLecture
# 248 "data/maps/SitkaLab/scripts.pory"

# 249 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_AprilTakesSpheal::
# 250 "data/maps/SitkaLab/scripts.pory"
	applymovement LOCALID_APRIL, SitkaLab_Movement_AprilChooseSpheal
# 251 "data/maps/SitkaLab/scripts.pory"
	waitmovement 0
# 252 "data/maps/SitkaLab/scripts.pory"
	setvar VAR_APRIL_STARTER, SPECIES_SPHEAL
# 253 "data/maps/SitkaLab/scripts.pory"
	setflag FLAG_HIDE_SITKA_LAB_SPHEAL
# 254 "data/maps/SitkaLab/scripts.pory"
	removeobject LOCALID_SPHEAL
# 255 "data/maps/SitkaLab/scripts.pory"

# 256 "data/maps/SitkaLab/scripts.pory"
SitkaLab_EventScript_StarterLecture::
# 257 "data/maps/SitkaLab/scripts.pory"
	setspeaker SP_NAME_PROFESSOR_SITKA
# 258 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ProfessorTrouble, MSGBOX_DEFAULT
# 259 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ProfessorResponsibility, MSGBOX_DEFAULT
# 260 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ProfessorTallGrass, MSGBOX_DEFAULT
# 261 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ProfessorBeCareful, MSGBOX_DEFAULT
# 262 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_ProfessorGreatSummer, MSGBOX_DEFAULT
# 263 "data/maps/SitkaLab/scripts.pory"
	special BufferAprilName
# 264 "data/maps/SitkaLab/scripts.pory"
	setspeaker SitkaLab_Text_AprilSpeakerName
# 265 "data/maps/SitkaLab/scripts.pory"
	msgbox SitkaLab_Text_AprilWontLetDown, MSGBOX_DEFAULT
# 266 "data/maps/SitkaLab/scripts.pory"
	setvar VAR_ALASIA_INTRO_STATE, 6
# 267 "data/maps/SitkaLab/scripts.pory"
	releaseall
# 268 "data/maps/SitkaLab/scripts.pory"
	end
# 269 "data/maps/SitkaLab/scripts.pory"

# 270 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Movement_PlayerApproach:
# 271 "data/maps/SitkaLab/scripts.pory"
	walk_up
# 272 "data/maps/SitkaLab/scripts.pory"
	walk_up
# 273 "data/maps/SitkaLab/scripts.pory"
	walk_up
# 274 "data/maps/SitkaLab/scripts.pory"
	step_end
# 275 "data/maps/SitkaLab/scripts.pory"

# 276 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Movement_AprilEnter:
# 277 "data/maps/SitkaLab/scripts.pory"
	walk_up
# 278 "data/maps/SitkaLab/scripts.pory"
	step_end
# 279 "data/maps/SitkaLab/scripts.pory"

# 280 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Movement_AprilRunToPokemon:
# 281 "data/maps/SitkaLab/scripts.pory"
	walk_fast_left
# 282 "data/maps/SitkaLab/scripts.pory"
	walk_fast_left
# 283 "data/maps/SitkaLab/scripts.pory"
	walk_fast_up
# 284 "data/maps/SitkaLab/scripts.pory"
	walk_fast_up
# 285 "data/maps/SitkaLab/scripts.pory"
	walk_fast_up
# 286 "data/maps/SitkaLab/scripts.pory"
	face_up
# 287 "data/maps/SitkaLab/scripts.pory"
	step_end
# 288 "data/maps/SitkaLab/scripts.pory"

# 289 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Movement_AprilWaitByTable:
# 290 "data/maps/SitkaLab/scripts.pory"
	walk_left
# 291 "data/maps/SitkaLab/scripts.pory"
	walk_left
# 292 "data/maps/SitkaLab/scripts.pory"
	face_right
# 293 "data/maps/SitkaLab/scripts.pory"
	step_end
# 294 "data/maps/SitkaLab/scripts.pory"

# 295 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Movement_AprilChooseMareep:
# 296 "data/maps/SitkaLab/scripts.pory"
	walk_right
# 297 "data/maps/SitkaLab/scripts.pory"
	walk_up
# 298 "data/maps/SitkaLab/scripts.pory"
	face_up
# 299 "data/maps/SitkaLab/scripts.pory"
	step_end
# 300 "data/maps/SitkaLab/scripts.pory"

# 301 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Movement_AprilChooseSandile:
# 302 "data/maps/SitkaLab/scripts.pory"
	walk_right
# 303 "data/maps/SitkaLab/scripts.pory"
	walk_right
# 304 "data/maps/SitkaLab/scripts.pory"
	walk_up
# 305 "data/maps/SitkaLab/scripts.pory"
	face_up
# 306 "data/maps/SitkaLab/scripts.pory"
	step_end
# 307 "data/maps/SitkaLab/scripts.pory"

# 308 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Movement_AprilChooseSpheal:
# 309 "data/maps/SitkaLab/scripts.pory"
	walk_right
# 310 "data/maps/SitkaLab/scripts.pory"
	walk_right
# 311 "data/maps/SitkaLab/scripts.pory"
	walk_right
# 312 "data/maps/SitkaLab/scripts.pory"
	walk_up
# 313 "data/maps/SitkaLab/scripts.pory"
	face_up
# 314 "data/maps/SitkaLab/scripts.pory"
	step_end
# 315 "data/maps/SitkaLab/scripts.pory"

# 316 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_NoWayAreThese:
# 317 "data/maps/SitkaLab/scripts.pory"
	.string "No way…are these…?$"
# 318 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_AprilSpeakerName:
# 319 "data/maps/SitkaLab/scripts.pory"
	.string "{STR_VAR_1}$"
# 320 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_TheyArePokemon:
# 321 "data/maps/SitkaLab/scripts.pory"
	.string "Yes. They’re Pokémon.$"
# 322 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_GrassWasDangerous:
# 323 "data/maps/SitkaLab/scripts.pory"
	.string "Your friend here was trying to\n"
# 324 "data/maps/SitkaLab/scripts.pory"
	.string "enter the tall grass on their own.\l"
# 325 "data/maps/SitkaLab/scripts.pory"
	.string "{STR_VAR_2} would have been defenceless\l"
# 326 "data/maps/SitkaLab/scripts.pory"
	.string "if a wild Pokémon attacked.$"
# 327 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_GiveYouPokemon:
# 328 "data/maps/SitkaLab/scripts.pory"
	.string "So…{PLAYER}, I’m going to give you\n"
# 329 "data/maps/SitkaLab/scripts.pory"
	.string "your own Pokémon. You’re old enough\l"
# 330 "data/maps/SitkaLab/scripts.pory"
	.string "now, and with a partner by your side\l"
# 331 "data/maps/SitkaLab/scripts.pory"
	.string "you’ll be able to explore lots this\l"
# 332 "data/maps/SitkaLab/scripts.pory"
	.string "summer.$"
# 333 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_AprilSoCool:
# 334 "data/maps/SitkaLab/scripts.pory"
	.string "NO WAY! SO COOL!$"
# 335 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ChooseFromTable:
# 336 "data/maps/SitkaLab/scripts.pory"
	.string "Go ahead, choose a Pokémon from the\n"
# 337 "data/maps/SitkaLab/scripts.pory"
	.string "table.$"
# 338 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_PickAPokemonReminder:
# 339 "data/maps/SitkaLab/scripts.pory"
	.string "{PLAYER}! Aren’t you going to pick\n"
# 340 "data/maps/SitkaLab/scripts.pory"
	.string "a Pokémon?!$"
# 341 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ChooseSpheal:
# 342 "data/maps/SitkaLab/scripts.pory"
	.string "Spheal, the Clap Pokémon\n"
# 343 "data/maps/SitkaLab/scripts.pory"
	.string "Ice/Water\p"
# 344 "data/maps/SitkaLab/scripts.pory"
	.string "Would you like to choose this\n"
# 345 "data/maps/SitkaLab/scripts.pory"
	.string "Pokémon?$"
# 346 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ChooseSandile:
# 347 "data/maps/SitkaLab/scripts.pory"
	.string "Sandile, the Desert Croc Pokémon\n"
# 348 "data/maps/SitkaLab/scripts.pory"
	.string "Ground/Dark\p"
# 349 "data/maps/SitkaLab/scripts.pory"
	.string "Would you like to choose this\n"
# 350 "data/maps/SitkaLab/scripts.pory"
	.string "Pokémon?$"
# 351 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ChooseMareep:
# 352 "data/maps/SitkaLab/scripts.pory"
	.string "Mareep, the Wool Pokémon\n"
# 353 "data/maps/SitkaLab/scripts.pory"
	.string "Electric\p"
# 354 "data/maps/SitkaLab/scripts.pory"
	.string "Would you like to choose this\n"
# 355 "data/maps/SitkaLab/scripts.pory"
	.string "Pokémon?$"
# 356 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ReceivedSpheal:
# 357 "data/maps/SitkaLab/scripts.pory"
	.string "{PLAYER} received SPHEAL!$"
# 358 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ReceivedSandile:
# 359 "data/maps/SitkaLab/scripts.pory"
	.string "{PLAYER} received SANDILE!$"
# 360 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ReceivedMareep:
# 361 "data/maps/SitkaLab/scripts.pory"
	.string "{PLAYER} received MAREEP!$"
# 362 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_RemainingPokemon:
# 363 "data/maps/SitkaLab/scripts.pory"
	.string "This Pokémon belongs to Professor\n"
# 364 "data/maps/SitkaLab/scripts.pory"
	.string "Sitka.$"
# 365 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_AprilNotFair:
# 366 "data/maps/SitkaLab/scripts.pory"
	.string "Man, not fair! I want a Pokémon too.\n"
# 367 "data/maps/SitkaLab/scripts.pory"
	.string "Ugh, but my dad would never let me.$"
# 368 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ProfessorHmm:
# 369 "data/maps/SitkaLab/scripts.pory"
	.string "Hmm…$"
# 370 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ProfessorWhatTheHeck:
# 371 "data/maps/SitkaLab/scripts.pory"
	.string "Should I… Oh, what the heck…$"
# 372 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ProfessorOffersApril:
# 373 "data/maps/SitkaLab/scripts.pory"
	.string "{STR_VAR_1}, you can take a Pokémon\n"
# 374 "data/maps/SitkaLab/scripts.pory"
	.string "too. Tell your father to blame me.\l"
# 375 "data/maps/SitkaLab/scripts.pory"
	.string "I’ll handle him.$"
# 376 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_AprilSerious:
# 377 "data/maps/SitkaLab/scripts.pory"
	.string "W-what?! ARE YOU SERIOUS?!\n"
# 378 "data/maps/SitkaLab/scripts.pory"
	.string "THIS IS SO AWESOME!$"
# 379 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_AprilChooses:
# 380 "data/maps/SitkaLab/scripts.pory"
	.string "I choose…you!$"
# 381 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ProfessorTrouble:
# 382 "data/maps/SitkaLab/scripts.pory"
	.string "…I’m going to get in trouble for\n"
# 383 "data/maps/SitkaLab/scripts.pory"
	.string "this…$"
# 384 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ProfessorResponsibility:
# 385 "data/maps/SitkaLab/scripts.pory"
	.string "Listen, kids. Having Pokémon is a\n"
# 386 "data/maps/SitkaLab/scripts.pory"
	.string "lot of fun, but it’s a lot of\l"
# 387 "data/maps/SitkaLab/scripts.pory"
	.string "responsibility too.$"
# 388 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ProfessorTallGrass:
# 389 "data/maps/SitkaLab/scripts.pory"
	.string "These are yours to care for now.\n"
# 390 "data/maps/SitkaLab/scripts.pory"
	.string "With these partners by your side,\l"
# 391 "data/maps/SitkaLab/scripts.pory"
	.string "you’ll be able to enter tall grass\l"
# 392 "data/maps/SitkaLab/scripts.pory"
	.string "and face wild Pokémon.$"
# 393 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ProfessorBeCareful:
# 394 "data/maps/SitkaLab/scripts.pory"
	.string "Be careful…or I’ll never hear the\n"
# 395 "data/maps/SitkaLab/scripts.pory"
	.string "end of it from your parents.$"
# 396 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ProfessorGreatSummer:
# 397 "data/maps/SitkaLab/scripts.pory"
	.string "Now, go out there, have a great\n"
# 398 "data/maps/SitkaLab/scripts.pory"
	.string "summer, and prove that I made the\l"
# 399 "data/maps/SitkaLab/scripts.pory"
	.string "right decision by giving you these\l"
# 400 "data/maps/SitkaLab/scripts.pory"
	.string "Pokémon.$"
# 401 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_AprilWontLetDown:
# 402 "data/maps/SitkaLab/scripts.pory"
	.string "All right! We won’t let you down,\n"
# 403 "data/maps/SitkaLab/scripts.pory"
	.string "Professor.$"
# 404 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ProfessorAfterStarter:
# 405 "data/maps/SitkaLab/scripts.pory"
	.string "To be a young Trainer again…\p"
# 406 "data/maps/SitkaLab/scripts.pory"
	.string "Have fun on your Pokémon journey!$"
# 407 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ProfessorPartyHealthy:
# 408 "data/maps/SitkaLab/scripts.pory"
	.string "{PLAYER}, how is your Pokémon doing?\p"
# 409 "data/maps/SitkaLab/scripts.pory"
	.string "If they need to be healed, come see\n"
# 410 "data/maps/SitkaLab/scripts.pory"
	.string "me.$"
# 411 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_ProfessorPartyTired:
# 412 "data/maps/SitkaLab/scripts.pory"
	.string "{PLAYER}, your Pokémon look a bit\n"
# 413 "data/maps/SitkaLab/scripts.pory"
	.string "tired. Let me patch them up for you.$"
# 414 "data/maps/SitkaLab/scripts.pory"
SitkaLab_Text_AprilAfterStarter:
# 415 "data/maps/SitkaLab/scripts.pory"
	.string "This is so exciting! Your\n"
# 416 "data/maps/SitkaLab/scripts.pory"
	.string "{STR_VAR_2} is so cute!$"
