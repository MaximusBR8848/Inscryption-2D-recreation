#ifndef TEXT_H

#define TEXT_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class Text
{
private:

	sf::Font font;
	sf::Text text;

	sf::Color DarkGray;

	void initFont();
	void initText();

public:

	Text();
	virtual ~Text();

	void Move(float X, float Y);
	void Update();
	void Render(sf::RenderTarget& target);

};

#endif