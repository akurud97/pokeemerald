# 1 "data/maps/InquillTunnelF2/scripts.pory"

# 2 "data/maps/InquillTunnelF2/scripts.pory"
InquillTunnelF2_MapScripts::
# 3 "data/maps/InquillTunnelF2/scripts.pory"
	.byte 0
# 4 "data/maps/InquillTunnelF2/scripts.pory"

# 5 "data/maps/InquillTunnelF2/scripts.pory"
InquillTunnelF2_EventScript_Julian::
# 6 "data/maps/InquillTunnelF2/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_INQUILL_TUNNEL_JULIAN, InquillTunnelF2_Text_JulianIntro, InquillTunnelF2_Text_JulianDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, InquillTunnelF2_Text_JulianVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 7 "data/maps/InquillTunnelF2/scripts.pory"
	msgbox InquillTunnelF2_Text_JulianPostBattle, MSGBOX_AUTOCLOSE
# 8 "data/maps/InquillTunnelF2/scripts.pory"
	end
# 9 "data/maps/InquillTunnelF2/scripts.pory"

# 10 "data/maps/InquillTunnelF2/scripts.pory"
InquillTunnelF2_EventScript_Charles::
# 11 "data/maps/InquillTunnelF2/scripts.pory"
	trainerbattle TRAINER_BATTLE_EARLY_RIVAL, LOCALID_NONE, TRAINER_INQUILL_TUNNEL_CHARLES, InquillTunnelF2_Text_CharlesIntro, InquillTunnelF2_Text_CharlesDefeat, NULL, LOCALID_NONE, TRAINER_NONE, NULL, NULL, NULL, InquillTunnelF2_Text_CharlesVictory, NULL, FALSE, TRUE, FALSE, FALSE
# 12 "data/maps/InquillTunnelF2/scripts.pory"
	msgbox InquillTunnelF2_Text_CharlesPostBattle, MSGBOX_AUTOCLOSE
# 13 "data/maps/InquillTunnelF2/scripts.pory"
	end

InquillTunnelF2_Text_JulianIntro::
# 16 "data/maps/InquillTunnelF2/scripts.pory"
	.string "I came here to catch my favourite\n"
	.string "Pokémon! Want to see?$"

InquillTunnelF2_Text_JulianDefeat::
# 21 "data/maps/InquillTunnelF2/scripts.pory"
	.string "Ah! My Abra!$"

InquillTunnelF2_Text_JulianVictory::
# 25 "data/maps/InquillTunnelF2/scripts.pory"
	.string "That’s why I love Abra!$"

InquillTunnelF2_Text_JulianPostBattle::
# 29 "data/maps/InquillTunnelF2/scripts.pory"
	.string "I’m going to catch lots of Abra!$"

InquillTunnelF2_Text_CharlesIntro::
# 33 "data/maps/InquillTunnelF2/scripts.pory"
	.string "Do you know the secret pathways?\n"
	.string "Tell me!$"

InquillTunnelF2_Text_CharlesDefeat::
# 38 "data/maps/InquillTunnelF2/scripts.pory"
	.string "I’ll never find the way…$"

InquillTunnelF2_Text_CharlesVictory::
# 42 "data/maps/InquillTunnelF2/scripts.pory"
	.string "You’ve shown me the way!$"

InquillTunnelF2_Text_CharlesPostBattle::
# 46 "data/maps/InquillTunnelF2/scripts.pory"
	.string "There are rumours that these tunnels\n"
	.string "stretch far up into the hills, and\l"
	.string "there may be rare Pokémon deeper\l"
	.string "within. I’m here to find them.$"
