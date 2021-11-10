#pragma once

#include "Entity.h"
#include "Lifebar.h"

class Monster : public Entity
{
	public:
		Monster(int dim, sf::Texture texture, sf::Vector2f pos);
		~Monster();

		float getSpeed();
		sf::Vector2f getVelocity();
		sf::Vector2f getPosition();
		sf::Sprite getSprite();
		sf::Vector2f setPositionMoove(sf::Vector2f& posMonster);
		sf::Vector2f Monster::getPositionMoove();

		void setVelocityX(float f);
		void setVelocityY(float f);
		void setSpeed(float f);
		void setHP(int i);

		void normalize(sf::Vector2f& velocity, float speed);
		void update(float dt);
		void drawMonster(sf::RenderWindow& rw);
		
	protected:
		float monsterSpeed = 0.5;
		LifeBar monsterLifeBar;
		sf::Vector2f velocity = { 0,0 };
		sf::Vector2f positionMoove = { 40, 10 };
		sf::Vector2f moovementMonster = { 0 ,0 };
		sf::Vector2f moove1 = { 100 , 150 };
		sf::Vector2f moove2 = { 40 , 10 };

		//sf::Vector2f moove3 = { 400 , 400 };
		//sf::Vector2f moove4 = { 100 , 400 };
};