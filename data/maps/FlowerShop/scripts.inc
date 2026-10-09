# 1 "data/maps/FlowerShop/scripts.pory"

# 2 "data/maps/FlowerShop/scripts.pory"
FlowerShop_MapScripts::
# 3 "data/maps/FlowerShop/scripts.pory"
	.byte 0
# 4 "data/maps/FlowerShop/scripts.pory"

# 5 "data/maps/FlowerShop/scripts.pory"
FlowerShop_EventScript_Shopkeeper::
# 6 "data/maps/FlowerShop/scripts.pory"
	lock
# 7 "data/maps/FlowerShop/scripts.pory"
	faceplayer
# 8 "data/maps/FlowerShop/scripts.pory"
	msgbox FlowerShop_Text_ShopWelcome, MSGBOX_DEFAULT
# 9 "data/maps/FlowerShop/scripts.pory"
	pokemart FlowerShop_Pokemart_Mulch
# 10 "data/maps/FlowerShop/scripts.pory"
	msgbox FlowerShop_Text_ShopThanks, MSGBOX_DEFAULT
# 11 "data/maps/FlowerShop/scripts.pory"
	release
# 12 "data/maps/FlowerShop/scripts.pory"
	end
# 13 "data/maps/FlowerShop/scripts.pory"

# 14 "data/maps/FlowerShop/scripts.pory"
	.align 2
# 15 "data/maps/FlowerShop/scripts.pory"
FlowerShop_Pokemart_Mulch:
# 16 "data/maps/FlowerShop/scripts.pory"
	.2byte ITEM_GROWTH_MULCH
# 17 "data/maps/FlowerShop/scripts.pory"
	.2byte ITEM_STABLE_MULCH
# 18 "data/maps/FlowerShop/scripts.pory"
	.2byte ITEM_GOOEY_MULCH
# 19 "data/maps/FlowerShop/scripts.pory"
	.2byte ITEM_RICH_MULCH
# 20 "data/maps/FlowerShop/scripts.pory"
	.2byte ITEM_NONE
# 21 "data/maps/FlowerShop/scripts.pory"
	release
# 22 "data/maps/FlowerShop/scripts.pory"
	end
# 23 "data/maps/FlowerShop/scripts.pory"

# 24 "data/maps/FlowerShop/scripts.pory"
FlowerShop_EventScript_WailmerPailGift::
# 25 "data/maps/FlowerShop/scripts.pory"
	lock
# 26 "data/maps/FlowerShop/scripts.pory"
	faceplayer
# 27 "data/maps/FlowerShop/scripts.pory"
	goto_if_set FLAG_RECEIVED_WAILMER_PAIL, FlowerShop_EventScript_WailmerPailRepeat
# 28 "data/maps/FlowerShop/scripts.pory"
	msgbox FlowerShop_Text_WailmerPailGift, MSGBOX_DEFAULT
# 29 "data/maps/FlowerShop/scripts.pory"
	giveitem ITEM_WAILMER_PAIL
# 30 "data/maps/FlowerShop/scripts.pory"
	goto_if_eq VAR_RESULT, FALSE, Common_EventScript_ShowBagIsFull
# 31 "data/maps/FlowerShop/scripts.pory"
	setflag FLAG_RECEIVED_WAILMER_PAIL
# 32 "data/maps/FlowerShop/scripts.pory"
	release
# 33 "data/maps/FlowerShop/scripts.pory"
	end
# 34 "data/maps/FlowerShop/scripts.pory"

# 35 "data/maps/FlowerShop/scripts.pory"
FlowerShop_EventScript_WailmerPailRepeat::
# 36 "data/maps/FlowerShop/scripts.pory"
	msgbox FlowerShop_Text_WailmerPailRepeat, MSGBOX_DEFAULT
# 37 "data/maps/FlowerShop/scripts.pory"
	release
# 38 "data/maps/FlowerShop/scripts.pory"
	end

FlowerShop_EventScript_Object3::
# 42 "data/maps/FlowerShop/scripts.pory"
	msgbox FlowerShop_Text_Object3, MSGBOX_NPC
	end


FlowerShop_EventScript_Object4::
# 47 "data/maps/FlowerShop/scripts.pory"
	msgbox FlowerShop_Text_Object4, MSGBOX_NPC
	end


FlowerShop_Text_ShopWelcome::
# 51 "data/maps/FlowerShop/scripts.pory"
	.string "Welcome! Are you here to buy mulch?$"

FlowerShop_Text_ShopThanks::
# 55 "data/maps/FlowerShop/scripts.pory"
	.string "Thank you! Enjoy growing berries.$"

FlowerShop_Text_WailmerPailGift::
# 59 "data/maps/FlowerShop/scripts.pory"
	.string "Hello, young boy. Are you interested\n"
	.string "in growing berries for your Pokémon?\p"
	.string "You can have this watering can on us -\n"
	.string "just promise to buy some mulch from\l"
	.string "the counter!$"

FlowerShop_Text_WailmerPailRepeat::
# 67 "data/maps/FlowerShop/scripts.pory"
	.string "Have you been growing lots of berries?$"

FlowerShop_Text_Object3::
# 71 "data/maps/FlowerShop/scripts.pory"
	.string "This shop smells so good!$"

FlowerShop_Text_Object4::
# 75 "data/maps/FlowerShop/scripts.pory"
	.string "I wonder what kind of flowers my wife\n"
	.string "would like…$"
