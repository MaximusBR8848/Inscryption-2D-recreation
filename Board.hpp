#ifndef BOARD_H
#define BOARD_H

#include <SFML/Graphics.hpp>

class Board
{
private:

	sf::Text textCardDescripton, textScale, textDeckCounter, textBoneCounter;
	sf::Sprite spriteCardDescripton, spriteScale, spriteDeckCounter, spriteBoneCounter;

	std::vector<sf::Sprite> vector_spriteScale;

	sf::Texture* texture;

	void initIcons();
	void initText();

public:

	Board();
	virtual ~Board();

	void Update();
	void Render(sf::RenderTarget* target);

};

#endif
