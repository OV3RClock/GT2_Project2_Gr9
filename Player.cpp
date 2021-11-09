#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Entity.h"
#include "Player.h"

using namespace sf;
using namespace std;

Player::Player(Vector2f pos) : Entity(200, pos)
{
    texture.loadFromFile("characters.png");
    sprite = Sprite(texture);
    sprite.setTextureRect(IntRect(64, 0, 16, 16));
    sprite.setPosition(position);
    playerLifeBar.setValue(200);
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
void Player::update(float dt)
{
    normalize(velocity, playerSpeed);
    sprite.move(velocity * dt);
    position = sprite.getPosition();
    playerLifeBar.setPosition(position.x, position.y - 6);
}
void Player::drawPlayer(sf::RenderWindow& rw)
{
    rw.draw(sprite);
    rw.draw(playerLifeBar);
}

