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
    
    Vector2f point0 = { 100 , 150 };
    Vector2f point1 = { 40 , 10 };
    Vector2f point2 = { 200 , 50 };
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


void Monster::moveToTarget(Vector2f& player)
{
    
    if (playerIsInRange(player)) {
        
        target = player;
    }
    else
    {
        if (isOnTarget(numberTarget))
        {
            if (numberTarget >= path.size() - 1)
            {
                numberTarget = 0;
                target = path[numberTarget];
            }
            else
            {
                numberTarget++;
                target = path[numberTarget];
            }
        }
        else
        {
            target = path[numberTarget];
        }
    }
    movementMonster = target - sprite.getPosition();
}
bool Monster::isOnTarget(int i)
{
    float range = 0.5;
    Vector2f sizeTarget(range, range);
    FloatRect r1(path[i], sizeTarget);


    return (sprite.getGlobalBounds().intersects(r1));

/*((sprite.getPosition().x <= (path[i].x + range))
&& (sprite.getPosition().x >= (path[i].x - range))
&& (sprite.getPosition().y <= (path[i].y + range))
&& (sprite.getPosition().y >= (path[i].y - range)));*/
}

bool Monster::playerIsInRange(Vector2f& player)
{
    return ( ( sqrt( (player.x - sprite.getPosition().x)* (player.x - sprite.getPosition().x) + (player.x - sprite.getPosition().x) * (player.x - sprite.getPosition().x)) <= 100 ) );
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
void Monster::update(float dt, Vector2f& player)
{

    moveToTarget(player);
    normalize(movementMonster);
    sprite.move(movementMonster*dt);
    position = sprite.getPosition();
    monsterLifeBar.setPosition(position.x, position.y - 6);
}
void Monster::drawMonster(RenderWindow& rw)
{
    rw.draw(sprite);
    rw.draw(monsterLifeBar);
}


