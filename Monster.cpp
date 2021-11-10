#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Entity.h"
#include "Monster.h"

using namespace sf;
using namespace std;

Monster::Monster(int dim, Texture texture, Vector2f pos) : Entity(200,pos)
{
    sprite = Sprite(texture);
    sprite.setTextureRect(IntRect(10 * dim, 0, dim, dim));
    sprite.setPosition(position);
    setHP(200);
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
sf::Vector2f Monster::setPositionMoove(Vector2f& posMonster)
{
    int range = 1;
    if ((posMonster.x <= (moove2.x + range)) && (posMonster.x >= (moove2.x - range)) && (posMonster.y <= (moove2.y + range)) && (posMonster.y >= (moove2.y - range))) { positionMoove = moove1; };

    if ((posMonster.x <= (moove1.x + range)) && (posMonster.x >= (moove1.x - range)) && (posMonster.y <= (moove1.y + range)) && (posMonster.y >= (moove1.y - range))) { positionMoove = moove2; };
    moovementMonster.x = positionMoove.x - posMonster.x;
    moovementMonster.y = positionMoove.y - posMonster.y;

    
    return moovementMonster;
}
sf::Vector2f Monster::getPositionMoove()
{
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
void Monster::setHP(int i)
{
    entityHP = i;
    monsterLifeBar.setValue(entityHP);
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
    setPositionMoove(position);
    normalize(moovementMonster, monsterSpeed);
    sprite.move(moovementMonster*dt);
}
void Monster::drawMonster(RenderWindow& rw)
{
    rw.draw(sprite);
}

//( posMonster.x <= (posMoove.x + 5) ) && ( posMonster.x >= (posMoove.x + 5) )
//( posMonster.y <= (posMoove.y + 5) ) && ( posMonster.y <= (posMoove.y + 5) )
/*
Dans cet example, il faudra faire déplacer un ennemi le long d'une série de points configurables.
L'ennemi devra faire une pause d'une durée configurable à chaque arrêt, et faire demi tour selon le même tracé.

La vitesse du monstre doit être configurable.

Vous n'êtes pas obligé d'animer le sprite, mais cela sera un bon bonus.

Afin de bien débugguer, il faudra afficher des petits points colorés représentants l'itinéraire du monstre, avec aussi un tracé.
Il faudra donc utiliser sf::RectangleShape et sf::VertexArray, ainsi que sf::Timer.

Vous devrez donc créer une class enemy{} ou struct enemy{}, avec un constructeur,
et les méthodes membres update(float delta) et draw(sf::RenderWindow & window).

Lorsque le personnage touche un monstre, la partie se finit avec un message game over en Texte via sf::Text, et le jeu recommence de zéro.
Il faudra vous aider de la fonction Sprite::getGlobalBounds() et FloatRect::intersects()

Vous devrez réutiliser, de préférence, le code de chargement de texte que vous avez écrit dans vos précédents projets.
*/

/*
Annexe: en préparation du projet de physique, vous pouvez commencer a créer une classe vehicle, que le personnage peut rentrer et sortir grace à la touche entrée.

*/
