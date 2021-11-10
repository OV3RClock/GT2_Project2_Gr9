#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Entity.h"
#include "Monster.h"

using namespace sf;
using namespace std;

Monster::Monster(const int dim, Texture& texture, Vector2f pos) : Entity(200,pos)
{
    sprite = Sprite(texture);
    sprite.setTextureRect(IntRect(10 * dim, 0, dim, dim));
    sprite.setPosition(position);
    
    Vector2f point0 = { 100 , 150 };
    Vector2f point1 = { 40 , 10 };
    Vector2f point2 = { 200 , 50 };
    path.push_back(point0);
    path.push_back(point1);
    path.push_back(point2);
    target = point1;
}
Monster::~Monster()
{
}

float Monster::getSpeed()
{
    return monsterSpeed;
}
sf::Vector2f Monster::getVelocity()
{
    return velocity;
}
sf::Vector2f Monster::getPosition()
{
    return position;
}
sf::Sprite& Monster::getSprite()
{
    return sprite;
}
sf::Vector2f Monster::getTarget()
{
    return target;
}

sf::Vector2f Monster::moveToTarget()
{
    if (isOnTarget(0)) { target = path[1]; };
    if (isOnTarget(1)) { target = path[2]; };
    if (isOnTarget(2)) { target = path[0]; };

    movementMonster.x = target.x - sprite.getPosition().x;
    movementMonster.y = target.y - sprite.getPosition().y;

    return movementMonster;
}
bool Monster::isOnTarget(int i)
{
    int range = 1;
    return ((sprite.getPosition().x <= (path[i].x + range))
        && (sprite.getPosition().x >= (path[i].x - range))
        && (sprite.getPosition().y <= (path[i].y + range))
        && (sprite.getPosition().y >= (path[i].y - range)));
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
void Monster::setHP(int i)
{
    entityHP = i;
    monsterLifeBar.setValue(entityHP);
}

void Monster::normalize(Vector2f& vect)
{
    float norme = sqrt((vect.x * vect.x) + (vect.y * vect.y));
    if (norme != 0)
    {
        vect.x = ((vect.x) / norme) * monsterSpeed;
        vect.y = ((vect.y) / norme) * monsterSpeed;
    }
}
void Monster::update(float dt)
{
    moveToTarget();
    normalize(movementMonster);
    sprite.move(movementMonster*dt);
    position = sprite.getPosition();
}
void Monster::drawMonster(RenderWindow& rw)
{
    rw.draw(sprite);
}


