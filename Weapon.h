#pragma once

#include <SFML/Graphics.hpp>
class Weapon : public sf::Drawable, public sf::Transformable
{
	public:
		Weapon();
		~Weapon();

		void setDmg(int f);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	protected:
		sf::Sprite baguette;
		sf::Texture textureBaguette;
		int dmg = 0;
};

