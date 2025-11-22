#include "Board.hpp"
#include <iostream>

void Board::initIcons()
{
	//assembling the scale
	spriteScale.setScale(3, 3);

	for (int i = 0; i < 6; i++)
	{
		//vector_spriteScale.push_back(spriteScale);
	}

	if (!this->texture->loadFromFile("assets\\gbc_cardbattle_18.png"))
		std::cout << "ERROR::TEXTUREBOARD::SCALE_STEM::FAILED!" << std::endl;

	if (!this->texture->loadFromFile("assets\\gbc_cardbattle_2.png"))
		std::cout << "ERROR::TEXTUREBOARD::SCALE_BAR::FAILED!" << std::endl;

	if (!this->texture->loadFromFile("assets\\gbc_cardbattle_1.png"))
		std::cout << "ERROR::TEXTUREBOARD::SCALE_PLATE::FAILED!" << std::endl;

	if (!this->texture->loadFromFile("assets\\gbc_cardbattle_3.png"))
		std::cout << "ERROR::TEXTUREBOARD::SCALE_POINTER::FAILED!" << std::endl;

	if (!this->texture->loadFromFile("assets\\gbc_cardbattle_4.png"))
		std::cout << "ERROR::TEXTUREBOARD::SCALE_METER::FAILED!" << std::endl;

}

void Board::initText()
{

}

Board::Board()
{
	this->initIcons();
	this->initText();
}

Board::~Board()
{
	vector_spriteScale.clear();
}

void Board::Update()
{

}

void Board::Render(sf::RenderTarget* target)
{
	for (auto& spriteScale : vector_spriteScale)
	{ 
		target->draw(this->spriteScale);
	}
}