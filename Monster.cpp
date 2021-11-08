#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

#include "Entity.h"
#include "Monster.h"

using namespace sf;
using namespace std;

Monster::Monster(int scale, Vector2f pos) : Entity(200,pos)
{
    texture.loadFromFile("ghost.png");
    sprite = Sprite(texture);
    sprite.setScale(scale, scale);
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
void Monster::drawMonster(RenderWindow& rw)
{
    normalize(velocity, monsterSpeed);
    sprite.move(velocity.x, velocity.y);
    rw.draw(sprite);
}

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
