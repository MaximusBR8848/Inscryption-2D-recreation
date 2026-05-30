#include "Inscryption.hpp"

void InscryptionGame::Create_Window()
{
	switch (fullscreen)
	{
	case 0:
		window->create
		(
			sf::VideoMode(WIDTH, HEIGHT),
			Window_Name,
			sf::Style::Titlebar | sf::Style::Close
		);
		break;
	case 1:
		window->create
		(
			sf::VideoMode(WIDTH, HEIGHT),
			Window_Name,
			sf::Style::Fullscreen
		);
		break;
	}
	window->setMouseCursorVisible(false);
}

void InscryptionGame::DrawGame()
{
	window->clear();
	if (menu == false)
	{
		window->draw(s_board);
		for (auto& s_card_placement_l : l_card_placement)
		{
			window->draw(s_card_placement_l);
		}
		for (auto& s_card_placement_l_prev : l_card_placement_prev)
		{
			window->draw(s_card_placement_l_prev);
		}
		for (auto& s_card_placement_p : p_card_placement)
		{
			window->draw(s_card_placement_p);
		}
		window->draw(s_scale3);
		window->draw(s_scale2);
		for (auto& s_scale4 : v_scale_plate)
		{
			window->draw(s_scale4);
		}
		for (auto& scale_text : v_scale_text)
		{
			window->draw(scale_text);
		}
		window->draw(s_scale_indicator1);
		window->draw(s_scale_indicator2);
		window->draw(s_bell);
		window->draw(s_card_description1);
		window->draw(s_deck_icon);
		window->draw(deck_text);
		window->draw(s_bone_total);
		window->draw(bone_text);
		window->draw(s_hammer);
		for (auto& s_blood_cost : v_sacrifices_blood)
		{
			window->draw(s_blood_cost);
		}
		for (auto& s_batteries : v_batteries)
		{
			window->draw(s_batteries);
		}
		for (auto& s_mox_simbols : v_mox_simbols)
		{
			window->draw(s_mox_simbols);
		}
		for (int i = 0; i < v_card.size(); i++)
		{
			if (v_card[i].getPosition().x < WIDTH - 1 && v_card[i].getGlobalBounds().width > 0 && v_card[i].getPosition().y < HEIGHT - 1 && v_card[i].getGlobalBounds().height > 0)
			{
				window->draw(v_card[i]);
				window->draw(v_creature_card[i]);
				window->draw(v_card_cost[i]);
				window->draw(v_card_sigil_1[i]);
				window->draw(v_card_sigil_2[i]);
				window->draw(v_text_card_attk[i]);
				window->draw(v_text_card_hp[i]);
			}
		}
		for (auto& s_sacrifice_simbol : v_sacrifice_simbol)
		{
			window->draw(s_sacrifice_simbol);
		}

		if (leshy_mad == true)
		{
			window->draw(s_text_box);
			window->draw(Background_Frame);
			window->draw(s_face_leshy);
			window->draw(l_text);
		}
	}
	else
	{
		window->draw(s_menu_background);
		window->draw(s_icon_plate_attach);
		window->draw(s_icon_continue);
	}
	window->draw(s_cursor);
	window->draw(Layer_Effect);
	window->display();
}

void InscryptionGame::CursorStates()
{
	if (!sacrificing && !positionating && !smashing && cursor_clock.getElapsedTime().asMilliseconds() >= 220)
	{
		CURSOR_STATE = NORMAL;
	}
	else if (sacrificing == true)
	{
		if (BUTTON_STATE == BUTTON_PRESSED)
		{
			CURSOR_STATE = SACRIFICING_PRESSED;
			cursor_clock.restart();
		}
		else
		{
			CURSOR_STATE = SACRIFICING;
		}
	}
	else if (positionating == true)
	{
		if (BUTTON_STATE == BUTTON_PRESSED)
		{
			CURSOR_STATE = POSITIONING_PRESSED;
			cursor_clock.restart();
		}
		else
		{
			CURSOR_STATE = POSITIONING;
		}
	}
	else if (smashing == true)
	{
		if (BUTTON_STATE == BUTTON_PRESSED)
		{
			CURSOR_STATE = SMASHING_PRESSED;
			cursor_clock.restart();
		}
		else
		{
			CURSOR_STATE = SMASHING;
		}
	}

	switch (CURSOR_STATE)
	{
	case NORMAL:
		s_cursor.setTextureRect(sf::IntRect(0, 56, 10, 25));
		break;
	case SACRIFICING:
		s_cursor.setTextureRect(sf::IntRect(62, 52, 11, 19));
		break;
	case SACRIFICING_PRESSED:
		s_cursor.setTextureRect(sf::IntRect(77, 56, 11, 16));
		break;
	case POSITIONING:
		s_cursor.setTextureRect(sf::IntRect(1, 28, 13, 18));
		break;
	case POSITIONING_PRESSED:
		s_cursor.setTextureRect(sf::IntRect(18, 32, 13, 14));
		break;
	case SMASHING:
		s_cursor.setTextureRect(sf::IntRect(202, 3, 13, 20));
		break;
	case SMASHING_PRESSED:
		s_cursor.setTextureRect(sf::IntRect(218, 10, 20, 13));
		break;
	}
}

void InscryptionGame::Events()
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window->close();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F11))
		{
			fullscreen = !fullscreen;
			Create_Window();
		}
		else if (event.type == sf::Event::LostFocus || !window->hasFocus())
		{
			if (menu == false)
				music1.pause();
			else
				music2.pause();
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			if (menu == false)
				music1.play();
			else
				music2.play();
		}

		if (PRESS_INPUTS)
		{
			BUTTON_STATE = BUTTON_PRESSED;
		}
		else
		{
			BUTTON_STATE = BUTTON_IDLE;
		}

		if (PASS_INPUTS)
		{
			PLAYER_INPUT = PASS_INPUT;
		}
		if (SKIP_INPUTS)
		{
			PLAYER_INPUT = SKIP_INPUT;
		}
		else if (!(PASS_INPUTS) && !(SKIP_INPUTS))
		{
			PLAYER_INPUT = IDDLE;
		}

		switch (fullscreen)
		{
		case 0: s_cursor.setPosition((float)mouse.getPosition(*window).x, (float)mouse.getPosition(*window).y + (short)BUTTON_STATE); break;
		case 1:	s_cursor.setPosition((float)mouse.getPosition().x, (float)mouse.getPosition().y + (short)BUTTON_STATE); break;
		}
	}
}

