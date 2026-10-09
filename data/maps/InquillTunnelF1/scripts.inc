# 1 "data/maps/InquillTunnelF1/scripts.pory"

# 2 "data/maps/InquillTunnelF1/scripts.pory"
InquillTunnelF1_MapScripts::
# 3 "data/maps/InquillTunnelF1/scripts.pory"
	.byte 0
# 4 "data/maps/InquillTunnelF1/scripts.pory"

# 5 "data/maps/InquillTunnelF1/scripts.pory"
InquillTunnelF1_EventScript_Aiden::
# 6 "data/maps/InquillTunnelF1/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_INQUILL_TUNNEL_AIDEN, InquillTunnelF1_Text_AidenIntro, InquillTunnelF1_Text_AidenDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, InquillTunnelF1_Text_AidenVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 7 "data/maps/InquillTunnelF1/scripts.pory"
	msgbox InquillTunnelF1_Text_AidenPostBattle, MSGBOX_AUTOCLOSE
# 8 "data/maps/InquillTunnelF1/scripts.pory"
	end
# 9 "data/maps/InquillTunnelF1/scripts.pory"

# 10 "data/maps/InquillTunnelF1/scripts.pory"
InquillTunnelF1_EventScript_Mason::
# 11 "data/maps/InquillTunnelF1/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_INQUILL_TUNNEL_MASON, InquillTunnelF1_Text_MasonIntro, InquillTunnelF1_Text_MasonDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, InquillTunnelF1_Text_MasonVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 12 "data/maps/InquillTunnelF1/scripts.pory"
	msgbox InquillTunnelF1_Text_MasonPostBattle, MSGBOX_AUTOCLOSE
# 13 "data/maps/InquillTunnelF1/scripts.pory"
	end

InquillTunnelF1_Text_AidenIntro::
# 16 "data/maps/InquillTunnelF1/scripts.pory"
	.string "Is that a bug? Oh no, it’s just a\n"
	.string "trainer.$"

InquillTunnelF1_Text_AidenDefeat::
# 21 "data/maps/InquillTunnelF1/scripts.pory"
	.string "I need to get my eyesight checked…$"

InquillTunnelF1_Text_AidenVictory::
# 25 "data/maps/InquillTunnelF1/scripts.pory"
	.string "Squashed like a bug.$"

InquillTunnelF1_Text_AidenPostBattle::
# 29 "data/maps/InquillTunnelF1/scripts.pory"
	.string "There are lots of crawlies in these\n"
	.string "caves…but they’re hard to spot in the\l"
	.string "dark.$"

InquillTunnelF1_Text_MasonIntro::
# 35 "data/maps/InquillTunnelF1/scripts.pory"
	.string "Hey kid! Are you gonna snitch on me?$"

InquillTunnelF1_Text_MasonDefeat::
# 39 "data/maps/InquillTunnelF1/scripts.pory"
	.string "I knew I should have found a better\n"
	.string "hiding spot.$"

InquillTunnelF1_Text_MasonVictory::
# 44 "data/maps/InquillTunnelF1/scripts.pory"
	.string "That’ll teach you to be a snitch!$"

InquillTunnelF1_Text_MasonPostBattle::
# 48 "data/maps/InquillTunnelF1/scripts.pory"
	.string "Listen kid, I’m hiding out in here\n"
	.string "for…reasons. Don’t tell no one, okay?$"
