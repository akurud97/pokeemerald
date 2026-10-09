# 1 "data/maps/MintakaCenter/scripts.pory"

# 2 "data/maps/MintakaCenter/scripts.pory"
.set LOCALID_NURSE, LOCALID_MINTAKA_CENTER_NURSE
# 3 "data/maps/MintakaCenter/scripts.pory"

# 4 "data/maps/MintakaCenter/scripts.pory"
MintakaCenter_MapScripts::
# 5 "data/maps/MintakaCenter/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, MintakaCenter_OnTransition
# 6 "data/maps/MintakaCenter/scripts.pory"
	.byte 0
# 7 "data/maps/MintakaCenter/scripts.pory"

# 8 "data/maps/MintakaCenter/scripts.pory"
MintakaCenter_OnTransition:
# 9 "data/maps/MintakaCenter/scripts.pory"
	setrespawn HEAL_LOCATION_MINTAKA_CITY
# 10 "data/maps/MintakaCenter/scripts.pory"
	end
# 11 "data/maps/MintakaCenter/scripts.pory"

# 12 "data/maps/MintakaCenter/scripts.pory"
MintakaCenter_EventScript_Nurse::
# 13 "data/maps/MintakaCenter/scripts.pory"
	setvar VAR_0x800B, LOCALID_NURSE
# 14 "data/maps/MintakaCenter/scripts.pory"
	goto Common_EventScript_CustomPkmnCenterNurse

MintakaCenter_EventScript_Object2::
# 18 "data/maps/MintakaCenter/scripts.pory"
	lock
# 19 "data/maps/MintakaCenter/scripts.pory"
	msgbox MintakaCenter_Text_Object2, MSGBOX_DEFAULT
# 20 "data/maps/MintakaCenter/scripts.pory"
	release
	end


MintakaCenter_EventScript_Object3::
# 25 "data/maps/MintakaCenter/scripts.pory"
	lock
# 26 "data/maps/MintakaCenter/scripts.pory"
	msgbox MintakaCenter_Text_Object3, MSGBOX_DEFAULT
# 27 "data/maps/MintakaCenter/scripts.pory"
	release
	end


MintakaCenter_Text_Object2::
# 31 "data/maps/MintakaCenter/scripts.pory"
	.string "…and look at the picture of this\n"
	.string "Barboach I pulled up! It was huge!$"

MintakaCenter_Text_Object3::
# 36 "data/maps/MintakaCenter/scripts.pory"
	.string "…Hm? Oh… wow, yeah…$"
