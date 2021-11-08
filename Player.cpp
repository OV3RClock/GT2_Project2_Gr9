#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Entity.h"
#include "Player.h"

using namespace sf;
using namespace std;

Player::Player(int scale, Vector2f pos) : Entity(200, pos)
{
    texture.loadFromFile("ghost.png");
	sprite = Sprite(texture);
    sprite.setScale(scale, scale);
    sprite.setPosition(position);
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
    sprite.move(velocity*dt);
}
void Player::drawPlayer(sf::RenderWindow& rw)
{
    rw.draw(sprite);
}

