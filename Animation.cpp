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

void Animation::loadPlayerTiles()
{
	for (int j = 0; j < 64; j += 16)
	{
		for (int i = 48; i < 96; i += 16)
		{
			Sprite sprite;
			sprite.setTextureRect(IntRect(i, 0, 16, 16));
			playerTiles.push_back(sprite);
			if (i >= 96)
			{
				i = 48;
				j += 16;
			}
		}
	}
}
void Animation::loadMonsterTiles()
{
}

