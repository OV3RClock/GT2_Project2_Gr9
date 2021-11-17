#include <SFML/Graphics.hpp>
#include "EntitiesMap.h"

using namespace sf;
EntitiesMap::EntitiesMap(Texture& texture)
{
	Texture monsterTexture;
	monsterTexture.loadFromFile("assets/characters.png");
	for (size_t i = 0; i < 5; i++)
	{
		addMonster(creatMonster(monsterTexture));
	}
}

EntitiesMap::~EntitiesMap()
{
}

void EntitiesMap::addMonster(Monster monster)
{
	monsterList.push_back(monster);
}

Monster EntitiesMap::creatMonster(Texture texture)
{
	Monster *monster = new Monster(texture);
	return *monster;
}

void EntitiesMap::updateMonsters(float dt, Player &player, bool &isTouched)
{
	for (size_t i = 0; i < monsterList.size(); i++)
	{
		monsterList[i].update(dt, player, isTouched);
	}
}

void EntitiesMap::drawMonsters(sf::RenderWindow& rw)
{
	for (size_t i = 0; i < monsterList.size(); i++)
	{
		monsterList[i].drawMonster(rw);
	}
}


