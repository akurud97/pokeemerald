# 1 "data/maps/InquillCenter/scripts.pory"

# 2 "data/maps/InquillCenter/scripts.pory"
.set LOCALID_NURSE, LOCALID_INQUILL_CENTER_NURSE
# 3 "data/maps/InquillCenter/scripts.pory"

# 4 "data/maps/InquillCenter/scripts.pory"
InquillCenter_MapScripts::
# 5 "data/maps/InquillCenter/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, InquillCenter_OnTransition
# 6 "data/maps/InquillCenter/scripts.pory"
	.byte 0
# 7 "data/maps/InquillCenter/scripts.pory"

# 8 "data/maps/InquillCenter/scripts.pory"
InquillCenter_OnTransition:
# 9 "data/maps/InquillCenter/scripts.pory"
	setrespawn HEAL_LOCATION_INQUILL_TOWN
# 10 "data/maps/InquillCenter/scripts.pory"
	end
# 11 "data/maps/InquillCenter/scripts.pory"

# 12 "data/maps/InquillCenter/scripts.pory"
InquillCenter_EventScript_Nurse::
# 13 "data/maps/InquillCenter/scripts.pory"
	setvar VAR_0x800B, LOCALID_NURSE
# 14 "data/maps/InquillCenter/scripts.pory"
	goto Common_EventScript_CustomPkmnCenterNurse

InquillCenter_EventScript_Object2::
# 18 "data/maps/InquillCenter/scripts.pory"
	msgbox InquillCenter_Text_Object2, MSGBOX_NPC
	end


InquillCenter_Text_Object2::
# 22 "data/maps/InquillCenter/scripts.pory"
	.string "The gym here seemed kind of girly,\n"
	.string "but I got my butt whooped.$"
