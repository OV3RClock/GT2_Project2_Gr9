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

void Weapon::setDmg(int f)
{
	dmg = f;
}

void Weapon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(baguette, states);
}


