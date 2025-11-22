#pragma once
#include "Inscryption.hpp"

InscryptionGame::InscryptionGame()
{
	Window_Name = "Inscryption Forbiden Version v_02 alpha";

	WIDTH = 1280;
	HEIGHT = 720;

	window = std::make_shared<sf::RenderWindow>
	(
	sf::VideoMode(WIDTH,HEIGHT),
	Window_Name,
	sf::Style::Titlebar | sf::Style::Close
	);

	Create_Window();

	RARITY = COMMON;
	SIGIL_1 = None;
	SIGIL_2 = None;
	SCALE_INCLINATION_CONST = 1.5;
	BUTTON_STATE = BUTTON_IDLE;
	BELL_STATE = BELL_UNLIT;
	TURN_OWNER = EVENT_TURN;
	CURSOR_STATE = NORMAL;
	PLAYER_INPUT = IDDLE;
	CARD_NUMBER = Squirrel;
	PLAYER_PLACEMENT = -1;
	XANDY_MULTIPLIER = 3;
	CARD_OPACITY = 254;
	CARD_SELECTED = -1;
	CARDS_ON_BOARD = 0;
	BATTERY_CHARGE = 0;
	DIALOGUE_STEP = 0;
	COLOR_OPACITY = 0;
	BONE_COUNTER = 100; //changed
	SCALE_POINTS = 5;
	SCALE_DAMAGE = 5;
	LESHY_SCALE_POINTS = 0;
	PLAYER_SCALE_POINTS = 0;
	TURN_NUMBER = 1;
	VELOCITY = 0;
	DELTA_TIME = 0.83;
	TEXT_TIME = 75;
	DECK_SIZE = 15;
	SACRIFICES = 0;
	BLOOD_COST = 0;
	CARD_STEP = 0;
	BONE_COST = 0;
	CHAR_VAR = 37;
	C_WORD = 0;
	ATTK = 0;
	HP = 1;

	continue_move = 0;
	positionating = 0;
	sacrificing = 0;
	sacrificed = 0;
	fullscreen = 0;
	leshy_mad = 0;//also mod
	on_board = 0;
	smashing = 0;
	ocupied = 0;
	menu = 1; //modified

	DarkGray.r = 10;
	DarkGray.g = 10;
	DarkGray.b = 10;
	DarkGray.a = 220;

	DarkRed.r = 220;
	DarkRed.g = 0;
	DarkRed.b = 0;
	DarkRed.a = 255;

	Object_Moving_Coords.x = 0;
	Object_Moving_Coords.y = 0;
	Object_Coords.x = 0;
	Object_Coords.y = 0;

	music1.openFromFile("assets\\gbc_battle_leshy.flac");
	music1.setLoop(true);
	music1.setVolume(70);
	music2.openFromFile("assets\\gbc_battle_basic.flac");
	music2.setLoop(true);
	music2.setVolume(200);
	music2.play();

	blip_buffer1.loadFromFile("assets\\chipBlip2.wav");
	blip1.setBuffer(blip_buffer1);
	blip_buffer2.loadFromFile("assets\\chipBlip4.wav");
	blip2.setBuffer(blip_buffer2);
	blip_buffer3.loadFromFile("assets\\chipBlip3.wav");
	blip3.setBuffer(blip_buffer3);
	continue_fits_buffer.loadFromFile("assets\\crunch_short2.wav");
	continue_fits_sound.setBuffer(continue_fits_buffer);
	exit_dialog_buffer.loadFromFile("assets\\chipDelay_2.wav");
	exit_dialogue_sound.setBuffer(exit_dialog_buffer);

	card_attack1_buffer.loadFromFile("assets\\pixel_card_attack_nature.wav");
	card_attack1_sound.setBuffer(card_attack1_buffer);

	t_cursors_map.loadFromFile("assets\\cursor_icons.png");
	s_cursor.setTexture(t_cursors_map);
	s_cursor.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);
	mouse.setPosition(sf::Vector2i(window->getPosition().x + WIDTH / 2, window->getPosition().y + HEIGHT / 2));

	t_menu_background.loadFromFile("assets\\startscreen_background_PART1.png");
	s_menu_background.setTexture(t_menu_background);
	s_menu_background.setScale(3.2,3.2);

	Layer_Effect.setSize(sf::Vector2f(WIDTH, HEIGHT));
	Layer_Effect.setFillColor(sf::Color(0,0,0,COLOR_OPACITY));

	t_icon_plate_dark.loadFromFile("assets\\startscreen_slot_PART1.png");
	t_icon_plate_midlight.loadFromFile("assets\\startscreen_slot_mediumlighted_PART1.png");
	t_icon_plate_light.loadFromFile("assets\\startscreen_slot_highlighted_PART1.png");
	s_icon_plate_attach.setTexture(t_icon_plate_light);
	s_icon_plate_attach.setPosition(sf::Vector2f(568,215));
	s_icon_plate_attach.setScale(XANDY_MULTIPLIER,XANDY_MULTIPLIER);

	t_icon_continue.loadFromFile("assets\\menucard_continue.png");
	s_icon_continue.setTexture(t_icon_continue);
	s_icon_continue.setScale(XANDY_MULTIPLIER,XANDY_MULTIPLIER);
	s_icon_continue.setPosition(sf::Vector2f(WIDTH, 520));

	t_text_box.loadFromFile("assets\\text_box_nature.png");
	s_text_box.setTexture(t_text_box);
	s_text_box.setScale(2.5,2.5);
	s_text_box.setPosition(sf::Vector2f(280,540));

	Background_Frame.setSize(sf::Vector2f(109.2,109.2));
	Background_Frame.setFillColor(sf::Color(216, 228, 164, 255));
	Background_Frame.setOutlineColor(sf::Color::Black);
	Background_Frame.setOutlineThickness(-2);
	Background_Frame.setPosition(sf::Vector2f(s_text_box.getPosition().x, s_text_box.getPosition().y - 130));

	t_face_leshy.loadFromFile("assets\\leshy_pixel_portraits.png");
	s_face_leshy.setTexture(t_face_leshy);
	s_face_leshy.setPosition(Background_Frame.getPosition().x - 25, Background_Frame.getPosition().y - 10);
	s_face_leshy.setScale(1.8,1.8);

	font.loadFromFile("assets\\Marksman.ttf");
	l_text.setFont(font);
	l_text.setCharacterSize(44);
	l_text.setLineSpacing(0.75);
	l_text.setPosition(s_text_box.getPosition().x + 30, s_text_box.getPosition().y + 20);
	l_text.setFillColor(DarkGray);
	s_text_leshy = "";

	t_board.loadFromFile("assets\\gbc_board_nature.jpg");
	s_board.setTexture(t_board);
	s_board.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);
	s_board.setPosition(sf::Vector2f(-125, -140));

	t_bell.loadFromFile("assets\\gbc_bellbutton_nature.png");
	s_bell.setTexture(t_bell);
	s_bell.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);
	s_bell.setTextureRect(sf::IntRect(0, 0, 91, 34));
	s_bell.setPosition(sf::Vector2f(s_board.getPosition().x + 200, s_board.getPosition().y + 272));

	t_card_placement_l_prev.loadFromFile("assets\\gbc_cardslots_0.png");
	s_card_placement_l_prev.setTexture(t_card_placement_l_prev);
	s_card_placement_l_prev.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);

	l_card_placement_prev.push_back(s_card_placement_l_prev);
	l_card_placement_prev[0].setPosition(sf::Vector2f(s_board.getPosition().x + 500, s_board.getPosition().y + 170));
	for (int i = 1; i < 4; i++)
	{
		l_card_placement_prev.push_back(s_card_placement_l_prev);
		l_card_placement_prev[i].setPosition(sf::Vector2f(l_card_placement_prev[i - 1].getPosition().x + 133, l_card_placement_prev[i - 1].getPosition().y));
	}

	t_card_placement_p.loadFromFile("assets\\gbc_cardslots_nature.png");
	s_card_placement_p.setTexture(t_card_placement_p);
	s_card_placement_p.setRotation(180);
	s_card_placement_p.setOrigin(0,56);
	s_card_placement_p.setScale(-XANDY_MULTIPLIER, XANDY_MULTIPLIER);

	t_card_placement_l.loadFromFile("assets\\gbc_cardslots_nature.png");
	s_card_placement_l.setTexture(t_card_placement_l);
	s_card_placement_l.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);

	l_card_placement.push_back(s_card_placement_l);
	l_card_placement[0].setPosition(sf::Vector2f(l_card_placement_prev[0].getPosition().x, s_board.getPosition().y + 266));
	p_card_placement.push_back(s_card_placement_p);
	p_card_placement[0].setPosition(sf::Vector2f(l_card_placement[0].getPosition().x, s_board.getPosition().y + 460));
	for (int i = 1; i < 4; i++)
	{
		l_card_placement.push_back(s_card_placement_l);
		l_card_placement[i].setPosition(sf::Vector2f(l_card_placement[i - 1].getPosition().x + 133, l_card_placement[i - 1].getPosition().y));
		p_card_placement.push_back(s_card_placement_p);
		p_card_placement[i].setPosition(sf::Vector2f(p_card_placement[i - 1].getPosition().x + 133, p_card_placement[i - 1].getPosition().y));
		v_ocupied.push_back(ocupied);
	}
	
	t_scale_indicator1.loadFromFile("assets\\gbc_cardbattle_3.png");
	t_scale_indicator2.loadFromFile("assets\\gbc_cardbattle_4.png");

	s_scale_indicator1.setTexture(t_scale_indicator1);
	s_scale_indicator1.setOrigin(s_scale_indicator1.getGlobalBounds().width / 2, 0);
	s_scale_indicator2.setTexture(t_scale_indicator2);

	s_scale_indicator2.setPosition(s_bell.getPosition().x, s_bell.getPosition().y + s_bell.getGlobalBounds().height + 35);
	s_scale_indicator1.setPosition(s_scale_indicator2.getPosition().x + 45.5 * XANDY_MULTIPLIER, s_scale_indicator2.getPosition().y - 24);

	s_scale_indicator1.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);
	s_scale_indicator2.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);

	t_scale1.loadFromFile("assets\\gbc_cardbattle_0.png");
	t_scale2.loadFromFile("assets\\gbc_cardbattle_18.png");
	t_scale3.loadFromFile("assets\\gbc_cardbattle_2.png");
	t_scale4.loadFromFile("assets\\gbc_cardbattle_1.png");

	s_scale1.setTexture(t_scale1);
	s_scale2.setTexture(t_scale2);
	s_scale2.setOrigin(s_scale2.getGlobalBounds().width / 2, 0);
	s_scale3.setTexture(t_scale3);
	s_scale3.setOrigin(s_scale3.getGlobalBounds().width / 2, 0);
	s_scale4.setTexture(t_scale4);
	s_scale4.setOrigin(s_scale4.getGlobalBounds().width / 2, 0);

	s_scale1.setScale(XANDY_MULTIPLIER,XANDY_MULTIPLIER);
	s_scale2.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);
	s_scale3.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);
	s_scale4.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);

	s_scale2.setPosition(s_scale_indicator1.getPosition().x, p_card_placement[0].getPosition().y - 18);
	s_scale3.setPosition(s_scale2.getPosition().x, s_scale2.getPosition().y + 36);

	for (int i = 0; i < 2; i++)
	{
		v_scale_plate.push_back(s_scale4);
	}
	v_scale_plate[0].setPosition(s_scale3.getPosition().x - s_scale3.getGlobalBounds().width / 1.6, s_scale3.getPosition().y - 3);
	v_scale_plate[1].setPosition(s_scale3.getPosition().x + s_scale3.getGlobalBounds().width / 1.6, s_scale3.getPosition().y - 3);

	scale_text.setFont(font);
	scale_text.setFillColor(sf::Color(230,230,185,255));
	scale_text.setOutlineColor(sf::Color::Black);
	scale_text.setOutlineThickness(-2.5);
	scale_text.setCharacterSize(44);
	scale_text.setString("x0");
	scale_text.setOrigin(scale_text.getGlobalBounds().width / 2, 0);
	for (int i = 0; i < 3; i++)
	{
		v_scale_text.push_back(scale_text);
	}
	v_scale_text[0].setPosition(v_scale_plate[0].getPosition().x + 2, v_scale_plate[0].getPosition().y + 54);
	v_scale_text[1].setPosition(v_scale_plate[1].getPosition().x + 2, v_scale_plate[1].getPosition().y + 54);

	v_scale_text[2].setPosition(s_scale2.getPosition().x + 2, s_scale2.getPosition().y + 72);
	v_scale_text[2].setString("x2");

	t_hammer.loadFromFile("assets\\gbc_cardbattle.png");
	s_hammer.setTexture(t_hammer);
	s_hammer.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);
	s_hammer.setTextureRect(sf::IntRect(47,34,29,20));
	s_hammer.setColor(sf::Color(215, 226, 163, 255));
	s_hammer.setPosition(s_scale1.getPosition().x + 125, p_card_placement[0].getPosition().y + p_card_placement[0].getGlobalBounds().height - 21);

	t_card_description1.loadFromFile("assets\\gbc_cardbattle_10.png");
	t_card_description2.loadFromFile("assets\\gbc_cardbattle_19.png");

	s_card_description1.setTexture(t_card_description1);
	s_card_description2.setTexture(t_card_description2);

	s_card_description1.setScale(XANDY_MULTIPLIER,XANDY_MULTIPLIER);
	s_card_description2.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);
	s_card_description1.setPosition(s_board.getPosition().x + 1050, l_card_placement_prev[0].getPosition().y);

	t_deck_icon.loadFromFile("assets\\gbc_cardbattle_25.png");
	s_deck_icon.setTexture(t_deck_icon);
	s_deck_icon.setPosition(s_board.getPosition().x + 1250, s_hammer.getPosition().y + 14);
	s_deck_icon.setScale(XANDY_MULTIPLIER,XANDY_MULTIPLIER);

	deck_text.setFont(font);
	deck_text.setFillColor(sf::Color(230, 230, 185, 255));
	deck_text.setOutlineColor(sf::Color::Black);
	deck_text.setOutlineThickness(-2.5);
	deck_text.setCharacterSize(40);
	deck_text.setString("x" + std::to_string(DECK_SIZE));
	deck_text.setPosition(sf::Vector2f(s_deck_icon.getPosition().x + 22, s_deck_icon.getPosition().y + 10));

	t_card_common.loadFromFile("assets\\pixel_card_empty.png");
	t_card_rare.loadFromFile("assets\\pixel_card_empty_rare.png");
	s_card.setTexture(t_card_common);
	s_card.setScale(XANDY_MULTIPLIER,XANDY_MULTIPLIER);
	s_card.setPosition(WIDTH, 530);

	t_bone_total.loadFromFile("assets\\gbc_cardbattle_8.png");
	s_bone_total.setTexture(t_bone_total);
	s_bone_total.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);
	s_bone_total.setPosition(s_bell.getPosition().x, s_board.getPosition().y + 178);

	bone_text.setFont(font);
	bone_text.setFillColor(sf::Color(230, 230, 185, 255));
	bone_text.setOutlineColor(sf::Color::Black);
	bone_text.setOutlineThickness(-2.5);
	bone_text.setCharacterSize(45);
	bone_text.setString("x" + std::to_string(BONE_COUNTER));
	bone_text.setPosition(s_bone_total.getPosition().x + s_bone_total.getGlobalBounds().width - 6, s_bone_total.getPosition().y - 2);

	t_blood_empty.loadFromFile("assets\\gbc_cardbattle_6.png");
	t_blood_full.loadFromFile("assets\\gbc_cardbattle_9.png");
	s_blood_icon.setTexture(t_blood_empty);
	s_blood_icon.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);

	for (int i = 0; i < 4; i++)
	{
		v_sacrifices_blood.push_back(s_blood_icon);
		if (i == 0)
		{
			v_sacrifices_blood[0].setPosition(s_bell.getPosition().x + s_bell.getGlobalBounds().width / 2 + 24, s_bell.getPosition().y - s_blood_icon.getGlobalBounds().height - 4);
		}
		else
		{
			v_sacrifices_blood[i].setPosition(v_sacrifices_blood[static_cast<std::vector<sf::Sprite, std::allocator<sf::Sprite>>::size_type>(i) - 1].getPosition().x + s_blood_icon.getGlobalBounds().width - 6, v_sacrifices_blood[static_cast<std::vector<sf::Sprite, std::allocator<sf::Sprite>>::size_type>(i) - 1].getPosition().y);
		}
	}

	t_batteries.loadFromFile("assets\\gbc_cardbattle.png");
	s_batteries.setTexture(t_batteries);
	s_batteries.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);
	s_batteries.setTextureRect(sf::IntRect(0, 0, 11, 25));
	
	for (int i = 0; i < 6; i++)
	{
		v_batteries.push_back(s_batteries);
		v_batteries[i].setPosition(sf::Vector2f(v_sacrifices_blood[3].getPosition().x - (28 * i), s_bone_cost.getPosition().y + 10));
	}

	t_mox_simbols.loadFromFile("assets\\gbc_cardbattle.png");
	s_mox_simbols.setTexture(t_mox_simbols);
	s_mox_simbols.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);

	for (int i = 0; i < 3; i++)
	{
		v_mox_simbols.push_back(s_mox_simbols);
		v_mox_simbols[i].setPosition(s_bell.getPosition().x + (45 * i), v_sacrifices_blood[0].getPosition().y + 3);
	}

	v_mox_simbols[0].setTextureRect(sf::IntRect(1, 57, 14, 13));
	v_mox_simbols[1].setTextureRect(sf::IntRect(16, 57, 14, 13));
	v_mox_simbols[2].setTextureRect(sf::IntRect(31, 57, 14, 13));


	t_sacrifice_simbol.loadFromFile("assets\\pixel_card_sacrifice_marker.png");
	s_sacrifice_simbol.setTexture(t_sacrifice_simbol);
	s_sacrifice_simbol.setScale(XANDY_MULTIPLIER,XANDY_MULTIPLIER);

	for (int i = 0; i < 4; i++)
	{
		v_sacrifice_simbol.push_back(s_sacrifice_simbol);
		v_sacrifice_simbol[i].setPosition(p_card_placement[i].getPosition());
		v_sacrifice_simbol[i].setColor(sf::Color(255, 255, 255, 0));
	}

	t_card_creature_squirrel.loadFromFile("assets\\pixelportrait_squirrel.png");
	t_card_creature_wolf.loadFromFile("assets\\pixelportrait_wolf.png");
	t_card_creature_coyote.loadFromFile("assets\\pixelportrait_coyote.png");
	t_card_creature_bloodhound.loadFromFile("assets\\pixelportrait_bloodhound.png");
	t_card_creature_kingfisher.loadFromFile("assets\\pixelportrait_kingfisher.png");
	t_card_creature_magpie.loadFromFile("assets\\pixelportrait_magpie.png");
	t_card_creature_blackgoat.loadFromFile("assets\\pixelportrait_blackgoat.png");
	t_card_creature_alpha.loadFromFile("assets\\pixelportrait_alpha.png");
	t_card_creature_elk.loadFromFile("assets\\pixelportrait_elk.png");
	t_card_creature_elkfaw.loadFromFile("assets\\pixelportrait_elkfawn.png");
	t_card_creature_bullfrog.loadFromFile("assets\\pixelportrait_bullfrog.png");
	t_card_creature_geck.loadFromFile("assets\\pixelportrait_geck.png");
	t_card_creature_mantisgod.loadFromFile("assets\\pixelportrait_mantisgod.png");
	t_card_creature_moosebuck.loadFromFile("assets\\pixelportrait_moosebuck.png");
	t_card_creature_wolfcub.loadFromFile("assets\\pixelportrait_wolfcub.png");
	t_card_creature_raven.loadFromFile("assets\\pixelportrait_raven.png");
	t_card_creature_ringworm.loadFromFile("assets\\pixelportrait_ringworm.png");
	t_card_creature_dire_wolf_pup.loadFromFile("assets\\pixelportrait_direwolfcub.png");
	t_card_creature_dire_wolf.loadFromFile("assets\\pixelportrait_direwolf.png");
	t_card_creature_stoat.loadFromFile("assets\\pixelportrait_stoat.png");
	t_card_creature_adder.loadFromFile("assets\\pixelportrait_adder.png");
	t_card_creature_skunk.loadFromFile("assets\\pixelportrait_skunk.png");
	t_card_creature_moleman.loadFromFile("assets\\pixelportrait_moleman.png");
	t_card_creature_mole.loadFromFile("assets\\pixelportrait_mole.png");
	t_card_creature_starvation.loadFromFile("assets\\pixelportrait_starvation.png");
	t_card_creature_cat.loadFromFile("assets\\pixelportrait_cat.png");
	t_card_creature_ouroboros.loadFromFile("assets\\pixelportrait_ouroboros.png");
	t_card_creature_urayuli.loadFromFile("assets\\pixelportrait_urayuli.png");
	t_card_creature_warren.loadFromFile("assets\\pixelportrait_warren.png");
	t_card_creature_fieldmice.loadFromFile("assets\\pixelportrait_fieldmice.png");
	t_card_creature_ratking.loadFromFile("assets\\pixelportrait_ratking.png");
	t_card_creature_grizzly.loadFromFile("assets\\pixelportrait_grizzly.png");
	t_card_creature_opossum.loadFromFile("assets\\pixelportrait_opossum.png");
	t_card_creature_rabbit.loadFromFile("assets\\pixelportrait_rabbit.png");
	t_card_creature_undeadcat.loadFromFile("assets\\pixelportrait_cat_undead.png");

	s_card_creature_squirrel.setTexture(t_card_creature_squirrel);
	s_card_creature_wolf.setTexture(t_card_creature_wolf);
	s_card_creature_coyote.setTexture(t_card_creature_coyote);
	s_card_creature_bloodhound.setTexture(t_card_creature_bloodhound);
	s_card_creature_kingfisher.setTexture(t_card_creature_kingfisher);
	s_card_creature_magpie.setTexture(t_card_creature_magpie);
	s_card_creature_blackgoat.setTexture(t_card_creature_blackgoat);
	s_card_creature_alpha.setTexture(t_card_creature_alpha);
	s_card_creature_elk.setTexture(t_card_creature_elk);
	s_card_creature_elkfaw.setTexture(t_card_creature_elkfaw);
	s_card_creature_bullfrog.setTexture(t_card_creature_bullfrog);
	s_card_creature_geck.setTexture(t_card_creature_geck);
	s_card_creature_mantisgod.setTexture(t_card_creature_mantisgod);
	s_card_creature_moosebuck.setTexture(t_card_creature_moosebuck);
	s_card_creature_wolfcub.setTexture(t_card_creature_wolfcub);
	s_card_creature_raven.setTexture(t_card_creature_raven);
	s_card_creature_ringworm.setTexture(t_card_creature_ringworm);
	s_card_creature_dire_wolf_pup.setTexture(t_card_creature_dire_wolf_pup);
	s_card_creature_dire_wolf.setTexture(t_card_creature_dire_wolf);
	s_card_creature_stoat.setTexture(t_card_creature_stoat);
	s_card_creature_adder.setTexture(t_card_creature_adder);
	s_card_creature_skunk.setTexture(t_card_creature_skunk);
	s_card_creature_moleman.setTexture(t_card_creature_moleman);
	s_card_creature_mole.setTexture(t_card_creature_mole);
	s_card_creature_starvation.setTexture(t_card_creature_starvation);
	s_card_creature_cat.setTexture(t_card_creature_cat);
	s_card_creature_ouroboros.setTexture(t_card_creature_ouroboros);
	s_card_creature_urayuli.setTexture(t_card_creature_urayuli);
	s_card_creature_warren.setTexture(t_card_creature_warren);
	s_card_creature_fieldmice.setTexture(t_card_creature_fieldmice);
	s_card_creature_ratking.setTexture(t_card_creature_ratking);
	s_card_creature_grizzly.setTexture(t_card_creature_grizzly);
	s_card_creature_opossum.setTexture(t_card_creature_opossum);
	s_card_creature_rabbit.setTexture(t_card_creature_rabbit);
	s_card_creature_undeadcat.setTexture(t_card_creature_undeadcat);

	t_sigil_MightyLeap.loadFromFile("assets\\pixelability_reach.png");
	t_sigil_Airborne.loadFromFile("assets\\pixelability_flying.png");
	t_sigil_BoneDigger.loadFromFile("assets\\pixelability_bonedigger.png");
	t_sigil_Leader.loadFromFile("assets\\pixelability_buffneighbours.png");
	t_sigil_DoubleStrike.loadFromFile("assets\\pixelability_doublestrike.png");
	t_sigil_Fledgling.loadFromFile("assets\\pixelability_evolve.png");
	t_sigil_Guardian.loadFromFile("assets\\pixelability_guarddog.png");
	t_sigil_Hefty.loadFromFile("assets\\pixelability_strafepush.png");
	t_sigil_Hoarder.loadFromFile("assets\\pixelability_tutor.png");
	t_sigil_repulsive.loadFromFile("assets\\pixelability_preventattack.png");
	t_sigil_Sprinter.loadFromFile("assets\\pixelability_strafe.png");
	t_sigil_TrifurcatedStrike.loadFromFile("assets\\pixelability_tristrike.png");
	t_sigil_Waterborne.loadFromFile("assets\\pixelability_submerge.png");
	t_sigil_WorthySacrifice.loadFromFile("assets\\pixelability_tripleblood.png");
	t_sigil_stinky.loadFromFile("assets\\pixelability_stinky.png");
	t_sigil_burrower.loadFromFile("assets\\pixelability_whackamole.png");
	t_sigil_Touchofdeath.loadFromFile("assets\\pixelability_deathtouch.png");
	t_sigil_Immortal.loadFromFile("assets\\pixelability_sacrificial.png");
	t_sigil_Unkillable.loadFromFile("assets\\pixelability_drawcopyondeath.png");
	t_sigil_RabbitHole.loadFromFile("assets\\pixelability_drawrabbits.png");
	t_sigil_BoneKing.loadFromFile("assets\\pixelability_quadruplebones.png");
	t_sigil_Fecundity.loadFromFile("assets\\pixelability_drawcopy.png");

	s_sigil_MightyLeap.setTexture(t_sigil_MightyLeap);
	s_sigil_Airborne.setTexture(t_sigil_Airborne);
	s_sigil_BoneDigger.setTexture(t_sigil_BoneDigger);
	s_sigil_Leader.setTexture(t_sigil_Leader);
	s_sigil_DoubleStrike.setTexture(t_sigil_DoubleStrike);
	s_sigil_Fledgling.setTexture(t_sigil_Fledgling);
	s_sigil_Guardian.setTexture(t_sigil_Guardian);
	s_sigil_Hefty.setTexture(t_sigil_Hefty);
	s_sigil_Hoarder.setTexture(t_sigil_Hoarder);
	s_sigil_repulsive.setTexture(t_sigil_repulsive);
	s_sigil_Sprinter.setTexture(t_sigil_Sprinter);
	s_sigil_TrifurcatedStrike.setTexture(t_sigil_TrifurcatedStrike);
	s_sigil_Waterborne.setTexture(t_sigil_Waterborne);
	s_sigil_WorthySacrifice.setTexture(t_sigil_WorthySacrifice);
	s_sigil_stinky.setTexture(t_sigil_stinky);
	s_sigil_burrower.setTexture(t_sigil_burrower);
	s_sigil_Touchofdeath.setTexture(t_sigil_Touchofdeath);
	s_sigil_Immortal.setTexture(t_sigil_Immortal);
	s_sigil_Unkillable.setTexture(t_sigil_Unkillable);
	s_sigil_RabbitHole.setTexture(t_sigil_RabbitHole);
	s_sigil_BoneKing.setTexture(t_sigil_BoneKing);
	s_sigil_Fecundity.setTexture(t_sigil_Fecundity);

	card_text.setFont(font);
	card_text.setFillColor(sf::Color(DarkGray));
	card_text.setCharacterSize(50);

	t_card_cost.loadFromFile("assets\\pixel_card_costs.png");
	s_card_cost.setTexture(t_card_cost);
	s_card_cost.setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);

	//if you read this and your name isn't Maximus then you are 100% gay with no way to remove this curse 'cause if you try you are even more gay
	//TO_D0:
	//Finish sigils
	//Leshy cards
	//Leshy dialogues
	//Leshy Mechanics
	//Death Section
	//Deck Builder
	//Polish (not the nacionality or language)
}