void InscryptionGame::DrawFromDeck()
{
	TURN_OWNER = PLAYER_TURN;
	if (DECK_SIZE > 0)
	{
		DECK_SIZE--;
		if (DECK_SIZE == 2)
		{
			deck_text.setFillColor(sf::Color(DarkRed));
			s_deck_icon.setColor(sf::Color(DarkRed));
		}
		deck_text.setString("x" + std::to_string(DECK_SIZE));
		CreateCard();
	}
}

void InscryptionGame::CreateCard()
{
	SIGIL_1 = None;
	SIGIL_2 = None;
	player_placement.push_back(PLAYER_PLACEMENT);
	s_card_cost.setTextureRect(sf::IntRect(0, 0, 0, 0));

	switch (CARD_NUMBER)
	{
	case Squirrel:

		HP = 1;
		ATTK = 0;
		v_creature_card.push_back(s_card_creature_squirrel);
		RARITY = COMMON;

		break;
	case Wolf:

		BLOOD_COST = 2;
		HP = 2;
		ATTK = 3;
		v_creature_card.push_back(s_card_creature_wolf);
		RARITY = COMMON;

		break;
	case Coyote:

		BONE_COST = 2;
		HP = 1;
		ATTK = 2;
		v_creature_card.push_back(s_card_creature_coyote);
		RARITY = COMMON;

		break;
	case Bloodhound:

		BLOOD_COST = 2;
		HP = 3;
		ATTK = 2;
		v_creature_card.push_back(s_card_creature_bloodhound);
		RARITY = COMMON;
		SIGIL_1 = Guardian;

		break;
	case Kingfisher:

		BLOOD_COST = 1;
		HP = 1;
		ATTK = 1;
		v_creature_card.push_back(s_card_creature_kingfisher);
		RARITY = COMMON;
		SIGIL_1 = Airborne;
		SIGIL_2 = Waterborne;

		break;
	case BlackGoat:

		BLOOD_COST = 1;
		HP = 1;
		ATTK = 0;
		v_creature_card.push_back(s_card_creature_blackgoat);
		RARITY = COMMON;
		SIGIL_1 = WorthySacrifice;

		break;
	case Magpie:

		BLOOD_COST = 2;
		HP = 1;
		ATTK = 1;
		v_creature_card.push_back(s_card_creature_magpie);
		RARITY = COMMON;
		SIGIL_1 = Airborne;
		SIGIL_2 = Hoarder;

		break;
	case Alpha:

		BONE_COST = 4;
		HP = 3;
		ATTK = 1;
		v_creature_card.push_back(s_card_creature_alpha);
		RARITY = COMMON;
		SIGIL_1 = Leader;

		break;
	case Elk:

		BLOOD_COST = 2;
		HP = 4;
		ATTK = 2;
		v_creature_card.push_back(s_card_creature_elk);
		RARITY = COMMON;
		SIGIL_1 = Sprinter;

		break;
	case ElkFawn:

		BLOOD_COST = 1;
		HP = 1;
		ATTK = 1;
		v_creature_card.push_back(s_card_creature_elkfaw);
		RARITY = COMMON;
		SIGIL_1 = Sprinter;
		SIGIL_2 = Fledgling;

		break;
	case BullFrog:

		BLOOD_COST = 1;
		HP = 2;
		ATTK = 1;
		v_creature_card.push_back(s_card_creature_bullfrog);
		RARITY = COMMON;
		SIGIL_1 = MightyLeap;

		break;
	case Geck:

		HP = 1;
		ATTK = 1;
		v_creature_card.push_back(s_card_creature_geck);
		RARITY = RARE;

		break;
	case MantisGod:

		BLOOD_COST = 1;
		HP = 1;
		ATTK = 1;
		v_creature_card.push_back(s_card_creature_mantisgod);
		RARITY = RARE;
		SIGIL_1 = TrifurcatedStrike;

		break;
	case MooseBuck:

		BLOOD_COST = 3;
		HP = 7;
		ATTK = 3;
		v_creature_card.push_back(s_card_creature_moosebuck);
		RARITY = COMMON;
		SIGIL_1 = Hefty;

		break;
	case Raven:

		BLOOD_COST = 2;
		HP = 3;
		ATTK = 2;
		v_creature_card.push_back(s_card_creature_raven);
		RARITY = COMMON;
		SIGIL_1 = Airborne;

		break;
	case DireWolfPup:

		BLOOD_COST = 2;
		HP = 1;
		ATTK = 1;
		v_creature_card.push_back(s_card_creature_dire_wolf_pup);
		RARITY = COMMON;
		SIGIL_1 = BoneDigger;
		SIGIL_2 = Fledgling;

		break;
	case DireWolf:

		BLOOD_COST = 3;
		HP = 5;
		ATTK = 2;
		v_creature_card.push_back(s_card_creature_dire_wolf);
		RARITY = COMMON;
		SIGIL_1 = DoubleStrike;

		break;
	case WolfCub:

		BLOOD_COST = 1;
		HP = 1;
		ATTK = 1;
		v_creature_card.push_back(s_card_creature_wolfcub);
		RARITY = COMMON;
		SIGIL_1 = Fledgling;

		break;
	case Stoat:

		BLOOD_COST = 1;
		HP = 2;
		ATTK = 1;
		v_creature_card.push_back(s_card_creature_stoat);
		RARITY = COMMON;
		break;
	case Skunk:

		BLOOD_COST = 1;
		HP = 3;
		ATTK = 0;
		v_creature_card.push_back(s_card_creature_skunk);
		RARITY = COMMON;
		SIGIL_1 = Stinky;

		break;
	case Mole:

		BLOOD_COST = 1;
		HP = 4;
		ATTK = 0;
		v_creature_card.push_back(s_card_creature_mole);
		RARITY = COMMON;
		SIGIL_1 = Burrower;

		break;
	case Adder:

		BLOOD_COST = 2;
		HP = 1;
		ATTK = 1;
		v_creature_card.push_back(s_card_creature_adder);
		RARITY = COMMON;
		SIGIL_1 = TouchofDeath;

		break;
	case MoleMan:

		BLOOD_COST = 1;
		HP = 6;
		ATTK = 0;
		v_creature_card.push_back(s_card_creature_moleman);
		RARITY = RARE;
		SIGIL_1 = Burrower;
		SIGIL_2 = MightyLeap;

		break;
	case Cat:

		BLOOD_COST = 1;
		HP = 1;
		ATTK = 0;
		v_creature_card.push_back(s_card_creature_cat);
		RARITY = COMMON;
		SIGIL_1 = Immortal;

		break;
	case Ouroboros:

		BLOOD_COST = 2;
		HP = 1;
		ATTK = 1;
		v_creature_card.push_back(s_card_creature_ouroboros);
		RARITY = RARE;
		SIGIL_1 = Unkillable;

		break;
	case Urayuli:

		BLOOD_COST = 4;
		HP = 7;
		ATTK = 7;
		v_creature_card.push_back(s_card_creature_urayuli);
		RARITY = RARE;

		break;
	case Warren:

		BLOOD_COST = 1;
		HP = 1;
		ATTK = 0;
		v_creature_card.push_back(s_card_creature_warren);
		RARITY = COMMON;
		SIGIL_1 = RabbitHole;

		break;
	case FieldMice:

		BLOOD_COST = 2;
		HP = 2;
		ATTK = 2;
		v_creature_card.push_back(s_card_creature_fieldmice);
		RARITY = COMMON;
		SIGIL_1 = Fecundity;

		break;
	case RatKing:

		BLOOD_COST = 2;
		HP = 1;
		ATTK = 2;
		v_creature_card.push_back(s_card_creature_ratking);
		RARITY = COMMON;
		SIGIL_1 = BoneKing;

		break;
	case Grizzly:

		BLOOD_COST = 3;
		HP = 6;
		ATTK = 4;
		v_creature_card.push_back(s_card_creature_grizzly);
		RARITY = COMMON;

		break;
	case Opossum:

		BONE_COST = 2;
		HP = 1;
		ATTK = 1;
		v_creature_card.push_back(s_card_creature_opossum);
		RARITY = COMMON;

		break;
	case Rabbit:

		HP = 1;
		ATTK = 0;
		v_creature_card.push_back(s_card_creature_rabbit);
		RARITY = COMMON;

		break;
	default:

		BLOOD_COST = 1;
		HP = 1;
		ATTK = 0;
		v_creature_card.push_back(s_card_creature_ringworm);
		RARITY = COMMON;

		break;
	}

	switch (BLOOD_COST)
	{
	case 1:
		s_card_cost.setTextureRect(sf::IntRect(29 , 1, 25, 15));
		break;
	case 2:
		s_card_cost.setTextureRect(sf::IntRect(29, 17, 25, 15));
		break;
	case 3:
		s_card_cost.setTextureRect(sf::IntRect(29, 33, 25, 15));
		break;
	case 4:
		s_card_cost.setTextureRect(sf::IntRect(29, 49, 25, 15));
		break;
	default:
		break;
	}

	switch (BONE_COST)
	{
	case 1:
		s_card_cost.setTextureRect(sf::IntRect(1, 1, 25, 15));
		break;
	case 2:
		s_card_cost.setTextureRect(sf::IntRect(1, 17, 25, 15));
		break;
	case 3:
		s_card_cost.setTextureRect(sf::IntRect(1, 33, 25, 15));
		break;
	case 4:
		s_card_cost.setTextureRect(sf::IntRect(1, 49, 25, 15));
		break;
	case 5:
		s_card_cost.setTextureRect(sf::IntRect(1, 65, 25, 15));
		break;
	case 6:
		s_card_cost.setTextureRect(sf::IntRect(1, 81, 25, 15));
		break;
	case 7:
		s_card_cost.setTextureRect(sf::IntRect(1, 97, 25, 15));
		break;
	case 8:
		s_card_cost.setTextureRect(sf::IntRect(1, 113, 25, 15));
		break;
	default:
		break;
	}

	switch (RARITY)
	{
	case COMMON:
		s_card.setTexture(t_card_common);
		break;
	case RARE:
		s_card.setTexture(t_card_rare);
		break;
	}

	v_card.push_back(s_card);

	switch (SIGIL_1)
	{
	case None:
		v_card_sigil_1.push_back(s_null);
		break;
	case MightyLeap:
		v_card_sigil_1.push_back(s_sigil_MightyLeap);
		break;
	case Airborne:
		v_card_sigil_1.push_back(s_sigil_Airborne);
		break;
	case Sprinter:
		v_card_sigil_1.push_back(s_sigil_Sprinter);
		break;
	case Fledgling:
		v_card_sigil_1.push_back(s_sigil_Fledgling);
		break;
	case Hoarder:
		v_card_sigil_1.push_back(s_sigil_Hoarder);
		break;
	case Waterborne:
		v_card_sigil_1.push_back(s_sigil_Waterborne);
		break;
	case Guardian:
		v_card_sigil_1.push_back(s_sigil_Guardian);
		break;
	case WorthySacrifice:
		v_card_sigil_1.push_back(s_sigil_WorthySacrifice);
		break;
	case TrifurcatedStrike:
		v_card_sigil_1.push_back(s_sigil_TrifurcatedStrike);
		break;
	case BoneDigger:
		v_card_sigil_1.push_back(s_sigil_BoneDigger);
		break;
	case DoubleStrike:
		v_card_sigil_1.push_back(s_sigil_DoubleStrike);
		break;
	case Leader:
		v_card_sigil_1.push_back(s_sigil_Leader);
		break;
	case Repulsive:
		v_card_sigil_1.push_back(s_sigil_repulsive);
		break;
	case Hefty:
		v_card_sigil_1.push_back(s_sigil_Hefty);
		break;
	case Stinky:
		v_card_sigil_1.push_back(s_sigil_stinky);
		break;
	case Burrower:
		v_card_sigil_1.push_back(s_sigil_burrower);
		break;
	case TouchofDeath:
		v_card_sigil_1.push_back(s_sigil_Touchofdeath);
		break;
	case Immortal:
		v_card_sigil_1.push_back(s_sigil_Immortal);
		break;
	case Unkillable:
		v_card_sigil_1.push_back(s_sigil_Unkillable);
		break;
	case RabbitHole:
		v_card_sigil_1.push_back(s_sigil_RabbitHole);
		break;
	case BoneKing:
		v_card_sigil_1.push_back(s_sigil_BoneKing);
		break;
	case Fecundity:
		v_card_sigil_1.push_back(s_sigil_Fecundity);
		break;
	}

	switch (SIGIL_2)
	{
	case None:
		v_card_sigil_2.push_back(s_null);
		break;
	case MightyLeap:
		v_card_sigil_2.push_back(s_sigil_MightyLeap);
		break;
	case Airborne:
		v_card_sigil_2.push_back(s_sigil_Airborne);
		break;
	case Sprinter:
		v_card_sigil_2.push_back(s_sigil_Sprinter);
		break;
	case Fledgling:
		v_card_sigil_2.push_back(s_sigil_Fledgling);
		break;
	case Hoarder:
		v_card_sigil_2.push_back(s_sigil_Hoarder);
		break;
	case Waterborne:
		v_card_sigil_2.push_back(s_sigil_Waterborne);
		break;
	case Guardian:
		v_card_sigil_2.push_back(s_sigil_Guardian);
		break;
	case WorthySacrifice:
		v_card_sigil_2.push_back(s_sigil_WorthySacrifice);
		break;
	case TrifurcatedStrike:
		v_card_sigil_2.push_back(s_sigil_TrifurcatedStrike);
		break;
	case BoneDigger:
		v_card_sigil_2.push_back(s_sigil_BoneDigger);
		break;
	case DoubleStrike:
		v_card_sigil_2.push_back(s_sigil_DoubleStrike);
		break;
	case Leader:
		v_card_sigil_2.push_back(s_sigil_Leader);
		break;
	case Repulsive:
		v_card_sigil_2.push_back(s_sigil_repulsive);
		break;
	case Hefty:
		v_card_sigil_2.push_back(s_sigil_Hefty);
		break;
	case Stinky:
		v_card_sigil_2.push_back(s_sigil_stinky);
		break;
	case Burrower:
		v_card_sigil_2.push_back(s_sigil_burrower);
		break;
	case TouchofDeath:
		v_card_sigil_2.push_back(s_sigil_Touchofdeath);
		break;
	case Immortal:
		v_card_sigil_2.push_back(s_sigil_Immortal);
		break;
	case Unkillable:
		v_card_sigil_2.push_back(s_sigil_Unkillable);
		break;
	case RabbitHole:
		v_card_sigil_2.push_back(s_sigil_RabbitHole);
		break;
	case BoneKing:
		v_card_sigil_2.push_back(s_sigil_BoneKing);
		break;
	case Fecundity:
		v_card_sigil_2.push_back(s_sigil_Fecundity);
		break;
	}

	for (this->CARD_STEP = CARD_STEP; CARD_STEP < v_card.size(); CARD_STEP++)
	{
		v_creature_card[CARD_STEP].setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);
		if (CARD_NUMBER != MoleMan && CARD_NUMBER != UndeadCat)
		{
			v_creature_card[CARD_STEP].setColor(sf::Color(DarkGray));
		}
		v_card_sigil_1[CARD_STEP].setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);
		v_card_sigil_2[CARD_STEP].setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);

		v_card_sigil_1[CARD_STEP].setColor(sf::Color(DarkGray));
		v_card_sigil_2[CARD_STEP].setColor(sf::Color(DarkGray));

		v_text_card_hp.push_back(card_text);
		v_text_card_attk.push_back(card_text);
		v_card_cost.push_back(s_card_cost);

		v_card_cost[CARD_STEP].setOrigin(25, 0);

		blood_cost.push_back(BLOOD_COST);
		bone_cost.push_back(BONE_COST);
		card_id.push_back(CARD_NUMBER);
		card_attk.push_back(ATTK);
		card_hp.push_back(HP);
		sigil_type_1.push_back(SIGIL_1);
		sigil_type_2.push_back(SIGIL_2);

		v_on_board.push_back(on_board);
		v_sacrificed.push_back(sacrificed);

		v_text_card_hp[CARD_STEP].setString(std::to_string(HP));
		v_text_card_attk[CARD_STEP].setString(std::to_string(ATTK));
		card_opacity.push_back((std::int16_t)CARD_OPACITY);

		BLOOD_COST = 0;
		BONE_COST = 0;
	}

	for (int i = 0; i < v_card.size(); i++)
	{
		std::uniform_int_distribution<int> RANDOM_CARD(0, 32);
		CARD_NUMBER = RANDOM_CARD(Random_Card_Var);
	}
}

