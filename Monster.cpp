#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Entity.h"
#include "Monster.h"

using namespace sf;
using namespace std;

Monster::Monster(Vector2f pos) : Entity(200,pos)
{
    texture.loadFromFile("assets/ghost.png");
    sprite = Sprite(texture);
    sprite.setPosition(position);
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
sf::Sprite Monster::getSprite()
{
    return sprite;
}
sf::Vector2f Monster::setGetPositionMoove(Vector2f posMonster)
{
    int marge = 20;
    if (((posMonster.x <= (moove1.x + marge)) && (posMonster.x >= (moove1.x - marge))) && ((posMonster.y <= (moove1.y + marge)) && (posMonster.y >= (moove1.y - marge))))
    {
        positionMoove = moove2;
    }
    if (((posMonster.x <= (moove2.x + marge)) && (posMonster.x >= (moove2.x - marge))) && ((posMonster.y <= (moove2.y + marge)) && (posMonster.y >= (moove2.y - marge))))
    {
        positionMoove = moove1;
    }
    
    
    return positionMoove;
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
void Monster::update(float dt)
{
    position = sprite.getPosition();
    normalize(velocity, monsterSpeed);
    sprite.move(velocity*dt);
}
void Monster::drawMonster(RenderWindow& rw)
{
    rw.draw(sprite);
}
void Monster::mooveMonster(Vector2f& posMoove, Vector2f posMonster)
{
    int marge = -5;
    if (posMonster.x != posMoove.x ) 
    {
        if (posMonster.x < posMoove.x + marge)
        {
            setVelocityX(monsterSpeed);
        }
        if (posMonster.x > posMoove.x - marge)
        {
            setVelocityX(-monsterSpeed);
        }
    }
    if (posMonster.y != posMoove.y)
    {
        if (posMonster.y < posMoove.y + marge)
        {
            setVelocityY(monsterSpeed);
        }
        if (posMonster.y > posMoove.y - marge)
        {
            setVelocityY(-monsterSpeed);
        }
    }
}
void Monster::stopMonster(Vector2f& posMoove, Vector2f posMonster)
{
    if ( ( (posMonster.x <= (posMoove.x + 10)) && (posMonster.x >= (posMoove.x - 10)) ) &&  ( (posMonster.y <= (posMoove.y + 10)) && (posMonster.y >= (posMoove.y - 10)) ) )
    {
        setVelocityX(0);
        setVelocityY(0);
    }
}
//( posMonster.x <= (posMoove.x + 10) ) && ( posMonster.x >= (posMoove.x + 10) )
//( posMonster.y <= (posMoove.y + 10) ) && ( posMonster.y <= (posMoove.y + 10) )
/*
Dans cet example, il faudra faire d�placer un ennemi le long d'une s�rie de points configurables.
L'ennemi devra faire une pause d'une dur�e configurable � chaque arr�t, et faire demi tour selon le m�me trac�.

La vitesse du monstre doit �tre configurable.

Vous n'�tes pas oblig� d'animer le sprite, mais cela sera un bon bonus.

Afin de bien d�bugguer, il faudra afficher des petits points color�s repr�sentants l'itin�raire du monstre, avec aussi un trac�.
Il faudra donc utiliser sf::RectangleShape et sf::VertexArray, ainsi que sf::Timer.

Vous devrez donc cr�er une class enemy{} ou struct enemy{}, avec un constructeur,
et les m�thodes membres update(float delta) et draw(sf::RenderWindow & window).

Lorsque le personnage touche un monstre, la partie se finit avec un message game over en Texte via sf::Text, et le jeu recommence de z�ro.
Il faudra vous aider de la fonction Sprite::getGlobalBounds() et FloatRect::intersects()

Vous devrez r�utiliser, de pr�f�rence, le code de chargement de texte que vous avez �crit dans vos pr�c�dents projets.
*/

/*
Annexe: en pr�paration du projet de physique, vous pouvez commencer a cr�er une classe vehicle, que le personnage peut rentrer et sortir grace � la touche entr�e.

*/
