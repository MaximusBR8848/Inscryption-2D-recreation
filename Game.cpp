#include "Game.hpp"
#include "Card.hpp"
#include "Text.hpp"

#include <iostream>

sf::RenderWindow* window = nullptr;

//Private Functions
void Game::initWindow()
{
	WIDTH = 1280;
	HEIGHT = 720;

	DELTA_TIME = 16;

	window = new sf::RenderWindow(sf::VideoMode(WIDTH,HEIGHT), "Inscryption Lost Version", sf::Style::Titlebar | sf::Style::Close);

	window->setMouseCursorVisible(false);
}

void Game::initTextures()
{
	this->textures["CARD"] = new sf::Texture();

	this->textureCursor.loadFromFile("assets\\cursor_icons.png");
	this->spriteCursor.setTexture(textureCursor);
	this->spriteCursor.setScale(2, 2);
	this->spriteCursor.setTextureRect(sf::IntRect(0, 56, 10, 25));
}

void Game::initText()
{

}

void Game::initBoard()
{
	if (!this->textureBoard.loadFromFile("assets\\gbc_board_nature.jpg"))
		std::cout << "ERROR::BACKGROUNDBOARD::INITTEXTURE::Failed" << std::endl;
	this->spriteBoard.setTexture(textureBoard);
	this->spriteBoard.setScale(3, 3);
	this->spriteBoard.setPosition(-125, -140);

	if (!this->texturePlacementPrev.loadFromFile("assets\\gbc_cardslots_0.png"))
		std::cout << "ERROR::BACKGROUNDBOARD::INITTEXTURE::Failed" << std::endl;
	if (!this->texturePlacement.loadFromFile("assets\\gbc_cardslots_nature.png"))
		std::cout << "ERROR::BACKGROUNDBOARD::INITTEXTURE::Failed" << std::endl;
	this->spritePlacementPrev.setTexture(texturePlacementPrev);
	this->spritePlacement.setTexture(texturePlacement);
	this->spritePlacementPrev.setScale(3, 3);
	this->spritePlacement.setScale(3, 3);

	for (int i = 0; i < 4; i++)
		this->vector_spritePlacementPrev.push_back(spritePlacementPrev);

	this->vector_spritePlacementPrev[0].setPosition(spriteBoard.getPosition().x + 500, spriteBoard.getPosition().y + 170);
	for (int i = 1; i < 4; i++)
		this->vector_spritePlacementPrev[i].setPosition(this->vector_spritePlacementPrev[0].getPosition().x + 133 * i, this->vector_spritePlacementPrev[0].getPosition().y);

	for (int i = 0; i < 8; i++)
		this->vector_spritePlacement.push_back(spritePlacement);

	this->vector_spritePlacement[0].setPosition(this->vector_spritePlacementPrev[0].getPosition().x, spriteBoard.getPosition().y + 266);
	for (int i = 1; i < 4; i++)
		this->vector_spritePlacement[i].setPosition(this->vector_spritePlacement[0].getPosition().x + 133 * i, this->vector_spritePlacement[0].getPosition().y);

	for (int i = 4; i < 8; i++)
	{
		this->vector_spritePlacement[i].setRotation(180);
		this->vector_spritePlacement[i].setOrigin(42,56);
		this->vector_spritePlacement[i].setPosition(vector_spritePlacement[0].getPosition().x + 133 * (i - 4), spriteBoard.getPosition().y + 460);
	}
}

//Constructor
Game::Game()
{
	this->initWindow();
	this->initTextures();
	this->initText();
	this->initBoard();
}

//Destructor
Game::~Game()
{
	delete window;

	//textures
	for (auto &i : this->textures)
	{
		delete i.second;
	}

	//cards
	for (auto *i : this->cards)
	{
		delete i;
	}

	//text

}

void Game::Run()
{
	while (window->isOpen())
	{
		this->Update();
		this->Render();
	}
}

void Game::RecieveInputs()
{
	if (sf::Event::KeyReleased && sf::Event::KeyPressed && window->hasFocus())
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && cards.size() < 20)
		{
			this->cards.push_back(new Card());
		}
		else if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && cards.size() > 0)
		{
			this->cards.pop_back();
		}
	}
}

void Game::UpdatePollEvents()
{
	sf::Event e;
	while (window->pollEvent(e))
	{
		if (e.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			window->close();
	}
}

void Game::UpdateCards()
{
	
}

void Game::UpdateUI()
{
	this->spriteCursor.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window)));
}

void Game::Update()
{
	if (timeElapsed.getElapsedTime().asMilliseconds() >= DELTA_TIME)
	{
		this->RecieveInputs();
		this->UpdatePollEvents();
		this->UpdateCards();
		this->UpdateUI();

		timeElapsed.restart();

		//informative outputs

	}
}

void Game::RenderBoard()
{
	//Board Background
	window->draw(spriteBoard);

	//Draw placements
	for (auto& spritePlacement : vector_spritePlacement)
	{
		window->draw(spritePlacement);
	}
	for (auto& spritePlacementPrev : vector_spritePlacementPrev)
	{
		window->draw(spritePlacementPrev);
	}
}

void Game::Render()
{
	window->clear();

	//Draw Background
	this->RenderBoard();

	//Draw other things
	for (auto* card : this->cards)
	{
		card->Render(window);
	}
	window->draw(spriteCursor);

	window->display();
}