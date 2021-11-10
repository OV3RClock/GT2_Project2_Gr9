#include "Animation.h"

using namespace sf;


Animation::Animation() : holdTime(0)
{
}

Animation::Animation(int x, int y, int width, int height, int nFrames, float holdTime, Texture texture) : holdTime(holdTime)
{
	frames.reserve(nFrames);
	this->texture = texture;
	for (int i = 0; i < nFrames; i++)
	{
		frames.emplace_back(sf::Vector2i{ x,y }, sf::Vector2i{ width,height });
		x += width;
	}
}

void Animation::advance()
{
	if (++iFrame >= int(frames.size()))
	{
		iFrame = 0;
	}
}

void Animation::applyToSprite(sf::Sprite & s)
{
	s.setTexture(texture);
	s.setTextureRect(frames[iFrame]);
}

void Animation::update(float dt)
{
	time += dt;
	while (time >= holdTime)
	{
		time -= holdTime;
		advance();
	}
}

