#pragma once

#include <SFML/Graphics.hpp>

class LifeBar : public sf::Drawable, public sf::Transformable
{
	public:
		LifeBar();
		LifeBar(float hp);
		~LifeBar();

		void setValue(float f);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	protected:
		sf::Sprite back;
		sf::Sprite fill;
		sf::Texture t1;
		sf::Texture t2;
		float maxValue = 0;
		float value = 0;
};