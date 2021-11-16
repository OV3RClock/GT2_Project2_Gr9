#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Entity.h"
#include "Monster.h"
#include "Animation.h"
#include "LifeBar.h"

using namespace sf;
using namespace std;

Monster::Monster(const int dim, float hp, Texture& texture, Vector2f pos) : Entity(hp,pos), monsterLifeBar(LifeBar(hp))
{
    animations[(int)AnimationIndex::Up] = Animation(6 * dim, 7 * dim, dim, dim, 3, 0.3, texture);
    animations[(int)AnimationIndex::Left] = Animation(6 * dim, 5 * dim, dim, dim, 3, 0.3, texture);
    animations[(int)AnimationIndex::Down] = Animation(6 * dim, 4 * dim, dim, dim, 3, 0.3, texture);
    animations[(int)AnimationIndex::Right] = Animation(6 * dim, 6 * dim, dim, dim, 3, 0.3, texture);
    
    sprite = Sprite(texture);
    sprite.setTextureRect(IntRect(10 * dim, 0, dim, dim));
    sprite.setPosition(pos);
    
    Vector2f point0 = { 300,420 };
    Vector2f point1 = { 530,360 };
    Vector2f point2 = { 440,480 };
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

bool Monster::isHit(Player player)
{
    return ( this->sprite.getGlobalBounds().intersects(player.getWeapon().getSprite().getGlobalBounds()) );
}

bool Monster::monsterHitPlayer(Player player)
{
    return (player.getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()));
}

void Monster::setDirection()
{
    if (velocity.x > 0.0f)
    {
        curAnimation = AnimationIndex::Right;
    }
    else if (velocity.x < 0.0f)
    {
        curAnimation = AnimationIndex::Left;
    }
    else if (velocity.y < 0.0f)
    {
        curAnimation = AnimationIndex::Up;
    }
    else if (velocity.y > 0.0f)
    {
        curAnimation = AnimationIndex::Down;
    }
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
void Monster::update(float dt, Player& player, bool& isTouched)
{

    if (isHit(player))
    {
        if (!isTouched)
        {
            this->takeDmg(10);
            isTouched = true;
        }
    }
    if (monsterHitPlayer(player))
    {
        if (elapsedTime > 1.5)
        {
            player.takeDmg(10);
            elapsedTime = 0;
        }
    }
    moveToTarget(player.getPosition());
    normalize(velocity);
    setDirection();
    if (isPlayerInRange(player.getPosition())) 
    { 
        animations[int(curAnimation)].update(dt);
        animations[int(curAnimation)].applyToSprite(sprite);
        sprite.move(velocity * 2.f * dt);

    }
    else 
    { 
        animations[int(curAnimation)].update(dt);
        animations[int(curAnimation)].applyToSprite(sprite);
        sprite.move(velocity * dt); 
    }
    
    position = sprite.getPosition();
    monsterLifeBar.setPosition(position.x, position.y - 6);
    elapsedTime += dt;
}
void Monster::drawMonster(RenderWindow& rw)
{
    rw.draw(sprite);
    rw.draw(monsterLifeBar);
}


