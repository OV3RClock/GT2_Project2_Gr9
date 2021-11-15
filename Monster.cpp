#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Entity.h"
#include "Monster.h"

using namespace sf;
using namespace std;

Monster::Monster(const int dim, Texture& texture, Vector2f pos) : Entity(150,pos)
{
    sprite = Sprite(texture);
    sprite.setTextureRect(IntRect(10 * dim, 0, dim, dim));
    sprite.setPosition(pos);
    
    Vector2f point0 = { 300 , 420 };
    Vector2f point1 = { 530 , 360 };
    Vector2f point2 = { 440, 480 };
    path.push_back(point0);
    path.push_back(point1);
    path.push_back(point2);
    target = point0;
}
Monster::~Monster()
{
}

float Monster::getSpeed()
{
    return monsterSpeed;
}
Vector2f Monster::getVelocity()
{
    return velocity;
}
Vector2f Monster::getPosition()
{
    return position;
}
Sprite Monster::getSprite()
{
    return sprite;
}
Vector2f Monster::getTarget()
{
    return target;
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



bool Monster::isPlayerInRange(Vector2f& player)
{
    return sqrt((player.x - sprite.getPosition().x) * (player.x - sprite.getPosition().x)
        + (player.y - sprite.getPosition().y) * (player.y - sprite.getPosition().y)) <= 50;
}
bool Monster::isOnTarget(int i)
{
    float range = 0.5;
    Vector2f sizeTarget(range, range);
    FloatRect r1(path[i], sizeTarget);

    return (sprite.getGlobalBounds().intersects(r1));
}

bool Monster::isHit(Player& player)
{
    return ( this->sprite.getGlobalBounds().intersects(player.getWeapon().getSprite().getGlobalBounds()) );
}

void Monster::moveToTarget(Vector2f& player)
{
    if (isPlayerInRange(player)) 
    { 
        target = player;
    }
    else
    {
        if (isOnTarget(numberTarget))
        {
            if (numberTarget >= path.size() - 1) { numberTarget = 0;  target = path[numberTarget]; }
            else { numberTarget++; target = path[numberTarget]; }
        }
        else { target = path[numberTarget]; }
    }
    velocity = target - sprite.getPosition();
}

void Monster::takeDmg(int dmg)
{
    entityHP -= dmg;
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
void Monster::update(float dt, Player& player)
{
    if (isHit(player))
    {
        cout << isHit(player);
        if (player.getWeapon().getElapsedTime()<0.05)
        {
            this->takeDmg(0.01);
        }
    }
    moveToTarget(player.getPosition());
    normalize(velocity);
    if (isPlayerInRange(player.getPosition())) { sprite.move(velocity * 2.f * dt); }
    else { sprite.move(velocity * dt); }
    position = sprite.getPosition();
    monsterLifeBar.setPosition(position.x, position.y - 6);
}
void Monster::drawMonster(RenderWindow& rw)
{
    rw.draw(sprite);
    rw.draw(monsterLifeBar);
}


