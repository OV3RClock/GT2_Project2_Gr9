#include <SFML/Graphics.hpp>
#include <iostream>
#include "Weapon.h"

using namespace sf;
using namespace std;

Weapon::Weapon(int dmg) : dmg(dmg)
{
	texture.loadFromFile("assets/baguette2.png");
	sprite = Sprite(texture);
	
	sprite.scale(Vector2f( 0.5,0.5 ));
	sprite.setOrigin(Vector2f( 0,5 ));
	sprite.setPosition(Vector2f( 0,0 ));
}
Weapon::~Weapon()
{
}

Sprite Weapon::getSprite()
{
	return sprite;
}
float Weapon::getCurrentAngle()
{
	return currentMovementAngle;
}
float Weapon::getMaxAngle()
{
	return maxAngle;
}
float Weapon::getElapsedTime()
{
	return elapsedTime;
}

void Weapon::setDmg(int i)
{
	dmg = i;
}
void Weapon::setStartAngle(float f)
{
	startAngle = f;
}
void Weapon::setPosition(sf::Vector2f pos)
{
	this->sprite.setPosition(pos);
}

void Weapon::update(float dt, bool& isAttacking)
{
	if (isAttacking)
	{
		if (elapsedTime < 0.05)
		{
			elapsedTime = 0;
			if (currentMovementAngle < maxAngle)
			{
				currentMovementAngle += 5;
				sprite.rotate(5);
			}
			else
			{
				isAttacking = false;
			}
		}
		else
		{
			elapsedTime += dt;
		}
	}
	else
	{
		currentMovementAngle = 0;
		sprite.setRotation(startAngle);
	}
}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
}


