#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Entity.h"

using namespace sf;
using namespace std;

Entity::Entity(float entityHP, Vector2f pos) : position(pos)
{
	this->entityHP = entityHP;
}

Entity::~Entity()
{
}

int Entity::getEntityHP()
{
	return entityHP;
}


bool Entity::isAlive(int entityHP)
{
	return entityHP > 0;
}







