#include "Card.hpp"
#include "Game.hpp"
#include "Text.hpp"

#include <iostream>
#include <cctype>
#include <algorithm>

void Card::initData()
{
	std::uniform_int_distribution<int> RandomCard(0, 14);
	CARD_ID = RandomCard(Random_Card_Var);

	//to do: list of card stats
	switch (CARD_ID)
	{
	case Squirrel:

		attack = 0;
		hp = 1;
		Name = "Squirrel";
		Sigils = "None,None";
		Rarity = "Common";

		break;

	case Wolf:

		attack = 3;
		hp = 2;
		bloodCost = 2;
		Name = "Wolf";
		Sigils = "None,None";
		Rarity = "Common";

		break;
	case Coyote:

		attack = 2;
		hp = 1;
		boneCost = 2;
		Name = "Coyote";
		Sigils = "None,None";
		Rarity = "Common";

		break;
	case Bloodhound:

		attack = 2;
		hp = 3;
		Name = "Bloodhound";
		Sigils = "GuardDog,None";
		Rarity = "Common";

		break;
	case Kingfisher:

		attack = 1;
		hp = 1;
		Name = "Kingfisher";
		Sigils = "Flying,Submerge";
		Rarity = "Common";

		break;
	case Magpie:

		attack = 1;
		hp = 1;
		Name = "Magpie";
		Sigils = "Flying,Tutor";
		Rarity = "Common";

		break;
	case Raven:

		attack = 2;
		hp = 3;
		Name = "Raven";
		Sigils = "Flying,None";
		Rarity = "Common";

		break;
	case BlackGoat:

		attack = 0;
		hp = 1;
		Name = "BlackGoat";
		Sigils = "TripleBlood,None";
		Rarity = "Common";

		break;
	case Elk:

		attack = 2;
		hp = 4;
		Name = "Elk";
		Sigils = "Strafe,None";
		Rarity = "Common";

		break;
	case ElkFawn:

		attack = 1;
		hp = 1;
		Name = "ElkFawn";
		Sigils = "Strafe,Evolve";
		Rarity = "Common";

		break;
	case MooseBuck:

		attack = 3;
		hp = 7;
		Name = "MooseBuck";
		Sigils = "StrafePush,None";
		Rarity = "Common";

		break;
	case WolfCub:

		attack = 1;
		hp = 1;
		Name = "WolfCub";
		Sigils = "Evolve,None";
		Rarity = "Common";

		break;
	case Alpha:

		attack = 1;
		hp = 2;
		Name = "Alpha";
		Sigils = "BuffNeighbours,None";
		Rarity = "Common";

		break;
	case MantisGod:

		attack = 1;
		hp = 1;
		bloodCost = 1;
		Name = "MantisGod";
		Sigils = "TriStrike,None";
		Rarity = "Rare";
		break;
	default:

		attack = 0;
		hp = 1;
		bloodCost = 1;
		Name = "RingWorm";
		Sigils = "None,None";
		Rarity = "Common";
		break;
	}

	std::transform(Name.begin(), Name.end(), Name.begin(), ::tolower);
	texture_Creature.loadFromFile("assets\\pixelportrait_" + Name + ".png");

	std::stringstream ss(Sigils);
	std::getline(ss, FirstSigil, ',');

	std::transform(FirstSigil.begin(), FirstSigil.end(), FirstSigil.begin(), ::tolower);
	texture_Sigil1.loadFromFile("assets\\pixelability_" + FirstSigil + ".png");

	std::getline(ss, SecondSigil, ',');

	std::transform(SecondSigil.begin(), SecondSigil.end(), SecondSigil.begin(), ::tolower);
	texture_Sigil2.loadFromFile("assets\\pixelability_" + SecondSigil + ".png");
}

