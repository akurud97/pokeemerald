# 1 "data/maps/AprilHouse1F/scripts.pory"

# 2 "data/maps/AprilHouse1F/scripts.pory"
.set LOCALID_DAD, LOCALID_APRIL_HOUSE1F_DAD
# 3 "data/maps/AprilHouse1F/scripts.pory"

# 4 "data/maps/AprilHouse1F/scripts.pory"
AprilHouse1F_MapScripts::
# 5 "data/maps/AprilHouse1F/scripts.pory"
	.byte 0
# 6 "data/maps/AprilHouse1F/scripts.pory"

# 7 "data/maps/AprilHouse1F/scripts.pory"
AprilHouse1F_EventScript_Dad::
# 8 "data/maps/AprilHouse1F/scripts.pory"
	lock
# 9 "data/maps/AprilHouse1F/scripts.pory"
	faceplayer
# 10 "data/maps/AprilHouse1F/scripts.pory"
	goto_if_ge VAR_ALASIA_INTRO_STATE, 10, AprilHouse1F_EventScript_AfterChapterOne
# 11 "data/maps/AprilHouse1F/scripts.pory"
	goto_if_ge VAR_ALASIA_INTRO_STATE, 6, AprilHouse1F_EventScript_AfterStarters
# 12 "data/maps/AprilHouse1F/scripts.pory"
	setspeaker SP_NAME_NONE
# 13 "data/maps/AprilHouse1F/scripts.pory"
	msgbox AprilHouse1F_Text_DadBeforeStarters, MSGBOX_DEFAULT
# 14 "data/maps/AprilHouse1F/scripts.pory"
	release
# 15 "data/maps/AprilHouse1F/scripts.pory"
	end
# 16 "data/maps/AprilHouse1F/scripts.pory"

# 17 "data/maps/AprilHouse1F/scripts.pory"
AprilHouse1F_EventScript_AfterChapterOne::
# 18 "data/maps/AprilHouse1F/scripts.pory"
	special BufferAprilName
# 19 "data/maps/AprilHouse1F/scripts.pory"
	setspeaker AprilHouse1F_Text_DadSpeakerName
# 20 "data/maps/AprilHouse1F/scripts.pory"
	msgbox AprilHouse1F_Text_DadAfterChapterOne, MSGBOX_DEFAULT
# 21 "data/maps/AprilHouse1F/scripts.pory"
	setspeaker SP_NAME_NONE
# 22 "data/maps/AprilHouse1F/scripts.pory"
	release
# 23 "data/maps/AprilHouse1F/scripts.pory"
	end
# 24 "data/maps/AprilHouse1F/scripts.pory"

# 25 "data/maps/AprilHouse1F/scripts.pory"
AprilHouse1F_EventScript_AfterStarters::
# 26 "data/maps/AprilHouse1F/scripts.pory"
	special BufferAprilName
# 27 "data/maps/AprilHouse1F/scripts.pory"
	setspeaker AprilHouse1F_Text_DadSpeakerName
# 28 "data/maps/AprilHouse1F/scripts.pory"
	msgbox AprilHouse1F_Text_Dad, MSGBOX_DEFAULT
# 29 "data/maps/AprilHouse1F/scripts.pory"
	setspeaker SP_NAME_NONE
# 30 "data/maps/AprilHouse1F/scripts.pory"
	release
# 31 "data/maps/AprilHouse1F/scripts.pory"
	end
# 32 "data/maps/AprilHouse1F/scripts.pory"

# 33 "data/maps/AprilHouse1F/scripts.pory"
AprilHouse1F_Text_DadSpeakerName:
# 34 "data/maps/AprilHouse1F/scripts.pory"
	.string "{STR_VAR_1}'s Dad$"
# 35 "data/maps/AprilHouse1F/scripts.pory"

# 36 "data/maps/AprilHouse1F/scripts.pory"
AprilHouse1F_Text_DadBeforeStarters:
# 37 "data/maps/AprilHouse1F/scripts.pory"
	.string "You guys are off school already?\n"
# 38 "data/maps/AprilHouse1F/scripts.pory"
	.string "Time flies.\p"
# 39 "data/maps/AprilHouse1F/scripts.pory"
	.string "My daughter went downstairs to her\n"
# 40 "data/maps/AprilHouse1F/scripts.pory"
	.string "room if you're looking for her.$"
# 41 "data/maps/AprilHouse1F/scripts.pory"

# 42 "data/maps/AprilHouse1F/scripts.pory"
AprilHouse1F_Text_Dad:
# 43 "data/maps/AprilHouse1F/scripts.pory"
	.string "Have you seen {STR_VAR_1}? She said\n"
# 44 "data/maps/AprilHouse1F/scripts.pory"
	.string "she was going by your house.$"
# 45 "data/maps/AprilHouse1F/scripts.pory"

# 46 "data/maps/AprilHouse1F/scripts.pory"
AprilHouse1F_Text_DadAfterChapterOne:
# 47 "data/maps/AprilHouse1F/scripts.pory"
	.string "So, Professor Sitka gave you two\n"
# 48 "data/maps/AprilHouse1F/scripts.pory"
	.string "Pokémon, huh?\p"
# 49 "data/maps/AprilHouse1F/scripts.pory"
	.string "I chewed her out, but really, I’m\n"
# 50 "data/maps/AprilHouse1F/scripts.pory"
	.string "happy for you.\p"
# 51 "data/maps/AprilHouse1F/scripts.pory"
	.string "That professor needs to learn some\n"
# 52 "data/maps/AprilHouse1F/scripts.pory"
	.string "responsibility though…\p"
# 53 "data/maps/AprilHouse1F/scripts.pory"
	.string "Anyway, if you see {STR_VAR_1}, tell\n"
# 54 "data/maps/AprilHouse1F/scripts.pory"
	.string "her to stop by sometimes. She rushed\l"
# 55 "data/maps/AprilHouse1F/scripts.pory"
	.string "off. You know how she is.$"
