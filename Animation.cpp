#include "Animation.h"

using namespace sf;

Animation::Animation()
{
	characterTexture.loadFromFile("assets/characters.png");
}

Animation::~Animation()
{
}

std::vector<sf::Sprite> Animation::getPlayerTiles()
{
	return playerTiles;
}
std::vector<sf::Sprite> Animation::getMonsterTiles()
{
	return monsterTiles;
}

void Animation::loadPlayerTiles(int dim)
{
	for (int j = 0; j < 4*dim; j += dim)
	{
		for (int i = 3*dim; i < 6*dim; i += dim)
		{
			Sprite sprite;
			sprite.setTextureRect(IntRect(i, 0, dim, dim));
			playerTiles.push_back(sprite);
			if (i >= 6*dim)
			{
				i = 3*dim;
				j += dim;
			}
		}
	}
}
void Animation::loadMonsterTiles(int dim)
{
}