void InscryptionGame::DrawCard()//112 px
{
	for (int I = 0; I < 4; I++)
	{
		for (int i = 0; i < v_card.size(); i++)
		{

		bool isMouseOverCardHand = s_cursor.getPosition().x >= v_card[i].getPosition().x
			&& s_cursor.getPosition().x <= v_card[i].getPosition().x + v_card[i].getGlobalBounds().width
			&& s_cursor.getPosition().y >= v_card[i].getPosition().y
			&& s_cursor.getPosition().y <= v_card[i].getPosition().y + v_card[i].getGlobalBounds().height
			&& !v_on_board[i];

		bool isMouseOverCardBoard = s_cursor.getPosition().x >= v_card[i].getPosition().x
			&& s_cursor.getPosition().x <= v_card[i].getPosition().x + v_card[i].getGlobalBounds().width
			&& s_cursor.getPosition().y >= v_card[i].getPosition().y
			&& s_cursor.getPosition().y <= v_card[i].getPosition().y + v_card[i].getGlobalBounds().height;

		bool isMouseOverPlacement = s_cursor.getPosition().x >= p_card_placement[I].getPosition().x
			&& s_cursor.getPosition().x <= p_card_placement[I].getPosition().x + p_card_placement[I].getGlobalBounds().width
			&& s_cursor.getPosition().y >= p_card_placement[I].getPosition().y
			&& s_cursor.getPosition().y <= p_card_placement[I].getPosition().y + p_card_placement[I].getGlobalBounds().height;

			if (v_card_sigil_2[i].getGlobalBounds().width > 20)
			{
				v_card_sigil_1[i].setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);
				v_card_sigil_2[i].setScale(XANDY_MULTIPLIER, XANDY_MULTIPLIER);

				v_card_sigil_1[i].setPosition(v_card[i].getPosition().x + 12, v_card[i].getPosition().y + 93);
			}
			else
			{
				v_card_sigil_1[i].setPosition(v_card[i].getPosition().x + 39, v_card[i].getPosition().y + 93);
			}
			v_card_sigil_2[i].setPosition(v_card_sigil_1[i].getPosition().x + v_card_sigil_1[i].getGlobalBounds().width + 4, v_card_sigil_1[i].getPosition().y);

			float velocity_x = v_card[i].getPosition().x / 150;

			if (v_on_board[i] == false && v_sacrificed[i] == false)
			{
				if (v_card[i].getPosition().x > 100 * v_card.size() - 100)
				{
					v_card[i].setPosition(sf::Vector2f(v_card[i].getPosition().x - velocity_x, v_card[i].getPosition().y));
				}

				if (isMouseOverCardHand && positionating == false && sacrificing == false)
				{
					//make border
				}
				else if (!(isMouseOverCardHand) && positionating == false && sacrificing == false)
				{
					//undo border
				}
			}

			v_creature_card[i].setPosition(sf::Vector2f(v_card[i].getPosition().x + 3, v_card[i].getPosition().y + 3));
			v_text_card_hp[i].setPosition(v_creature_card[i].getPosition().x + 100, v_text_card_attk[i].getPosition().y);
			v_text_card_attk[i].setPosition(v_creature_card[i].getPosition().x + 5, v_creature_card[i].getPosition().y + 108);
			v_card_cost[i].setPosition(v_card[i].getPosition().x + v_card[i].getGlobalBounds().width - 2, v_card[i].getPosition().y + 2);
		}
	}
}

