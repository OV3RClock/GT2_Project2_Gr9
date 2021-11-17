#include <SFML/Graphics.hpp>
#include "Monster.h"

class EntitiesMap
{
	public :
		EntitiesMap();
		~EntitiesMap();

		void addMonster(Monster monster);
		void creatMonster(Monster monster, Texture texture);
		

	protected :
		std::vector<Monster> monsterList;
		std::vector<sf::Vertex> deplacementMonster;
};
