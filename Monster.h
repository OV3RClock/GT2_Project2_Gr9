#pragma once

#include "Entity.h"

class Monster : public Entity
{
	public:
		Monster(int scale, sf::Vector2f pos);
		~Monster();

		float getSpeed();
		sf::Vector2f getVelocity();
		sf::Vector2f getPosition();
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