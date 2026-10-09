# 1 "data/maps/InquillHouse5/scripts.pory"

# 2 "data/maps/InquillHouse5/scripts.pory"
InquillHouse5_MapScripts::
# 3 "data/maps/InquillHouse5/scripts.pory"
	.byte 0
# 4 "data/maps/InquillHouse5/scripts.pory"

# 5 "data/maps/InquillHouse5/scripts.pory"
InquillHouse5_EventScript_TradeBuneary::
# 6 "data/maps/InquillHouse5/scripts.pory"
	lock
# 7 "data/maps/InquillHouse5/scripts.pory"
	faceplayer
# 8 "data/maps/InquillHouse5/scripts.pory"
	goto_if_set FLAG_INQUILL_HOUSE5_TRADE_COMPLETED, InquillHouse5_EventScript_TradeCompleted
# 9 "data/maps/InquillHouse5/scripts.pory"
	setvar VAR_0x8008, INGAME_TRADE_BUNEARY
# 10 "data/maps/InquillHouse5/scripts.pory"
	call EventScript_GetInGameTradeSpeciesInfo
# 11 "data/maps/InquillHouse5/scripts.pory"
	msgbox InquillHouse5_Text_TradeOffer, MSGBOX_YESNO
# 12 "data/maps/InquillHouse5/scripts.pory"
	goto_if_eq VAR_RESULT, NO, InquillHouse5_EventScript_TradeDeclined
# 13 "data/maps/InquillHouse5/scripts.pory"
	checkspecies SPECIES_PHANPY
# 14 "data/maps/InquillHouse5/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, InquillHouse5_EventScript_NoPhanpy
# 15 "data/maps/InquillHouse5/scripts.pory"
	call EventScript_ChooseMonForInGameTrade
# 16 "data/maps/InquillHouse5/scripts.pory"
	goto_if_ge VAR_0x8004, PARTY_SIZE, InquillHouse5_EventScript_TradeDeclined
# 17 "data/maps/InquillHouse5/scripts.pory"
	call EventScript_GetInGameTradeSpecies
# 18 "data/maps/InquillHouse5/scripts.pory"
	goto_if_ne VAR_RESULT, VAR_0x8009, InquillHouse5_EventScript_NotPhanpy
# 19 "data/maps/InquillHouse5/scripts.pory"
	call EventScript_DoInGameTrade
# 20 "data/maps/InquillHouse5/scripts.pory"
	msgbox InquillHouse5_Text_TradeCompleted, MSGBOX_DEFAULT
# 21 "data/maps/InquillHouse5/scripts.pory"
	setflag FLAG_INQUILL_HOUSE5_TRADE_COMPLETED
# 22 "data/maps/InquillHouse5/scripts.pory"
	release
# 23 "data/maps/InquillHouse5/scripts.pory"
	end
# 24 "data/maps/InquillHouse5/scripts.pory"

# 25 "data/maps/InquillHouse5/scripts.pory"
InquillHouse5_EventScript_NoPhanpy::
# 26 "data/maps/InquillHouse5/scripts.pory"
	msgbox InquillHouse5_Text_NoPhanpy, MSGBOX_DEFAULT
# 27 "data/maps/InquillHouse5/scripts.pory"
	release
# 28 "data/maps/InquillHouse5/scripts.pory"
	end
# 29 "data/maps/InquillHouse5/scripts.pory"

# 30 "data/maps/InquillHouse5/scripts.pory"
InquillHouse5_EventScript_NotPhanpy::
# 31 "data/maps/InquillHouse5/scripts.pory"
	msgbox InquillHouse5_Text_NotPhanpy, MSGBOX_DEFAULT
# 32 "data/maps/InquillHouse5/scripts.pory"
	release
# 33 "data/maps/InquillHouse5/scripts.pory"
	end
# 34 "data/maps/InquillHouse5/scripts.pory"

# 35 "data/maps/InquillHouse5/scripts.pory"
InquillHouse5_EventScript_TradeDeclined::
# 36 "data/maps/InquillHouse5/scripts.pory"
	release
# 37 "data/maps/InquillHouse5/scripts.pory"
	end
# 38 "data/maps/InquillHouse5/scripts.pory"

# 39 "data/maps/InquillHouse5/scripts.pory"
InquillHouse5_EventScript_TradeCompleted::
# 40 "data/maps/InquillHouse5/scripts.pory"
	msgbox InquillHouse5_Text_TradeCompleted, MSGBOX_DEFAULT
# 41 "data/maps/InquillHouse5/scripts.pory"
	release
# 42 "data/maps/InquillHouse5/scripts.pory"
	end

InquillHouse5_EventScript_Object1::
# 46 "data/maps/InquillHouse5/scripts.pory"
	msgbox InquillHouse5_Text_Object1, MSGBOX_NPC
	end


InquillHouse5_Text_Object1::
# 50 "data/maps/InquillHouse5/scripts.pory"
	.string "I moved into town to work at the new\n"
	.string "lab, but some shady characters took\l"
	.string "over operations.\p"
	.string "They wouldn’t tell us what we were\n"
	.string "working on.$"

InquillHouse5_Text_TradeOffer::
# 58 "data/maps/InquillHouse5/scripts.pory"
	.string "Have you seen Phanpy? They're so cute!\n"
	.string "I'll trade you my Buneary for one.$"

InquillHouse5_Text_NoPhanpy::
# 63 "data/maps/InquillHouse5/scripts.pory"
	.string "You don't have a Phanpy? Too bad...$"

InquillHouse5_Text_NotPhanpy::
# 67 "data/maps/InquillHouse5/scripts.pory"
	.string "That isn't a Phanpy. Too bad...$"

InquillHouse5_Text_TradeCompleted::
# 71 "data/maps/InquillHouse5/scripts.pory"
	.string "Phanpy's trunk is so adorable! Thank\n"
	.string "you!$"
