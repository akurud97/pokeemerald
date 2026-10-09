# 1 "data/maps/AprilHouse2F/scripts.pory"

# 2 "data/maps/AprilHouse2F/scripts.pory"
.set LOCALID_APRIL, LOCALID_APRIL_HOUSE2F_APRIL
# 3 "data/maps/AprilHouse2F/scripts.pory"

# 4 "data/maps/AprilHouse2F/scripts.pory"
AprilHouse2F_MapScripts::
# 5 "data/maps/AprilHouse2F/scripts.pory"
	map_script MAP_SCRIPT_ON_TRANSITION, AprilHouse2F_OnTransition
# 6 "data/maps/AprilHouse2F/scripts.pory"
	.byte 0
# 7 "data/maps/AprilHouse2F/scripts.pory"

# 8 "data/maps/AprilHouse2F/scripts.pory"
AprilHouse2F_OnTransition:
# 9 "data/maps/AprilHouse2F/scripts.pory"
	call_if_ge VAR_ALASIA_INTRO_STATE, 6, AprilHouse2F_EventScript_HideApril
# 10 "data/maps/AprilHouse2F/scripts.pory"
	end
# 11 "data/maps/AprilHouse2F/scripts.pory"

# 12 "data/maps/AprilHouse2F/scripts.pory"
AprilHouse2F_EventScript_HideApril:
# 13 "data/maps/AprilHouse2F/scripts.pory"
	setflag FLAG_HIDE_APRIL_HOUSE2F_APRIL
# 14 "data/maps/AprilHouse2F/scripts.pory"
	return
# 15 "data/maps/AprilHouse2F/scripts.pory"

# 16 "data/maps/AprilHouse2F/scripts.pory"
AprilHouse2F_EventScript_April::
# 17 "data/maps/AprilHouse2F/scripts.pory"
	lock
# 18 "data/maps/AprilHouse2F/scripts.pory"
	faceplayer
# 19 "data/maps/AprilHouse2F/scripts.pory"
	special BufferAprilName
# 20 "data/maps/AprilHouse2F/scripts.pory"
	goto_if_set FLAG_APRIL_NAMED, AprilHouse2F_EventScript_NamedApril
# 21 "data/maps/AprilHouse2F/scripts.pory"
	setspeaker SP_NAME_NONE
# 22 "data/maps/AprilHouse2F/scripts.pory"
	goto AprilHouse2F_EventScript_AprilDialogue
# 23 "data/maps/AprilHouse2F/scripts.pory"

# 24 "data/maps/AprilHouse2F/scripts.pory"
AprilHouse2F_EventScript_NamedApril:
# 25 "data/maps/AprilHouse2F/scripts.pory"
	setspeaker AprilHouse2F_Text_AprilSpeakerName
# 26 "data/maps/AprilHouse2F/scripts.pory"

# 27 "data/maps/AprilHouse2F/scripts.pory"
AprilHouse2F_EventScript_AprilDialogue:
# 28 "data/maps/AprilHouse2F/scripts.pory"
	msgbox AprilHouse2F_Text_April, MSGBOX_DEFAULT
# 29 "data/maps/AprilHouse2F/scripts.pory"
	setspeaker SP_NAME_NONE
# 30 "data/maps/AprilHouse2F/scripts.pory"
	release
# 31 "data/maps/AprilHouse2F/scripts.pory"
	end
# 32 "data/maps/AprilHouse2F/scripts.pory"

# 33 "data/maps/AprilHouse2F/scripts.pory"
AprilHouse2F_Text_AprilSpeakerName:
# 34 "data/maps/AprilHouse2F/scripts.pory"
	.string "{STR_VAR_1}$"
# 35 "data/maps/AprilHouse2F/scripts.pory"

# 36 "data/maps/AprilHouse2F/scripts.pory"
AprilHouse2F_Text_April:
# 37 "data/maps/AprilHouse2F/scripts.pory"
	.string "Hey, {PLAYER}! We're going to have\n"
# 38 "data/maps/AprilHouse2F/scripts.pory"
	.string "so much fun this summer, I can feel\l"
# 39 "data/maps/AprilHouse2F/scripts.pory"
	.string "it.$"
