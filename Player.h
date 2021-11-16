#pragma once

#include "Entity.h"
#include "Lifebar.h"
#include "Animation.h"
#include "Weapon.h"

class Player : public Entity 
{
	public:
		Player(int dim, sf::Texture& texture, sf::Vector2f& pos, Weapon w);
		~Player();

		float getSpeed();
		sf::Sprite getSprite();
		sf::Vector2f Player::getPosition();
		sf::Vector2f getVelocity();
		Weapon getWeapon();

		void setSpeed(float f);
		void setDirection(sf::Vector2f& dir);
		void setVelocityX(float f);
		void setVelocityY(float f);
		void setHP(int i);

		void takeDmg(int i);

		void normalize(sf::Vector2f& velocity);
		void update(float dt, bool isSprinting, bool& isAttacking );
		void drawPlayer(sf::RenderWindow& rw, bool isAttacking);

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
		Weapon baguette;
		LifeBar playerLifeBar;
		Animation animations[int(AnimationIndex::Count)];
		AnimationIndex curAnimation = AnimationIndex::idleDown;
};
