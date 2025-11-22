#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <string>
#include <memory>
#include <random>

#define PRESS_INPUTS sf::Mouse::isButtonPressed(sf::Mouse::Left)
#define SKIP_INPUTS sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Mouse::isButtonPressed(sf::Mouse::Left)
#define PASS_INPUTS sf::Keyboard::isKeyPressed(sf::Keyboard::Space)

class InscryptionGame
{
private:

	std::shared_ptr <sf::RenderWindow> window;

	sf::Font font;
	sf::Text l_text, card_text, scale_text, deck_text, bone_text;

	sf::Texture t_board, t_card_common, t_card_rare, t_card_terrain, t_card_placement_l, t_card_placement_l_prev, t_card_placement_p,
	t_card_placement_p_selected, t_text_box, t_face_leshy, t_menu_background, t_card_cost,
	t_icon_continue, t_icon_plate_light, t_icon_plate_midlight, t_icon_plate_dark, t_scale1, t_scale2, t_scale3, t_scale4, t_scale_indicator1, t_scale_indicator2,
	t_hammer, t_bell, t_blood_empty, t_blood_full, t_card_description1, t_card_description2, t_batteries, t_mox_simbols, 
	//CREATURES SPRITES
	t_card_creature_squirrel, t_card_creature_bloodhound, t_card_creature_wolf, t_card_creature_coyote, t_card_creature_kingfisher, t_card_creature_magpie, t_card_creature_raven,
	t_card_creature_blackgoat, t_card_creature_elkfaw, t_card_creature_elk, t_card_creature_moosebuck, t_card_creature_wolfcub, t_card_creature_alpha,
	t_card_creature_mantisgod, t_card_creature_ringworm, t_card_creature_geck, t_card_creature_bullfrog, t_card_creature_dire_wolf,
	t_card_creature_dire_wolf_pup, t_card_creature_stoat, t_card_creature_adder, t_card_creature_skunk, t_card_creature_moleman, t_card_creature_mole,
	t_card_creature_starvation, t_card_creature_ouroboros, t_card_creature_urayuli, t_card_creature_cat, t_card_creature_undeadcat,
	t_card_creature_warren, t_card_creature_fieldmice, t_card_creature_ratking, t_card_creature_grizzly, t_card_creature_opossum, t_card_creature_rabbit,
	//SIGILS
	t_sigil_MightyLeap, t_sigil_Airborne, t_sigil_Sprinter, t_sigil_Fledgling, t_sigil_Hoarder, t_sigil_Waterborne, t_sigil_Hefty, t_sigil_Guardian,
	t_sigil_WorthySacrifice, t_sigil_TrifurcatedStrike, t_sigil_BoneDigger, t_sigil_DoubleStrike, t_sigil_Leader, t_sigil_repulsive, t_sigil_stinky,
	t_sigil_burrower, t_sigil_Touchofdeath, t_sigil_Immortal, t_sigil_Unkillable, t_sigil_RabbitHole, t_sigil_BoneKing, t_sigil_Fecundity,
	//END SIGILS
	t_deck_icon, t_bone_cost, t_bone_total, t_blood_cost, t_sacrifice_simbol, t_cursors_map, t_null;

	sf::Sprite s_card, s_board, s_card_placement_l, s_card_placement_l_prev, s_card_placement_p, s_card_placement_p_selected, s_text_box, s_face_leshy,
	s_cursor, s_menu_background,
	s_icon_continue, s_icon_plate_attach, s_scale1, s_scale2, s_scale3, s_scale4, s_scale_indicator1, s_scale_indicator2,
	s_hammer, s_bell, s_blood_icon, s_card_description1, s_card_description2, s_batteries, s_mox_simbols,
	s_card_cost,
	//CREATURES SPRITES
	s_card_creature_squirrel, s_card_creature_bloodhound, s_card_creature_wolf, s_card_creature_coyote, s_card_creature_kingfisher, s_card_creature_magpie, s_card_creature_raven,
	s_card_creature_blackgoat, s_card_creature_elkfaw, s_card_creature_elk, s_card_creature_moosebuck, s_card_creature_wolfcub, s_card_creature_alpha,
	s_card_creature_mantisgod, s_card_creature_ringworm, s_card_creature_geck, s_card_creature_bullfrog, s_card_creature_dire_wolf, 
	s_card_creature_dire_wolf_pup, s_card_creature_stoat, s_card_creature_adder, s_card_creature_skunk, s_card_creature_moleman, s_card_creature_mole,
	s_card_creature_starvation, s_card_creature_ouroboros, s_card_creature_urayuli, s_card_creature_cat, s_card_creature_undeadcat,
	s_card_creature_warren, s_card_creature_fieldmice, s_card_creature_ratking, s_card_creature_grizzly, s_card_creature_opossum, s_card_creature_rabbit,
	//SIGILS
	s_sigil_MightyLeap, s_sigil_Airborne, s_sigil_Sprinter, s_sigil_Fledgling, s_sigil_Hoarder, s_sigil_Waterborne, s_sigil_Hefty, s_sigil_Guardian,
	s_sigil_WorthySacrifice, s_sigil_TrifurcatedStrike, s_sigil_BoneDigger, s_sigil_DoubleStrike, s_sigil_Leader, s_sigil_repulsive, s_sigil_stinky,
	s_sigil_burrower, s_sigil_Touchofdeath, s_sigil_Immortal, s_sigil_Unkillable, s_sigil_RabbitHole, s_sigil_BoneKing, s_sigil_Fecundity,
	//END SIGILS
	s_deck_icon, s_bone_cost, s_bone_total, s_blood_cost, s_sacrifice_simbol, s_null;

