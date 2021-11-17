#include <SFML/Graphics.hpp>
#include "EntitiesMap.h"
#include "Monster.h"

using namespace sf;
EntitiesMap::EntitiesMap()
{
	Texture monsterTexture;
	monsterTexture.loadFromFile("assets/characters.png");

	Monster *monster1 = new Monster(monsterTexture);
	addMonster(monster1);
}

EntitiesMap::~EntitiesMap()
{
}

std::vector<Monster*> EntitiesMap::getMonsterList()
{
	return monsterList;
}

void EntitiesMap::addMonster(Monster* monster)
{
	monsterList.push_back(monster);
}

/*Monster EntitiesMap::creatMonster(Texture& texture)
{
	Monster *monster = new Monster(texture);
	return *monster;
}*/

void EntitiesMap::updateMonsters(float dt, Player &player, bool &isTouched)
{
	for (int i = 0; i < monsterList.size(); i++)
	{
		monsterList[i]->update(dt, player, isTouched);
	}
}

void EntitiesMap::drawMonsters(sf::RenderWindow& rw)
{
	for (int i = 0; i < monsterList.size(); i++)
	{
		monsterList[i]->drawMonster(rw);
	}
}


