#pragma once

#include "Entity.h"
#include "Lifebar.h"

class Player : public Entity 
{
	public:
		Player(sf::Vector2f pos);
		~Player();

		float getSpeed();
		sf::Vector2f getVelocity();
		sf::Vector2f getPosition();
		sf::Sprite getSprite();

		void setVelocityX(float f);
		void setVelocityY(float f);
		void setSpeed(float f);
		void setHP(int i);

		void takeDmg(int i);

		void normalize(sf::Vector2f &velocity, float speed);
		void update(float dt);
		void drawPlayer(sf::RenderWindow &rw);

	protected:
		float playerSpeed = 0.5;
		sf::Vector2f velocity = { 0,0 };
		LifeBar playerLifeBar;
};