#include <SFML/Graphics.hpp>
#include <iostream>
#include "Weapon.h"

using namespace sf;

Weapon::Weapon()
{
	textureBaguette.loadFromFile("assets/baguette2.png");
	dmg = 100;
	baguette = Sprite(textureBaguette);
	

	baguette.scale(Vector2f(0.5,0.5));
	baguette.setOrigin(Vector2f(0, 5));
	baguette.setPosition(Vector2f(0, 0));
	
}

Weapon::~Weapon()
{
}

void Weapon::attack()
{
	ratio = 90 / attackSpeed;
	startAngle = ( angle - 45 + 360 ) % 360;
	baguette.setRotation(startAngle);
}
void Weapon::setDmg(int f)
{
	dmg = f;
}

void Weapon::setAngle(int f)
{
	angle = f;
}

void Weapon::update(float dt, bool isAttacking)
{

	if (elapsedTime < 40)
	{
		angle += 4;
		elapsedTime += dt;
		baguette.setRotation(angle);
	}
	else
	{
		elapsedTime = 0;
	}
	/*int rotation = baguette.getRotation();
	int tempAngle = (rotation + int(ratio) + 360) % 360;
	baguette.setRotation(tempAngle);*/
		
	//isAttacking = false;
}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(baguette, states);
}


