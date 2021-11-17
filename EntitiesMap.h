#include <SFML/Graphics.hpp>
#include "Monster.h"
#include "Player.h"

class EntitiesMap
{
	public :
		EntitiesMap();
		~EntitiesMap();

		std::vector<Monster*> getMonsterList();

		void addMonster(Monster* monster);
		//Monster creatMonster(sf::Texture& texture);
		void updateMonsters(float dt, Player& player, bool& isTouched);
		void drawMonsters(sf::RenderWindow& rw);
		
	protected :
		std::vector<Monster*> monsterList;
		std::vector<sf::Vertex> deplacementMonster;
};
