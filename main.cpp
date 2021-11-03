#include <SFML/Graphics.hpp>
#include <iostream>

#include "Tilemap.h"

using namespace sf;

int main()
{
    
    #pragma region INIT
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    sf::RectangleShape entity(sf::Vector2f(100.f, 100.f));
    Texture texture;
    texture.loadFromFile("ghost.png");
    Sprite sprite;
    entity.setTexture(&texture);
    Tilemap T;
    Texture maptexture;
    maptexture.loadFromFile("foresttiles2-t.png");
    #pragma endregion

    while (window.isOpen())
    {
        sf::Event event;

        float speed = 20.f;
        sf::Vector2f v;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){window.close();}  
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case Keyboard::Z:
                        v.y -= speed;
                        entity.move(v);
                        break;
                    case Keyboard::Q:
                        v.x -= speed;
                        entity.move(v);
                        break;
                    case Keyboard::S:
                        v.y += speed;
                        entity.move(v);
                        break;
                    case Keyboard::D:
                        v.x += speed;
                        entity.move(v);
                        break;
                }
            }
        } 
        
        window.clear();
        window.draw(entity);
        window.draw(sprite);
        window.draw(T.loadLevel(maptexture));
        window.display();

        //Sprite::setTextureRect();
    }

    return 0;
}