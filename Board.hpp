#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>
#include <array>

class Board
{
private:

	sf::Text textCardDescripton, textScale, textDeckCounter, textBoneCounter;
	sf::Texture texture;
	sf::Sprite spriteCardDescripton, spriteDeckCounter, spriteBoneCounter, spriteScale;

	std::vector<sf::Sprite> vect_spriteScale;

	void initIcons();
	void initText();
	void setPosition();

public:

	Board();
	virtual ~Board();

	void Update();
	void Render(sf::RenderTarget* target);
};

#endif