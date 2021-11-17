#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Entity.h"
#include "Player.h"
#include "Animation.h"
#include "Weapon.h"
#include "LifeBar.h"

using namespace sf;
using namespace std;

Player::Player(int dim, float hp, Vector2f& pos, float dmgWeapon) : Entity(hp, pos), baguette(Weapon(dmgWeapon)), playerLifeBar(LifeBar(hp))
{
	Texture playerTexture;
	Texture mountTexture;
	playerTexture.loadFromFile("assets/samurai 48x48.png");
	mountTexture.loadFromFile("assets/samurai mount 72x72.png");
	
	animations[(int)AnimationIndex::Up] = Animation(0 * 48, 3 * 48, 48, 48, 3, 0.1, playerTexture);
	animations[(int)AnimationIndex::Left] = Animation(0 * 48, 1 * 48, 48, 48, 3, 0.1, playerTexture);
	animations[(int)AnimationIndex::Down] = Animation(0 * 48, 0 * 48, 48, 48, 3, 0.1, playerTexture);
	animations[(int)AnimationIndex::Right] = Animation(0 * 48, 2 * 48, 48, 48, 3, 0.1, playerTexture);
	animations[(int)AnimationIndex::idleUp] = Animation(1 * 48, 3 * 48, 48, 48, 1, 10, playerTexture);
	animations[(int)AnimationIndex::idleLeft] = Animation(1 * 48, 1 * 48, 48, 48, 1, 10, playerTexture);
	animations[(int)AnimationIndex::idleDown] = Animation(1 * 48, 0 * 48, 48, 48, 1, 10, playerTexture);
	animations[(int)AnimationIndex::idleRight] = Animation(1 * 48, 2 * 48, 48, 48, 1, 10, playerTexture);

	animations[(int)AnimationIndex::mountUp] = Animation(0 * 72, 3 * 72, 72, 72, 3, 0.1, mountTexture);
	animations[(int)AnimationIndex::mountLeft] = Animation(0 * 72, 1 * 72, 72, 72, 3, 0.1, mountTexture);
	animations[(int)AnimationIndex::mountDown] = Animation(0 * 72, 0 * 72, 72, 72, 3, 0.1, mountTexture);
	animations[(int)AnimationIndex::mountRight] = Animation(0 * 72, 2 * 72, 72, 72, 3, 0.1, mountTexture);
	animations[(int)AnimationIndex::mountIdleUp] = Animation(1 * 72, 3 * 72, 72, 72, 1, 10, mountTexture);
	animations[(int)AnimationIndex::mountIdleLeft] = Animation(1 * 72, 1 * 72, 72, 72, 1, 10, mountTexture);
	animations[(int)AnimationIndex::mountIdleDown] = Animation(1 * 72, 0 * 72, 72, 72, 1, 10, mountTexture);
	animations[(int)AnimationIndex::mountIdleRight] = Animation(1 * 72, 2 * 72, 72, 72, 1, 10, mountTexture);

	sprite.setPosition(pos);
}
Player::~Player()
{
}

float Player::getSpeed()
{
    return playerSpeed;
}
sf::Sprite Player::getSprite()
{
	return sprite;
}
Vector2f Player::getPosition()
{
	return position;
}
Vector2f Player::getVelocity()
{
    return velocity;
}

Weapon Player::getWeapon()
{
	return baguette;
}