void InscryptionGame::CardAttackPlayer()
{
	for (int i = 0; i < v_card.size(); i++)
	{
		if (card_attk[i] != 0 && v_on_board[i] == true && animation_clock.getElapsedTime().asMilliseconds() > 1000)
		{
			SCALE_POINTS += card_attk[i];
		}
	}
}

void InscryptionGame::PlayCard()
{
	bool isMouseOverHammer = s_cursor.getPosition().x >= s_hammer.getPosition().x
		&& s_cursor.getPosition().x <= s_hammer.getPosition().x + s_hammer.getGlobalBounds().width
		&& s_cursor.getPosition().y >= s_hammer.getPosition().y
		&& s_cursor.getPosition().y <= s_hammer.getPosition().y + s_hammer.getGlobalBounds().height;

	for (int I = 0; I < 4; I++)
	{
		bool isMouseOverPlacement = s_cursor.getPosition().x >= p_card_placement[I].getPosition().x
			&& s_cursor.getPosition().x <= p_card_placement[I].getPosition().x + p_card_placement[I].getGlobalBounds().width
			&& s_cursor.getPosition().y >= p_card_placement[I].getPosition().y
			&& s_cursor.getPosition().y <= p_card_placement[I].getPosition().y + p_card_placement[I].getGlobalBounds().height;

		for (int i = 0; i < v_card.size(); i++)
		{
			bool isMouseOverCardHand = s_cursor.getPosition().x >= v_card[i].getPosition().x
				&& s_cursor.getPosition().x <= v_card[i].getPosition().x + v_card[i].getGlobalBounds().width
				&& s_cursor.getPosition().y >= v_card[i].getPosition().y
				&& s_cursor.getPosition().y <= v_card[i].getPosition().y + v_card[i].getGlobalBounds().height
				&& !v_on_board[i];

			bool isMouseOverCardBoard = s_cursor.getPosition().x >= v_card[i].getPosition().x
				&& s_cursor.getPosition().x <= v_card[i].getPosition().x + v_card[i].getGlobalBounds().width
				&& s_cursor.getPosition().y >= v_card[i].getPosition().y
				&& s_cursor.getPosition().y <= v_card[i].getPosition().y + v_card[i].getGlobalBounds().height
				&& v_on_board[i];


			if (BUTTON_STATE == BUTTON_PRESSED && isMouseOverCardHand
				&& positionating == false && sacrificing == false
				&& v_on_board[i] == false && v_sacrificed[i] == false)
			{
				CARD_SELECTED = i;
				if (blood_cost[i] > 0 && blood_cost[i] < 4 && CARDS_ON_BOARD >= blood_cost[i]
					|| blood_cost[i] == 4 && CARDS_ON_BOARD - 1 >= blood_cost[i])
				{
					sacrificing = 1;
				}
				else if (CARDS_ON_BOARD < 4 && bone_cost[i] <= BONE_COUNTER && blood_cost[i] == 0 || CARDS_ON_BOARD < 4 && bone_cost[i] == 0 && blood_cost[i] == 0)
				{
					BONE_COUNTER -= bone_cost[i];
					positionating = 1;
				}
				else if (blood_cost[i] > CARDS_ON_BOARD || bone_cost[i] > BONE_COUNTER || CARDS_ON_BOARD >= 4)
				{
					std::cout << "YOU CAN'T PLACE THAT" << std::endl;
				}

				std::cout

					<< "CARD_INFO |" << i << "| ID:" << card_id[i] << " COST : " << blood_cost[i] << ", " << bone_cost[i] << " DAMAGE : " << card_attk[i] << " HP : " << card_hp[i]
					<< " P:" << positionating << " S:" << sacrificing << " ON_B:" << v_on_board[i] << " BONES:"
					<< BONE_COUNTER << " SACS:" << SACRIFICES << " SIGILS: " << sigil_type_1[i] << ", " << sigil_type_2[i] <<

					std::endl;

			}

			//POSITIONING
			if (BUTTON_STATE == BUTTON_PRESSED && isMouseOverPlacement
				&& v_ocupied[I] == false && positionating == true
				&& sacrifice_wait.getElapsedTime().asMilliseconds() >= 500)
			{
				DesiredPosition.x = p_card_placement[I].getPosition().x;
				DesiredPosition.y = p_card_placement[I].getPosition().y;
				v_card[CARD_SELECTED].setPosition(sf::Vector2f(DesiredPosition.x, DesiredPosition.y));
				player_placement[i] = I;
				v_on_board[CARD_SELECTED] = 1;
				CARD_SELECTED = -1;
				positionating = 0;
				v_ocupied[I] = 1;
				bone_text.setString("x" + std::to_string(BONE_COUNTER));
				CARDS_ON_BOARD++;

				std::cout << "Your card is in: " << player_placement[i] << std::endl;
			}
			//SACRIFICING
			else if (BUTTON_STATE == BUTTON_PRESSED && isMouseOverCardBoard && isMouseOverPlacement
				&& sacrificing == true && v_ocupied[I] == true && v_sacrificed[i] == false && v_on_board[i] == true)
			{
				SACRIFICES++;
				CARDS_ON_BOARD--;
				v_sacrifice_simbol[I].setColor(sf::Color(255, 255, 255, 255));
				v_sacrificed[i] = 1;
				v_on_board[i] = 0;
				v_ocupied[I] = 0;

				if (SACRIFICES >= blood_cost[CARD_SELECTED])
				{
					BONE_COUNTER += SACRIFICES;
					bone_text.setString("x" + std::to_string(BONE_COUNTER));
					sacrificing = 0;
					SACRIFICES = 0;
					positionating = 1;
				}
				if (SACRIFICES < blood_cost[CARD_SELECTED])
				{
					sacrifice_wait.restart();
				}
			}
			//SMASHING
			if (BUTTON_STATE == BUTTON_PRESSED && isMouseOverCardBoard && isMouseOverPlacement && smashing)
			{
				smashing = 0;
			}
		}
		if (BUTTON_STATE == BUTTON_PRESSED && isMouseOverHammer && !sacrificing && !positionating && !smashing)
		{
			smashing = 1;
		}
		else if (BUTTON_STATE == BUTTON_PRESSED && !isMouseOverPlacement && !isMouseOverHammer)
		{
			smashing = 0;
		}
	}
}

