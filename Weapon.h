#pragma once

#include <SFML/Graphics.hpp>
class Weapon : public sf::Drawable, public sf::Transformable
{
	public:
		Weapon();
		~Weapon();

		void attack();

		void setDmg(int f);
		void setAngle(int f);

		void update(float dt, bool isAttacking);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	protected:
		sf::Sprite baguette;
		sf::Texture textureBaguette;
		int dmg = 0;
		int attackSpeed = 60;
		int angle;
		int startAngle;
		float elapsedTime = 0;
		float ratio;

};

