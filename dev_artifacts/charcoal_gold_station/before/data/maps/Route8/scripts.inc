# 1 "data/maps/Route8/scripts.pory"

# 2 "data/maps/Route8/scripts.pory"
Route8_MapScripts::
# 3 "data/maps/Route8/scripts.pory"
	.byte 0

Route8_EventScript_BridgeWarning::
# 7 "data/maps/Route8/scripts.pory"
	msgbox Route8_Text_BridgeWarning, MSGBOX_NPC
	end


Route8_EventScript_PokemonBarrier::
# 12 "data/maps/Route8/scripts.pory"
	msgbox Route8_Text_PokemonBarrier, MSGBOX_SIGN
	end


Route8_Text_BridgeWarning::
# 16 "data/maps/Route8/scripts.pory"
	.string "There's a Pokémon blocking the bridge.\p"
	.string "If you need to get to Castula City,\n"
	.string "you'll have to go through\l"
	.string "Dreamcatcher Woods.$"

Route8_Text_PokemonBarrier::
# 23 "data/maps/Route8/scripts.pory"
	.string "The Pokémon is projecting some kind\n"
	.string "of barrier.$"