void Player::setSpeed(float f)
{
	playerSpeed = f;
}
void Player::setDirection(sf::Vector2f& dir)
{
	curAnimation = AnimationIndex::idleDown;
	if (dir.x > 0.0f)
	{
		curAnimation = AnimationIndex::Right;
	}
	else if (dir.x < 0.0f)
	{
		curAnimation = AnimationIndex::Left;
	}
	else if (dir.y < 0.0f)
	{
		curAnimation = AnimationIndex::Up;
	}
	else if (dir.y > 0.0f)
	{
		curAnimation = AnimationIndex::Down;
	}
	else
	{
		if (velocity.x > 0.0f)
		{
			curAnimation = AnimationIndex::idleRight;
		}
		else if (velocity.x < 0.0f)
		{
			curAnimation = AnimationIndex::idleLeft;
		}
		else if (velocity.y < 0.0f)
		{
			curAnimation = AnimationIndex::idleUp;
		}
		else if (velocity.y > 0.0f)
		{
			curAnimation = AnimationIndex::idleDown;
		}
	}
	velocity = dir * playerSpeed;
}
void Player::setDirection(sf::Vector2f& dir, float poussee, float masse, float angle, float friction, float dt)
{
	curAnimation = AnimationIndex::mountIdleDown;
	if (abs(dir.y) > abs(dir.x))
	{
		if (dir.y < 0.0f)
		{
			curAnimation = AnimationIndex::mountUp;
		}
		else if (dir.y > 0.0f)
		{
			curAnimation = AnimationIndex::mountDown;
		}
	}
	else if(abs(dir.y) < abs(dir.x))
	{
		if (dir.x > 0.0f)
		{
			curAnimation = AnimationIndex::mountRight;
		}
		else if (dir.x < 0.0f)
		{
			curAnimation = AnimationIndex::mountLeft;
		}
	} 
	else if (abs(velocity.y) > abs(velocity.x))
	{
		if (velocity.y < 0.0f)
		{
			curAnimation = AnimationIndex::mountIdleUp;
		}
		else if (velocity.y > 0.0f)
		{
			curAnimation = AnimationIndex::mountIdleDown;
		}
	}
	else
	{
		if (velocity.x > 0.0f)
		{
			curAnimation = AnimationIndex::mountIdleRight;
		}
		else if (velocity.x < 0.0f)
		{
			curAnimation = AnimationIndex::mountIdleLeft;
		}
	}

	float accx = (1 / masse) * poussee * dir.x;
	float accy = (1 / masse) * poussee * dir.y;

	velocity.x = velocity.x + (accx - (friction / (masse) * velocity.x)) * dt;
	velocity.y = velocity.y + (accy - (friction / (masse) * velocity.y)) * dt;
}
void Player::setVelocityX(float f)
{
	velocity.x = f;
}
void Player::setVelocityY(float f)
{
	velocity.y = f;
}
void Player::setHP(int i)
{
    entityHP = i;
    playerLifeBar.setValue(entityHP);
}

void Player::takeDmg(int i)
{
    entityHP -= i;
    
	if (entityHP >= 0 )
	{
		playerLifeBar.setValue(entityHP);
	}
}

void Player::normalize(Vector2f& vect)
{
    float norme = sqrt((vect.x * vect.x) + (vect.y * vect.y));
    if (norme != 0)
    {
        vect.x = ((vect.x) / norme) * playerSpeed;
        vect.y = ((vect.y) / norme) * playerSpeed;
    }
}
void Player::update(float dt, bool isSprinting, bool& isAttacking, bool isOnMount)
{
	if(!isOnMount){ normalize(velocity); }
    sprite.move(velocity * dt);
	if (isOnMount) { sprite.setScale((1.f / 4.5f), (1.f / 4.5f)); }
	else { sprite.setScale((1.f / 3.f), (1.f / 3.f)); }
	position = sprite.getPosition();
	baguette.update(dt, isAttacking);

    if (isSprinting&&!isOnMount) 
    {
		animations[int(curAnimation)].update(dt*2);
        animations[int(curAnimation)].applyToSprite(sprite);
    }
    else
    {
        animations[int(curAnimation)].update(dt);
        animations[int(curAnimation)].applyToSprite(sprite);
    }
    playerLifeBar.setPosition(position.x, position.y - 6);
	baguette.setPosition(sprite.getPosition() + Vector2f{8,8});

	switch (curAnimation)
	{
		case Player::AnimationIndex::Up:
			baguette.setStartAngle(180);
			break;
		case Player::AnimationIndex::Left:
			baguette.setStartAngle(90);
			break;
		case Player::AnimationIndex::Down:
			baguette.setStartAngle(0);
			break;
		case Player::AnimationIndex::Right:
			baguette.setStartAngle(270);
			break;
	}
}
void Player::drawPlayer(sf::RenderWindow& rw, bool isAttacking)
{
	if (isAttacking)
	{
		rw.draw(baguette);
	}
	rw.draw(sprite);
    rw.draw(playerLifeBar);
}