void InscryptionGame::CardPerishing()
{
	for (int i = 0; i < v_card.size(); i++)
	{
		for (int I = 0; I < 4; I++)
		{
			if (v_sacrificed[i] == true && card_opacity[i] > 10 && !sacrificing
				&& p_card_placement[I].getPosition() == v_card[i].getPosition())
			{
				card_opacity[i] -= (std::int16_t)10;
				v_card[i].setColor(sf::Color((std::int8_t)card_opacity[i], (std::int8_t)card_opacity[i], (std::int8_t)card_opacity[i], (std::int8_t)255));
				v_creature_card[i].setColor(sf::Color((std::int8_t)card_opacity[i], (std::int8_t)card_opacity[i], (std::int8_t)card_opacity[i], (std::int8_t)255));
				v_card_cost[i].setColor(sf::Color((std::int8_t)card_opacity[i], (std::int8_t)card_opacity[i], (std::int8_t)card_opacity[i], (std::int8_t)255));
				player_placement[i] = -1;
				if (card_succumb_sound.Playing)
				{
					card_succumb_sound.play();
				}
			}
			else if (v_sacrificed[i] && !sacrificing && card_opacity[i] <= 10)
			{
				v_on_board[i] = 0;
				v_card[i].setPosition(WIDTH,HEIGHT);
				v_sacrifice_simbol[I].setColor(sf::Color((std::int8_t)255, (std::int8_t)255, (std::int8_t)255, (std::int8_t)0));
			}
		}
	}
}

