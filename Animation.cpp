#include "Animation.h"

using namespace sf;


Animation::Animation() : holdTime(0)
{
}
Animation::Animation(int x, int y, int width, int height, int nFrames, float holdTime, Texture texture) : holdTime(holdTime)
{
	this->texture = texture;
	for (int i = 0; i < nFrames; i++)
	{
		frames.push_back(IntRect(x, y, width, height));
		x += width;
	}
}
Animation::~Animation()
{
}

void Animation::advance()
{
	if (++currentFrame >= int(frames.size()))
	{
		currentFrame = 0;
	}
}
void Animation::applyToSprite(sf::Sprite& s)
{
	s.setTexture(texture);
	s.setTextureRect(frames[currentFrame]);
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

