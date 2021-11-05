#include <SFML/Graphics.hpp>
#include <iostream>

#include "Tilemap.h"

using namespace sf;
using namespace std;

int main()
{
    
    #pragma region INIT

    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");

    #pragma region Player
    sf::RectangleShape entity(sf::Vector2f(100.f, 100.f));
    Texture texture;
    texture.loadFromFile("ghost.png");
    Sprite sprite;
    entity.setTexture(&texture);
    #pragma endregion

    Tilemap T;
    Texture maptexture;
    maptexture.loadFromFile("foresttiles2-t.png");

    #pragma endregion

    while (window.isOpen())
    {
        sf::Event event;

        float speed = 20.f;
        sf::Vector2f velocity;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) { window.close(); }
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case Keyboard::Z:
                    velocity.y -= speed;
                    entity.move(velocity);
                    break;
                case Keyboard::Q:
                    velocity.x -= speed;
                    entity.move(velocity);
                    break;
                case Keyboard::S:
                    velocity.y += speed;
                    entity.move(velocity);
                    break;
                case Keyboard::D:
                    velocity.x += speed;
                    entity.move(velocity);
                    break;
                }
            }
        }

        window.clear();

        vector<Sprite> vecmap = T.loadLevel(maptexture);
        for (int i=0; i<vecmap.size(); i++)
        {
            window.draw(vecmap[i]);
        }
        window.draw(entity);
        window.draw(sprite);
        window.display();

        //Sprite::setTextureRect();
    }

    return 0;
}