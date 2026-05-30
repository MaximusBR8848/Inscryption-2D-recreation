#include "Board.hpp"
#include "Text.hpp"
#include "Game.hpp"

void Board::initIcons()
{
	//assembling the scale
	spriteScale.setScale(3, 3);
	spriteScale.setPosition(300, 300);
	texture.loadFromFile("assets\\gbc_cardbattle_18.png");
	spriteScale.setTexture(texture);

	/*
	for (int i = 0; i < 5; i++)
	{
		vect_spriteScale.push_back(spriteScale);
	}

	if (!texture.loadFromFile("assets\\gbc_cardbattle_18.png"))
		std::cout << "ERROR::TEXTUREBOARD::SCALE_STEM::FAILED!" << std::endl;

	vect_spriteScale[0].setTexture(texture);

	if (!texture.loadFromFile("assets\\gbc_cardbattle_2.png"))
		std::cout << "ERROR::TEXTUREBOARD::SCALE_BAR::FAILED!" << std::endl;

	vect_spriteScale[1].setTexture(texture);

	if (!texture.loadFromFile("assets\\gbc_cardbattle_1.png"))
		std::cout << "ERROR::TEXTUREBOARD::SCALE_PLATE::FAILED!" << std::endl;

	vect_spriteScale[2].setTexture(texture);

	if (!texture.loadFromFile("assets\\gbc_cardbattle_3.png"))
		std::cout << "ERROR::TEXTUREBOARD::SCALE_POINTER::FAILED!" << std::endl;

	vect_spriteScale[3].setTexture(texture);

	if (!texture.loadFromFile("assets\\gbc_cardbattle_4.png"))
		std::cout << "ERROR::TEXTUREBOARD::SCALE_METER::FAILED!" << std::endl;

	vect_spriteScale[4].setTexture(texture);
	*/
}

void Board::initText()
{

}

void Board::setPosition()
{
	/*
	for (int i = 1; i < vect_spriteScale.size(); i++)
	{
		vect_spriteScale[i].setPosition(vect_spriteScale[i--].getPosition().x, vect_spriteScale[i--].getPosition().y + 30);
	}
	*/
}

Board::Board()
{
	this->initIcons();
	this->initText();
	this->setPosition();
	this->Update();
}

Board::~Board()
{

}

void Board::Update()
{

}

void Board::Render(sf::RenderTarget* target)
{
	target->draw(this->spriteScale);
	std::cout << "Rendering" << std::endl;
}