void InscryptionGame::TurnEvents()
{
	bool isMouseOverBell = s_cursor.getPosition().x >= s_bell.getPosition().x
		&& s_cursor.getPosition().x <= s_bell.getPosition().x + s_bell.getGlobalBounds().width
		&& s_cursor.getPosition().y >= s_bell.getPosition().y
		&& s_cursor.getPosition().y <= s_bell.getPosition().y + s_bell.getGlobalBounds().height;

	if (TURN_OWNER == PLAYER_TURN && !sacrificing && !positionating && !smashing)
	{
		if (BUTTON_STATE != BUTTON_PRESSED && isMouseOverBell)
			BELL_STATE = BELL_SELECTED;

		if (BUTTON_STATE == BUTTON_PRESSED && BELL_STATE == BELL_SELECTED || PASS_INPUTS)
		{
			BELL_STATE = BELL_USED;
			TURN_OWNER = EVENT_TURN;
			bell_clock.restart();
		}
		else if (BUTTON_STATE == BUTTON_IDLE && !(isMouseOverBell))
			BELL_STATE = BELL_NORMAL;
	}
	else if (TURN_OWNER == EVENT_TURN && bell_clock.getElapsedTime().asMilliseconds() >= 400
		&& TURN_OWNER == EVENT_TURN && bell_clock.getElapsedTime().asMilliseconds() <= 700)
	{
		CardAttackPlayer();
		BELL_STATE = BELL_UNLIT;
		TURN_OWNER = LESHY_TURN;
	}
	if (TURN_OWNER == LESHY_TURN && bell_clock.getElapsedTime().asMilliseconds() >= 1200)
	{
		TURN_NUMBER++;
		DrawFromDeck();
		if (BATTERY_CHARGE < 6)
		BATTERY_CHARGE++;
	}

	switch (BELL_STATE)
	{
	case BELL_NORMAL:
		s_bell.setTextureRect(sf::IntRect(0, 0, 91, 36));
		break;
	case BELL_UNLIT:
		s_bell.setTextureRect(sf::IntRect(93, 0, 91, 36));
		break;
	case BELL_SELECTED:
		s_bell.setTextureRect(sf::IntRect(93, 39, 91, 36));
		break;
	case BELL_USED:
		s_bell.setTextureRect(sf::IntRect(0, 39, 91, 36));
		break;
	}
}

