#include "Animation.h"

using namespace sf;

Animation::Animation()
{
	characterTexture.loadFromFile("assets/characters.png");
}
Animation::~Animation()
{
}

Sprite Animation::getPlayerTile(int i)
{
	return playerTiles[i];
}
Sprite Animation::getSkeletonTile(int i)
{
	return skeletonTiles[i];
}

void Animation::loadPlayerTiles(int dim)
{
	for (int j = 0; j < 4*dim; j += dim)
	{
		for (int i = 3*dim; i < 6*dim; i += dim)
		{
			Sprite sprite;
			sprite.setTexture(characterTexture);
			sprite.setTextureRect(IntRect(i, j, dim, dim));
			playerTiles.push_back(sprite);
			if (i >= 6*dim)
			{
				i = 3*dim;
				j += dim;
			}
		}
	}
}
void Animation::loadSkeletonTiles(int dim)
{
	{
		for (int j = 0; j < 4 * dim; j += dim)
		{
			for (int i = 9 * dim; i < 12 * dim; i += dim)
			{
				Sprite sprite;
				sprite.setTexture(characterTexture);
				sprite.setTextureRect(IntRect(i, j, dim, dim));
				skeletonTiles.push_back(sprite);
				if (i >= 12 * dim)
				{
					i = 9 * dim;
					j += dim;
				}
			}
		}
	}
}

