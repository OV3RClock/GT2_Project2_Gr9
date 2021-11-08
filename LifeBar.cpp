#include "LifeBar.h"

using namespace sf;

LifeBar::LifeBar()
{
	t1.loadFromFile("back.png");
	t2.loadFromFile("fill.png");
	back = Sprite(t1);
	fill = Sprite(t2);
	//back.setScale(scale, scale);
	//fill.setScale(scale, scale);
	maxValue = 200;
	value = 200;
}

LifeBar::~LifeBar()
{
}

void LifeBar::setValue(float f)
{
	value = f;
	float percentage = value / maxValue;
	fill.setTextureRect(IntRect(0, 0, percentage * 15, 3));
}

void LifeBar::draw(RenderTarget& target, RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(back,states);
	target.draw(fill,states);
}