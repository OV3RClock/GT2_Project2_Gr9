#pragma once

#include "Entity.h"
#include "Lifebar.h"

class Monster : public Entity
{
	public:
		Monster(int dim, sf::Texture& texture, sf::Vector2f pos);
		~Monster();

		float getSpeed();
		sf::Vector2f getVelocity();
		sf::Vector2f getPosition();
		sf::Sprite& getSprite();
		
		sf::Vector2f Monster::getTarget();

		void setVelocityX(float f);
		void setVelocityY(float f);
		void setSpeed(float f);
		void setHP(int i);

		void moveToTarget();
		bool isOnTarget(int i);

		void normalize(sf::Vector2f& velocity);
		void update(float dt);
		void drawMonster(sf::RenderWindow& rw);
		
	protected:
		float monsterSpeed = 0.5;
		LifeBar monsterLifeBar;
		sf::Vector2f velocity;
		sf::Vector2f target;
		int index = 0;
		sf::Vector2f movementMonster;
		std::vector<sf::Vector2f> path;
};