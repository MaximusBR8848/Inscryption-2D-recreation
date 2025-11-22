#ifndef CARD_H
#define CARD_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <string>
#include <random>
#include <sstream>

class Card
{
private:

	std::random_device Random_Card_Var;

	sf::Font font;

	sf::Text cardAttack, cardHP;

	sf::Sprite cardSprite, creatureSprite, sigilSprite1, sigilSprite2, sprite;
	sf::Texture texture_Common, texture_Rare, texture_Creature, texture_Sigil1, texture_Sigil2;

	unsigned short SizeX, SizeY;
	float movementSpeed;

	std::string Rarity, Name, Sigils, FirstSigil, SecondSigil;

	short attack, hp, CARD_ID, bloodCost, boneCost;

	sf::Vector2f Position;

	enum CardID
	{
		Squirrel, Wolf, Coyote, Bloodhound, Kingfisher, Magpie, Raven, BlackGoat, ElkFawn, Elk, MooseBuck, WolfCub, Alpha, MantisGod, RingWorm,
		Geck, Ouroboros, BullFrog, DireWolfPup, DireWolf, Stoat, Adder, Cat, MoleMan, Mole, Urayuli, Skunk, Warren, FieldMice, RatKing, Grizzly,
		Opossum, Rabbit, UndeadCat, Starvation
	};

	void initData();
	void initTexture();
	void initText();
	void initSprite();

public:

	Card();
	Card(sf::Texture * texture_creature, sf::Texture * texture_card, float pos_y, float pos_x, float dir_x, float dir_y, float movement_speed);
	virtual ~Card();

	const sf::Vector2f& getPos() const;
	const sf::FloatRect getBounds() const;
	void Manipulate(const float dirX, const float dirY);
	void Update();
	void Render(sf::RenderTarget* target);
};

#endif