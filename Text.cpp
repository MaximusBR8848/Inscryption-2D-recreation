#include "Text.hpp"
#include <iostream>

void Text::initFont()
{
	if (!font.loadFromFile("assets\\Marksman.ttf"))
		std::cout << "ERROR::FONT::INITFONT::Failed" << std::endl;
}

void Text::initText()
{
	DarkGray.r = 10;
	DarkGray.g = 10;
	DarkGray.b = 10;
	DarkGray.a = 220;

	this->text.setFont(font);
	this->text.setCharacterSize(50);
	this->text.setFillColor(DarkGray);
	this->text.setScale(3,3);
}

Text::Text()
{
	this->initFont();
	this->initText();
}

Text::~Text()
{

}

void Text::Update()
{
	
}

void Text::Move(float X, float Y)
{
	
}

void Text::Render(sf::RenderTarget& target)
{
	target.draw(this->text);
}