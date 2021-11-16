#include <SFML/Graphics.hpp>
#include <iostream>

#include "LifeBar.h"

using namespace sf;

LifeBar::LifeBar()
{
}
LifeBar::LifeBar(float hp)
{
	t1.loadFromFile("assets/back.png");
	t2.loadFromFile("assets/fill.png");
	back = Sprite(t1);
	fill = Sprite(t2);
	fill.setPosition(Vector2f(0.5,0.5));
	maxValue = hp;
	value = hp;
}

LifeBar::~LifeBar()
{
}

void LifeBar::setValue(float f)
{
	value = f;
	float percentage = value / maxValue;
	fill.setScale(percentage, 1);
}

void LifeBar::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(back,states);
	target.draw(fill,states);
}