void InscryptionGame::MenuEvents()
{
	bool isMouseOverIcon = s_cursor.getPosition().x >= s_icon_continue.getPosition().x
		&& s_cursor.getPosition().x <= s_icon_continue.getPosition().x + 126
		&& s_cursor.getPosition().y >= s_icon_continue.getPosition().y
		&& s_cursor.getPosition().y <= s_icon_continue.getPosition().y + 168;

	unsigned short Time;
	Time = 1600;

	if (!continue_move)
	{
		if (delay_clock.getElapsedTime().asMilliseconds() < Time)
		{
			s_icon_plate_attach.setTexture(t_icon_plate_dark);
		}
		else if (delay_clock.getElapsedTime().asMilliseconds() >= Time && delay_clock.getElapsedTime().asMilliseconds() < Time * 2)
		{
			s_icon_plate_attach.setTexture(t_icon_plate_midlight);
		}
		else if (delay_clock.getElapsedTime().asMilliseconds() >= Time * 2)
		{
			delay_clock.restart();
		}
	}

	float TimeHorizontal, TimeVertical;
	TimeHorizontal = 4.0f;
	TimeVertical = 0.5f;

	float TimeElapsed;
	TimeElapsed = animation_clock.getElapsedTime().asSeconds();

	sf::Vector2f NewPos;

	float t1 = TimeElapsed / TimeHorizontal;
	float t2 = TimeElapsed / TimeVertical;

	//float increment = 1.0f / (60 * TimeHorizontal);
	//t1 += increment;

	//583,215
	DesiredPosition = sf::Vector2f(578, 215);

	NewPos.x = PositionObject.x + (DesiredPosition.x - PositionObject.x) * t1;
	NewPos.y = PositionObject.y + (DesiredPosition.y - PositionObject.y) * t2;

	if (!continue_move && t1 <= 1.0f)
	{
		s_icon_continue.setPosition(NewPos.x, s_icon_continue.getPosition().y);
	}
	///*
	else if (BUTTON_STATE == BUTTON_PRESSED && isMouseOverIcon && !continue_move)
	{
		continue_move = 1;
		continue_fits_sound.play();
		music2.setVolume(0);
		animation_clock.restart();
	}
	else if (t2 <= 1.0f && continue_move == true)
	{
		delay_clock.restart();
		s_icon_plate_attach.setTexture(t_icon_plate_light);
		s_icon_continue.setPosition(s_icon_continue.getPosition().x, NewPos.y);
	}
	else if (delay_clock.getElapsedTime().asMilliseconds() >= 1500 && continue_move == true && menu)
	{
		COLOR_OPACITY += 3;
		Layer_Effect.setFillColor(sf::Color(0, 0, 0, (std::int8_t)COLOR_OPACITY));

		if (COLOR_OPACITY == 255)
		{
			animation_clock.restart();
			menu = 0;
		}
	}
	//*/
}