void Card::initTexture()
{
	if (!this->texture_Common.loadFromFile("assets\\pixel_card_empty.png"))
		std::cout << "ERROR::CARDCOMMON::INITTEXTURE::Failed" << std::endl;
	if (!this->texture_Rare.loadFromFile("assets\\pixel_card_empty_rare.png"))
		std::cout << "ERROR::CARDRARE::INITTEXTURE::Failed" << std::endl;;
	if (!this->font.loadFromFile("assets\\Marksman.ttf"))
		std::cout << "ERROR::FONT::INITFONT::Failed" << std::endl;
}

void Card::initSprite()
{
	//linking textures
	if (Rarity == "Common")
		this->cardSprite.setTexture(this->texture_Common);
	else
		this->cardSprite.setTexture(this->texture_Rare);

	this->creatureSprite.setTexture(this->texture_Creature);

	this->sigilSprite1.setTexture(this->texture_Sigil1);
	this->sigilSprite2.setTexture(this->texture_Sigil2);

	//setting scale
	this->creatureSprite.setScale(3, 3);
	this->cardSprite.setScale(3, 3);

	this->sigilSprite1.setScale(3, 3);
	this->sigilSprite2.setScale(3, 3);

	//defining stats text
	this->cardAttack.setFont(this->font);
	this->cardHP.setFont(this->font);

	this->cardAttack.setCharacterSize(50);
	this->cardHP.setCharacterSize(50);

	this->cardAttack.setFillColor(sf::Color::Black);
	this->cardHP.setFillColor(sf::Color::Black);

	this->cardAttack.setString(std::to_string(this->attack));
	this->cardHP.setString(std::to_string(this->hp));

	//positioning card provisory
	sf::Mouse mouse;
	this->cardSprite.setPosition(std::int16_t(mouse.getPosition(*window).x), std::int16_t(mouse.getPosition(*window).y));
}


Card::Card()
{
	this->movementSpeed = 0.0f;

	this->initData();
	this->initTexture();
	this->initSprite();
	this->Update();
}

Card::~Card()
{
	
}

Card::Card(sf::Texture * texture_creature, sf::Texture * texture_card, float pos_y, float pos_x, float dir_x, float dir_y, float movement_speed)
{
	CARD_ID = Squirrel;

	boneCost = 0;
	bloodCost = 0;

	attack = 0;
	hp = 1;

	SizeX = 3;
	SizeY = 3;

	this->cardSprite.setTexture(*texture_card);
	this->creatureSprite.setTexture(*texture_creature);

	pos_x = 200;
	pos_y = 100;

	this->cardSprite.setPosition(pos_x,pos_y);

	this->movementSpeed = movement_speed;
}

const sf::Vector2f& Card::getPos() const
{
	return this->sprite.getPosition();
}

const sf::FloatRect Card::getBounds() const
{
	return this->cardSprite.getGlobalBounds();
}

void Card::Manipulate(const float dirX, const float dirY)
{
	this->cardSprite.move(this->movementSpeed * dirX, this->movementSpeed * dirY);
}

void Card::Update()
{
	creatureSprite.setPosition(cardSprite.getPosition().x + 3, cardSprite.getPosition().y + 3);
	cardAttack.setPosition(cardSprite.getPosition().x + 7, cardSprite.getPosition().y + 111);
	cardHP.setPosition(cardSprite.getPosition().x + 102, cardSprite.getPosition().y + 111);

	if (this->texture_Sigil2.getSize().x > 10)
		this->sigilSprite1.setPosition(cardSprite.getPosition().x + 12, cardSprite.getPosition().y + 93);
	else
		this->sigilSprite1.setPosition(cardSprite.getPosition().x + 39, cardSprite.getPosition().y + 93);

	this->sigilSprite2.setPosition(this->sigilSprite1.getPosition().x + 51, this->sigilSprite1.getPosition().y);

}

void Card::Render(sf::RenderTarget* target)
{
	target->draw(this->cardSprite);
	target->draw(this->creatureSprite);
	target->draw(this->cardAttack);
	target->draw(this->cardHP);
	target->draw(this->sigilSprite1);
	target->draw(this->sigilSprite2);
}