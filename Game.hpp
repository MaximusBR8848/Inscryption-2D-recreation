#ifndef GAME_H

#define GAME_H

#include "Card.hpp"
#include "Text.hpp"
#include "Board.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <map>
#include <string>
#include <memory>

enum class GameState {

	GAME_MENU,
	GAME_MAP,
	GAME_BOARD
};

extern sf::RenderWindow* window;

class Game {

private:

	//Window properties
	short WIDTH, HEIGHT;
	float DELTA_TIME;
	sf::Mouse mouse;

	//Global Tick Timer
	sf::Clock timeElapsed;

	//texture inicialization
	std::map<std::string, sf::Texture*> textures;

	//card properties
	std::vector<Card*> cards;
	std::string Name;

	//audio properties
	sf::SoundBuffer bufferMusic;

	//Board & UI
	sf::Texture textureBoard, texturePlacement, texturePlacementPrev, textureCursor;
	sf::Sprite spriteBoard, spritePlacement, spritePlacementPrev, spriteCursor;
	std::vector<sf::Sprite> vector_spritePlacement, vector_spritePlacementPrev;

	void initWindow();
	void initTextures();
	void initText();
	void initBoard();

public:

	Game();
	virtual ~Game();

	void Run();

	void RecieveInputs();
	void UpdatePollEvents();
	void UpdateCards();
	void UpdateUI();
	void Update();
	void RenderBoard();
	void Render();
};

#endif