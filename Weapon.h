#pragma once

#include <SFML/Graphics.hpp>

class Weapon : public sf::Drawable
{
	public:
		Weapon(int dmg);
		~Weapon();

		sf::Sprite getSprite();
		float getCurrentAngle();
		float getMaxAngle();
		float getElapsedTime();

		void setDmg(int i);
		void setStartAngle(float f);
		void setPosition(sf::Vector2f pos);

		void update(float dt, bool& isAttacking);

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	protected:
		sf::Sprite sprite;
		sf::Texture texture;
		int dmg = 0;
		float startAngle = 0;
		float currentMovementAngle = 0;
		float maxAngle = 180;
		float elapsedTime = 0;
};

