#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Entity.h"
#include "Player.h"
#include "Animation.h"

using namespace sf;
using namespace std;

Player::Player(int dim, Texture texture, sf::Vector2f& pos) : Entity(200, pos)
{
	animations[(int)AnimationIndex::Up] = Animation(3 * dim, 3 * dim, dim, dim, 3, 0.1, texture);
	animations[(int)AnimationIndex::Left] = Animation(3 * dim, 1 * dim, dim, dim, 3, 0.1, texture);
	animations[(int)AnimationIndex::Down] = Animation(3 * dim, 0 * dim, dim, dim, 3, 0.1, texture);
	animations[(int)AnimationIndex::Right] = Animation(3 * dim, 2 * dim, dim, dim, 3, 0.1, texture);
	animations[(int)AnimationIndex::idleUp] = Animation(4 * dim, 3 * dim, dim, dim, 1, 10, texture);
	animations[(int)AnimationIndex::idleLeft] = Animation(4 * dim, 1 * dim, dim, dim, 1, 10, texture);
	animations[(int)AnimationIndex::idleDown] = Animation(4 * dim, 0 * dim, dim, dim, 1, 10, texture);
	animations[(int)AnimationIndex::idleRight] = Animation(4 * dim, 2 * dim, dim, dim, 1, 10, texture);
}

Player::~Player()
{
}

Vector2f Player::getPosition()
{
	return position;
}
Vector2f Player::getVelocity()
{
    return velocity;
}

void Player::setSpeed(float f)
{
	playerSpeed = f;
}
void Player::setDirection(sf::Vector2f& dir)
{
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
void Player::setVelocityX(float f)
{
	velocity.x = f;
}
void Player::setVelocityY(float f)
{
	velocity.y = f;
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

void Player::update(float dt, bool isSprinting)
{
    position = sprite.getPosition();
    normalize(velocity);
    sprite.move(velocity * dt);
    if (isSprinting) 
    {
        animations[int(curAnimation)].update(dt*2);
        animations[int(curAnimation)].applyToSprite(sprite);
    }
    else
    {
        animations[int(curAnimation)].update(dt);
        animations[int(curAnimation)].applyToSprite(sprite);
    }
}

void Player::drawPlayer(sf::RenderWindow& rw)
{
	rw.draw(sprite);
}

/*
Player::Player(int dim, Texture texture, Vector2f pos) : Entity(200, pos)
{
    sprite = Sprite(texture);
    sprite.setPosition(position);
    setHP(200);
}
Player::~Player()
{
}

float Player::getSpeed()
{
    return playerSpeed;
}
Vector2f Player::getVelocity()
{
    return velocity;
}
Vector2f Player::getPosition()
{
    return position;
}
Sprite Player::getSprite()
{
    return sprite;
}

void Player::setVelocityX(float f)
{
    velocity.x = f;
}
void Player::setVelocityY(float f)
{
    velocity.y = f;
}
void Player::setSpeed(float f)
{
	playerSpeed = f;
}
void Player::setHP(int i)
{
    entityHP = i;
    playerLifeBar.setValue(entityHP);
}

void Player::takeDmg(int i)
{
    entityHP -= i;
    playerLifeBar.setValue(entityHP);
}

void Player::normalize(Vector2f &velocity, float s) 
{
    float norme = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
    if (norme != 0)
    {
        velocity.x = ((velocity.x) / norme) * s;
        velocity.y = ((velocity.y) / norme) * s;
    }
}
void Player::update(float dt, Animation a)
{
    normalize(velocity, playerSpeed);
    if (velocity.y < 0) 
    { 
        Sprite tmpSprite = a.getPlayerTile(10); 
        tmpSprite.setPosition(position);
        sprite = tmpSprite;
    };
    if (velocity.x < 0) 
    { 
        Sprite tmpSprite = a.getPlayerTile(4);
        tmpSprite.setPosition(position);
        sprite = tmpSprite;
    };
    if (velocity.y > 0) 
    { 
        Sprite tmpSprite = a.getPlayerTile(1);
        tmpSprite.setPosition(position);
        sprite = tmpSprite;
    };
    if (velocity.x > 0) 
    { 
        Sprite tmpSprite = a.getPlayerTile(7);
        tmpSprite.setPosition(position);
        sprite = tmpSprite;
    };
    sprite.move(velocity * dt);
    position = sprite.getPosition();
    playerLifeBar.setPosition(position.x, position.y - 6);
}
void Player::drawPlayer(sf::RenderWindow& rw)
{
    rw.draw(sprite);
    rw.draw(playerLifeBar);
}
*/

