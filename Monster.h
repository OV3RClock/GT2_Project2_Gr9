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
		sf::Vector2f setGetPositionMoove();

		void setVelocityX(float f);
		void setVelocityY(float f);
		void setSpeed(float f);

		void normalize(sf::Vector2f& velocity, float speed);
		void update(float dt);
		void drawMonster(sf::RenderWindow& rw);
		void mooveMonster(sf::Vector2f& posMoove, sf::Vector2f posMonster);

	protected:
		float monsterSpeed = 0.5;
		sf::Vector2f velocity = { 0,0 };
		sf::Vector2f positionMoove = { 0,0 };
};