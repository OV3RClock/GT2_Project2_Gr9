#pragma once

#include "Entity.h"

class Monster : public Entity
{
	public:
		Monster(sf::Vector2f pos);
		~Monster();

		float getSpeed();
		sf::Vector2f getVelocity();
		sf::Vector2f getPosition();
		sf::Sprite getSprite();
		sf::Vector2f setGetPositionMoove(sf::Vector2f posMonster);

		void setVelocityX(float f);
		void setVelocityY(float f);
		void setSpeed(float f);

		void normalize(sf::Vector2f& velocity, float speed);
		void update(float dt);
		void drawMonster(sf::RenderWindow& rw);
		void mooveMonster(sf::Vector2f& posMoove, sf::Vector2f posMonster);
		void stopMonster(sf::Vector2f& posMoove, sf::Vector2f posMonster);
	protected:
		float monsterSpeed = 0.5;
		sf::Vector2f velocity = { 0,0 };
		sf::Vector2f positionMoove = { 0, 0 };
		sf::Vector2f moove1 = { 100 , 100 };
		sf::Vector2f moove2 = { 400 , 100 };
		//sf::Vector2f moove3 = { 400 , 400 };
		//sf::Vector2f moove4 = { 100 , 400 };
};