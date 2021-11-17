#include <SFML/Graphics.hpp>
#include "EntitiesMap.h"

using namespace sf;
EntitiesMap::EntitiesMap()
{
	Texture monsterTexture;
	monsterTexture.loadFromFile("assets/characters.png");
}

EntitiesMap::~EntitiesMap()
{
}

void EntitiesMap::addMonster(Monster monster)
{
	monsterList.push_back(monster);
}

void EntitiesMap::creatMonster(Monster monster, Texture texture)
{
	Monster *monster = new Monster(texture);
}