	sf::Clock animation_clock, delay_clock, bell_clock, scale_delay_clock, sacrifice_wait, delta_Time, card_Perishing, cursor_clock;
	sf::Mouse mouse;
	sf::Music music1, music2;
	sf::SoundBuffer blip_buffer1, blip_buffer2, blip_buffer3, card_attack1_buffer, exit_dialog_buffer, continue_fits_buffer;
	sf::Sound blip1, blip2, blip3, card_attack1_sound, exit_dialogue_sound, continue_fits_sound;
	sf::RectangleShape Background_Frame, Layer_Effect;
	sf::Vector2f Object_Moving_Coords, Object_Coords;
	sf::Color DarkRed, DarkGray;
	sf::Shader ScreenShader;

	std::vector <sf::Text> v_text_card_hp, v_text_card_attk, v_scale_text;
	std::vector <sf::Sprite> v_card, l_card_placement, l_card_placement_prev, p_card_placement, p_card_placement_selected, v_creature_card,
	v_scale_plate, v_bone_cost, v_blood_cost, v_sacrifice_simbol, v_card_sigil_1, v_card_sigil_2, v_card_cost, v_sacrifices_blood, v_batteries,
	v_mox_simbols;
	std::string s_text_leshy, Window_Name;
	std::vector <short> blood_cost, bone_cost, card_id, card_hp, card_attk, card_opacity, sigil_type_1, sigil_type_2, player_placement, v_direction;
	std::vector <bool> v_on_board, v_ocupied, v_sacrificed;

	std::random_device Random_Card_Var;

	bool fullscreen, menu, leshy_mad, sacrificing, continue_move, positionating, on_board, ocupied, sacrificed, smashing;
	short HP, ATTK, SCALE_POINTS, SCALE_DAMAGE, CARD_SELECTED, SIGIL_1, SIGIL_2, PLAYER_PLACEMENT;
	unsigned short WIDTH, HEIGHT, C_WORD, TEXT_TIME, DIALOGUE_STEP, CHAR_VAR, BUTTON_STATE, BELL_STATE, TURN_OWNER, TURN_NUMBER, DECK_SIZE, CARD_NUMBER,
	BLOOD_COST, BONE_COST, BONE_COUNTER, CARD_STEP, CARDS_ON_BOARD, SACRIFICES, RARITY, XANDY_MULTIPLIER, LESHY_SCALE_POINTS,
	PLAYER_SCALE_POINTS, CURSOR_STATE, PLAYER_INPUT, BATTERY_CHARGE;
	float VELOCITY, COLOR_OPACITY, CARD_OPACITY, SCALE_INCLINATION_CONST, DELTA_TIME;

	enum buttonStates
	{
		BUTTON_IDLE, BUTTON_HOVER, BUTTON_PRESSED
	};
	enum Inputs
	{
		IDDLE, SKIP_INPUT, PASS_INPUT
	};
	enum CursorStates
	{
		NORMAL, SACRIFICING, SACRIFICING_PRESSED, POSITIONING, POSITIONING_PRESSED, SMASHING, SMASHING_PRESSED
	};
	enum bellStates
	{
		BELL_NORMAL, BELL_UNLIT, BELL_SELECTED, BELL_USED
	};
	enum gameTurn
	{
		LESHY_TURN, PLAYER_TURN, EVENT_TURN
	};
	enum rarity
	{
		COMMON, RARE, TERRAIN
	};
	
	enum cardId
	{
		Squirrel, Wolf, Coyote, Bloodhound, Kingfisher, Magpie, Raven, BlackGoat, ElkFawn, Elk, MooseBuck, WolfCub, Alpha, MantisGod, RingWorm,
		Geck, Ouroboros, BullFrog, DireWolfPup, DireWolf, Stoat, Adder, Cat, MoleMan, Mole,
		Urayuli, Skunk, Warren, FieldMice, RatKing, Grizzly, Opossum, Rabbit, UndeadCat, Starvation
	};

	enum SigilType
	{
		None, MightyLeap, Airborne, Sprinter, Fledgling, Hoarder, Waterborne, Hefty, Guardian, WorthySacrifice,
		TrifurcatedStrike, BoneDigger, DoubleStrike, Leader, Repulsive, Stinky, Burrower, TouchofDeath, Immortal, Unkillable,
		RabbitHole, Fecundity, BoneKing
	};

protected:

	void DrawGame();
	void CreateCard();
	void DrawCard();
	void DrawFromDeck();
	void PlayCard();
	void TurnEvents();
	void Events();
	void CursorStates();
	void MenuEvents();
	void ScaleLogic();
	void GameLogic();
	void Create_Window();
	void CardPerishing();
	void CardAttackPlayer();
	void CardAttackLeshy();
	void AnimationHandler();

public:

	void GameLoop();
	InscryptionGame();
};