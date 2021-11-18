#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <random>

#include "Entity.h"
#include "Monster.h"
#include "Animation.h"
#include "LifeBar.h"

using namespace sf;
using namespace std;

Monster::Monster(Texture& texture) : Entity(hp, pos), monsterLifeBar(LifeBar(hp))
{
    animations[(int)AnimationIndex::Up] = Animation(6 * dim, 7 * dim, dim, dim, 3, 0.3, texture);
    animations[(int)AnimationIndex::Left] = Animation(6 * dim, 5 * dim, dim, dim, 3, 0.3, texture);
    animations[(int)AnimationIndex::Down] = Animation(6 * dim, 4 * dim, dim, dim, 3, 0.3, texture);
    animations[(int)AnimationIndex::Right] = Animation(6 * dim, 6 * dim, dim, dim, 3, 0.3, texture);
    
    sprite = Sprite(texture);
    sprite.setTextureRect(IntRect(10 * dim, 0, dim, dim));
    sprite.setPosition({ 300 , 420 });

    Vector2f zoneMin = { pos.x - 100 , pos.y - 100 };
    Vector2f zoneMax = { pos.x + 100 , pos.y + 100 };
    Vector2f point0 = { (random_float(zoneMin.x, zoneMax.x)) ,(random_float(zoneMin.y, zoneMax.y)) };
    Vector2f point1 = { (random_float(zoneMin.x, zoneMax.x)) ,(random_float(zoneMin.y, zoneMax.y)) };
    Vector2f point2 = { (random_float(zoneMin.x, zoneMax.x)) ,(random_float(zoneMin.y, zoneMax.y)) };
    path.push_back(point0);
    path.push_back(point1);
    path.push_back(point2);
    target = point0;


    entityHP = hp;

}
Monster::~Monster()
{
}

float Monster::random_float(float min, float max)
{
    return ((float)rand() / RAND_MAX) * (max - min) + min;
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

bool Monster::isHit(Player& player, bool isAttacking)
{
    
        return ((sprite.getGlobalBounds().intersects(player.getWeapon().getSprite().getGlobalBounds())) && isAttacking);
        
}

bool Monster::monsterHitPlayer(Player& player)
{
    return (player.getSprite().getGlobalBounds().intersects(sprite.getGlobalBounds()));
}

void Monster::setDirection()
{
    if (abs(velocity.y) > abs(velocity.x)) 
    {
        if (velocity.y < 0.0f)
        {
            curAnimation = AnimationIndex::Up;
        }
        else if (velocity.y > 0.0f)
        {
            curAnimation = AnimationIndex::Down;
        }
    }
    else 
    {
        if (velocity.x > 0.0f)
        {
            curAnimation = AnimationIndex::Right;
        }
        else if (velocity.x < 0.0f)
        {
            curAnimation = AnimationIndex::Left;
        }
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

void Monster::takeDmg(float dmg)
{
    this->entityHP -= dmg;
    
    if (entityHP >= 0)
    {
        monsterLifeBar.setValue(entityHP);
    }
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
void Monster::update(float dt, Player& player, bool isAttacking)
{
    
    
        
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
        if (isHit(player, isAttacking))
        {
            if (elapsedHit > 1)
            {
                this->takeDmg(player.getWeapon().getDmg());
                elapsedHit = 0;
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
        monsterLifeBar.setPosition(position.x, position.y - 6);
        elapsedTime += dt;
        elapsedHit += dt;
        
    
}
void Monster::drawMonster(RenderWindow& rw)
{
        rw.draw(monsterLifeBar);
        rw.draw(sprite);
}


