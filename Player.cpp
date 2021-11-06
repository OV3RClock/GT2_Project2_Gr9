#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Entity.h"
#include "Player.h"

using namespace sf;
using namespace std;

Player::Player(int scale) : Entity(200)
{
    texture.loadFromFile("ghost.png");
	sprite = Sprite(texture);
    sprite.setScale(scale, scale);
}
Player::~Player()
{
}

float Player::getVelocityX()
{
    return velocity.x;
}
float Player::getVelocityY()
{
    return velocity.y;
}
float Player::getSpeed()
{
    return playerSpeed;
}
sf::Sprite Player::getSprite()
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

void Player::normalize(Vector2f &velocity, float speed) 
{
    float norme = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
    if (norme != 0)
    {
        velocity.x = ((velocity.x) / norme) * playerSpeed;
        velocity.y = ((velocity.y) / norme) * playerSpeed;
    }
}
void Player::drawPlayer(sf::RenderWindow& rw)
{
    normalize(velocity, playerSpeed);
    sprite.move(velocity.x, velocity.y);
    rw.draw(sprite);
}

