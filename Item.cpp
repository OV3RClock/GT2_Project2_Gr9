#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Item.h"
#include "Player.h"

using namespace sf;
using namespace std;

Item::Item()
{
	texture.loadFromFile("assets/potion.png");
	sprite = Sprite(texture);
}
Item::Item(float healAmount) : healAmount(healAmount)
{
	Texture texture;
	texture.loadFromFile("assets/potion.png");
	sprite = Sprite(texture);
}
Item::~Item()
{
}

float Item::getHealAmount()
{
	return healAmount;
}

sf::Sprite Item::getSprite()
{
	return sprite;
}

void Item::setHealAmount(float f)
{
	healAmount = f;
}

void Item::setPosition(sf::Vector2f v)
{
	sprite.setPosition(v);
}

void Item::drawItem(sf::RenderWindow& rw)
{
	rw.draw(sprite);
}
