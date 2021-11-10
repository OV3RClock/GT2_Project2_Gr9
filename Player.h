#pragma once

#include "Entity.h"
#include "Lifebar.h"
#include "Animation.h"

class Player : public Entity 
{
	public:
		Player(int dim, sf::Texture texture, sf::Vector2f& pos);
		~Player();

		sf::Vector2f Player::getPosition();
		sf::Vector2f getVelocity();

		void setSpeed(float f);
		void setDirection(sf::Vector2f& dir);
		void setVelocityX(float f);
		void setVelocityY(float f);

		void normalize(sf::Vector2f& velocity);

		void update(float dt, bool isSprinting);

		void drawPlayer(sf::RenderWindow& rw);

	private:
		enum class AnimationIndex
		{
			Up,
			Left,
			Down,
			Right,
			idleUp,
			idleLeft,
			idleDown,
			idleRight,
			Count
		};
		float playerSpeed;
		sf::Vector2f velocity = { 0,0 };
		Animation animations[int(AnimationIndex::Count)];
		AnimationIndex curAnimation = AnimationIndex::idleDown;
};
	/*
	public:
		Player(int dim, sf::Texture texture, sf::Vector2f pos);
		~Player();

		float getSpeed();
		sf::Vector2f getVelocity();
		sf::Vector2f getPosition();
		sf::Sprite getSprite();

		void setVelocityX(float f);
		void setVelocityY(float f);
		void setSpeed(float f);
		void setHP(int i);
		void setDirection();

		void takeDmg(int i);

		void normalize(sf::Vector2f &velocity, float speed);
		void update(float dt, Animation a);
		void drawPlayer(sf::RenderWindow &rw);

	protected:
		float playerSpeed = 0.5;
		sf::Vector2f velocity = { 0,0 };
		LifeBar playerLifeBar;
		Animation animations[int(AnimationIndex::Count)];
	};
	*/