void InscryptionGame::GameLogic()
{
	if (COLOR_OPACITY != 0 && animation_clock.getElapsedTime().asSeconds() >= 1)
	{
		COLOR_OPACITY -= 3;
		Layer_Effect.setFillColor(sf::Color((std::int8_t)0, (std::int8_t)0, (std::int8_t)0, (std::int8_t)COLOR_OPACITY));
		if (COLOR_OPACITY <= 10)
		{
			music2.stop();
			music1.play();
			leshy_mad = 1;
		}
	}
	else if (animation_clock.getElapsedTime().asMilliseconds() >= TEXT_TIME && C_WORD < CHAR_VAR && leshy_mad == true)
	{
		//44 limit by line
		switch (DIALOGUE_STEP)
		{
		case 0: s_text_leshy = "Hello begginer, let me tell you how it works\nhere."; break;
		case 1: s_text_leshy = "In this game every turn you will receive a\nrandom new card..."; break;
		case 2: s_text_leshy = "You can place it whenever you want whereas\nyou have what it costs."; break;
		case 3: s_text_leshy = "There are two types of elixir that you\nwill need to know, Blood costs and Bone Costs."; break;
		case 4: s_text_leshy = "For the blood cost all you need is the\nnumber of cards in the board that\nthe desired card needs to be invoked."; break;
		case 5: s_text_leshy = "While the bone cost cards only need to\nhave enough bones in the counter up there."; break;
		case 6: s_text_leshy = "That is everything you need to know by\nnow... Let's see how you will do."; break;
		case 7: s_text_leshy = "There will be more explanations as the\ngame goes on."; break;
		default: leshy_mad = 0; exit_dialogue_sound.play(); TURN_OWNER = PLAYER_TURN; break;
		}

		CHAR_VAR = static_cast<unsigned short>(s_text_leshy.length() + 1);
		animation_clock.restart();
		s_text_leshy.resize(C_WORD);
		C_WORD++;
		l_text.setString(s_text_leshy);

		if (s_text_leshy.size() >= 45 && s_text_leshy.size() <= 78)
		{
			l_text.setPosition(s_text_box.getPosition().x + (float)30, s_text_box.getPosition().y + (float)20);
		}
		else if (s_text_leshy.size() > 78)
		{
			l_text.setPosition(s_text_box.getPosition().x + (float)30, s_text_box.getPosition().y + (float)8);
		}
		else
		{
			l_text.setPosition(s_text_box.getPosition().x + (float)30, s_text_box.getPosition().y + (float)31);
		}

		if (s_text_leshy.length() % 5)
		{
			blip1.play();
		}
		else if (s_text_leshy.length() % 6)
		{
			blip2.play();
		}
		else if (s_text_leshy.length() % 7)
		{
			blip3.play();
		}
	}
	else if (PLAYER_INPUT == SKIP_INPUT && delay_clock.getElapsedTime().asMilliseconds() >= 300)
	{
		delay_clock.restart();
		C_WORD = 0;
		DIALOGUE_STEP++;
	}
}

void InscryptionGame::ScaleLogic()
{
	if (scale_delay_clock.getElapsedTime().asMilliseconds() >= 400 && SCALE_DAMAGE > 0 && SCALE_DAMAGE < 10)
	{
		if (SCALE_DAMAGE != SCALE_POINTS)
		{
			if (SCALE_DAMAGE < SCALE_POINTS)
			{
				//bigger
				SCALE_DAMAGE++;
				v_scale_text[1].setString("x" + std::to_string(PLAYER_SCALE_POINTS));
				if (SCALE_DAMAGE < 5)
				{
					v_scale_plate[0].setPosition(v_scale_plate[0].getPosition().x, v_scale_plate[0].getPosition().y + (SCALE_DAMAGE - 5));
					v_scale_plate[1].setPosition(v_scale_plate[1].getPosition().x, v_scale_plate[1].getPosition().y - (SCALE_DAMAGE - 5));
				}
				else if (SCALE_DAMAGE > 5)
				{
					v_scale_plate[0].setPosition(v_scale_plate[0].getPosition().x, v_scale_plate[0].getPosition().y + (5 - SCALE_DAMAGE));
					v_scale_plate[1].setPosition(v_scale_plate[1].getPosition().x, v_scale_plate[1].getPosition().y - (5 - SCALE_DAMAGE));
				}
				else
				{
					v_scale_plate[0].setPosition(s_scale3.getPosition().x - s_scale3.getGlobalBounds().width / (float)1.6, s_scale3.getPosition().y - 3);
					v_scale_plate[1].setPosition(s_scale3.getPosition().x + s_scale3.getGlobalBounds().width / (float)1.6, s_scale3.getPosition().y - 3);
				}
			}
			else if (SCALE_DAMAGE > SCALE_POINTS)
			{
				//smaller
				SCALE_DAMAGE--;
				v_scale_text[0].setString("x" + std::to_string(LESHY_SCALE_POINTS));
				if (SCALE_DAMAGE < 5)
				{
					v_scale_plate[0].setPosition(v_scale_plate[0].getPosition().x, v_scale_plate[0].getPosition().y - (SCALE_DAMAGE - 5));
					v_scale_plate[1].setPosition(v_scale_plate[1].getPosition().x, v_scale_plate[1].getPosition().y + (SCALE_DAMAGE - 5));
				}
				else if (SCALE_DAMAGE > 5)
				{
					v_scale_plate[0].setPosition(v_scale_plate[0].getPosition().x, v_scale_plate[0].getPosition().y - (5 - SCALE_DAMAGE));
					v_scale_plate[1].setPosition(v_scale_plate[1].getPosition().x, v_scale_plate[1].getPosition().y + (5 - SCALE_DAMAGE));
				}
				else
				{
					v_scale_plate[0].setPosition(s_scale3.getPosition().x - s_scale3.getGlobalBounds().width / (float)1.6, s_scale3.getPosition().y - 3);
					v_scale_plate[1].setPosition(s_scale3.getPosition().x + s_scale3.getGlobalBounds().width / (float)1.6, s_scale3.getPosition().y - 3);
				}
			}

			for (int i = 0; i <= 1; i++)
			{
				v_scale_text[i].setPosition(v_scale_plate[i].getPosition().x + 2, v_scale_plate[i].getPosition().y + 54);
			}
			s_scale3.setRotation((SCALE_DAMAGE - 5) * SCALE_INCLINATION_CONST);
			s_scale_indicator1.setPosition(s_scale_indicator2.getPosition().x + SCALE_DAMAGE * s_scale_indicator2.getGlobalBounds().width / 10, s_scale_indicator1.getPosition().y);
		}
		scale_delay_clock.restart();
	}
}

void InscryptionGame::GameLoop()
{
	while (window->isOpen())
	{
		if (delta_Time.getElapsedTime().asMilliseconds() >= DELTA_TIME)
		{
			Events();
			if (window->hasFocus())
			{
				delta_Time.restart();
				CursorStates();
				if (menu)
				{
					MenuEvents();
				}
				else
				{
					GameLogic();
					TurnEvents();
					if (!leshy_mad)
					{
						ScaleLogic();
						DrawCard();
						PlayCard();
						CardPerishing();
					}
				}
				DrawGame();
			}
		}
	}
}