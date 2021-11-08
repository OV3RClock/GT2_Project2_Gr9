#pragma once
#include "Entity.h"

class Monster : public Entity
{
	public:
		Monster(int scale);
		~Monster();

		float getSpeed();
		float getVelocityX();
		float getVelocityY();
		sf::Vector2f getVelocity();
		float getPositionX();
		float getPositionY();
		sf::Sprite getSprite();

		void setVelocityX(float f);
		void setVelocityY(float f);
		void setSpeed(float f);

		void normalize(sf::Vector2f& velocity, float speed);
		void drawMonster(sf::RenderWindow& rw);

	protected:
		float monsterSpeed = 0.5;
		sf::Vector2f velocity = { 0,0 };
};