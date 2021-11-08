#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Entity.h"
#include "Monster.h"

using namespace sf;
using namespace std;

Monster::Monster(int scale) : Entity(200)
{
    texture.loadFromFile("ghost.png");
    sprite = Sprite(texture);
    sprite.setScale(scale, scale);
}
Monster::~Monster()
{
}

float Monster::getSpeed()
{
    return monsterSpeed;
}
float Monster::getVelocityX()
{
    return velocity.x;
}
float Monster::getVelocityY()
{
    return velocity.y;
}
sf::Vector2f Monster::getVelocity()
{
    return velocity;
}
float Monster::getPositionX()
{
    return sprite.getPosition().x;
}
float Monster::getPositionY()
{
    return sprite.getPosition().y;

}
sf::Sprite Monster::getSprite()
{
    return sprite;
}

void Monster::setVelocityX(float f)
{
    velocity.x = f;
}
void Monster::setVelocityY(float f)
{
    velocity.y = f;
}
void Monster::setSpeed(float f)
{
    monsterSpeed = f;
}

void Monster::normalize(Vector2f& velocity, float s)
{
    float norme = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
    if (norme != 0)
    {
        velocity.x = ((velocity.x) / norme) * s;
        velocity.y = ((velocity.y) / norme) * s;
    }
}
void Monster::drawMonster(sf::RenderWindow& rw)
{
    normalize(velocity, monsterSpeed);
    sprite.move(velocity.x, velocity.y);
    rw.draw(sprite);
}
