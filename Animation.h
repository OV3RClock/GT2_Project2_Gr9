#pragma once

#include <SFML/Graphics.hpp>

class Animation
{
	public:
		Animation();
		~Animation();

		sf::Sprite getPlayerTile(int i);
		sf::Sprite getSkeletonTile(int i);

		void loadPlayerTiles(int dim);
		void loadSkeletonTiles(int dim);

	protected:
		std::vector<sf::Sprite> playerTiles;
		std::vector<sf::Sprite> skeletonTiles;
		sf::Texture characterTexture;
};


