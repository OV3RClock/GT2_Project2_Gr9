#pragma once

#include <SFML/Audio.hpp>

#include "Entity.h"
#include "Lifebar.h"
#include "Player.h"
#include "Animation.h"

class Monster : public Entity
{
	public:
		Monster(sf::Texture& texture);
		~Monster();

		float random_float(float min, float max);
		float getSpeed();
		sf::Vector2f getVelocity();
		sf::Vector2f getPosition();
		sf::Sprite getSprite();
		sf::Vector2f Monster::getTarget();
		
		void setSpeed(float f);
		void setHP(int i);

		bool isPlayerInRange(sf::Vector2f& player);
		bool isOnTarget(int i);
		bool isHit(Player& player, bool isAttacking);
		bool monsterHitPlayer(Player& player);
		void setDirection();

		void moveToTarget(sf::Vector2f& player, float dt);
		void takeDmg(float dmg, Player player);

		void normalize(sf::Vector2f& velocity);
		void update(float dt, Player& player, bool isAttacking, sf::Sound& sound);
		void drawMonster(sf::RenderWindow& rw);
		
	protected:
		float monsterSpeed = 30;
		int dim = 16;
		float hp = 150;
		int numberTarget = 0;
		float elapsedTime = 0;
		float elapsedHit = 0;
		float elapsedPause = 0;
		LifeBar monsterLifeBar;
		sf::Vector2f pos = { 300 , 420 };
		sf::Vector2f zoneMin ;
		sf::Vector2f zoneMax ;
		sf::Vector2f velocity;
		sf::Vector2f target;
		std::vector<sf::Vector2f> path;
		enum class AnimationIndex
		{
			Up,
			Left,
			Down,
			Right,
			Count
		};
		Animation animations[int(AnimationIndex::Count)];
		AnimationIndex curAnimation = AnimationIndex::Down;
};