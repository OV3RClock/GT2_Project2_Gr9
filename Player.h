#pragma once

#include "Entity.h"

class Player : public Entity 
{
	public:
		Player(int scale);
		~Player();

		float getSpeed();
		float getVelocityX();
		float getVelocityY();
		float getPositionX();
		float getPositionY();
		sf::Sprite getSprite();

		void setVelocityX(float f);
		void setVelocityY(float f);
		void setSpeed(float f);

		void normalize(sf::Vector2f &velocity, float speed);
		void drawPlayer(sf::RenderWindow &rw);

	protected:
		float playerSpeed = 0.5;
		sf::Vector2f velocity = { 0,0 };
};