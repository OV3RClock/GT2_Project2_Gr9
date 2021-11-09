#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
	public:
		Animation();
		~Animation();

		std::vector<sf::Sprite> getPlayerTiles();
		std::vector<sf::Sprite> getMonsterTiles();

		void loadPlayerTiles(int dim);
		void loadMonsterTiles(int dim);

	protected:
		std::vector<sf::Sprite> playerTiles;
		std::vector<sf::Sprite> monsterTiles;
		sf::Texture characterTexture;
};


