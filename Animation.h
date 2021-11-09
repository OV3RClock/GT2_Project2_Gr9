#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
	public:
		Animation();
		~Animation();

		std::vector<sf::Sprite> getPlayerTiles();
		std::vector<sf::Sprite> getMonsterTiles();

		void loadPlayerTiles();
		void loadMonsterTiles();

	protected:
		std::vector<sf::Sprite> playerTiles;
		std::vector<sf::Sprite> monsterTiles;
		sf::Texture characterTexture;
};


