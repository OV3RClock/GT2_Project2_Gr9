#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Entity.h"

using namespace sf;
using namespace std;

Entity::Entity(int entityHP)
{
}

Entity::~Entity()
{
}

int Entity::getEntityHP()
{
	return entityHP;
}

void Entity::setEntityHP(int i)
{
	entityHP = i;
}


