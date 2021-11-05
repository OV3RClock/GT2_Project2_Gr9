#include <SFML/Graphics.hpp>
#include <iostream>

#include "Tilemap.h"

using namespace sf;
using namespace std;

int main()
{
    
    #pragma region INIT
        int dim = 16;
        int scale = 3;
        sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
        #pragma region Player
            sf::RectangleShape entity(sf::Vector2f((dim*scale), (dim*scale)));
            Texture texture;
            texture.loadFromFile("ghost.png");
            Sprite sprite;
            entity.setTexture(&texture);
            #pragma endregion
        #pragma region Map
            Tilemap T;
            Texture maptexture;
            maptexture.loadFromFile("foresttiles2-t.png");
        #pragma endregion
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

        #pragma region Draw
            window.clear();

            vector<Sprite> vecground = T.loadGround(dim, scale, maptexture);
            for (int i = 0; i < vecground.size(); i++)
            {
                window.draw(vecground[i]);
            }
            vector<Sprite> vecmap = T.loadLevel(dim, scale, maptexture);
            for (int i = 0; i < vecmap.size(); i++)
            {
                window.draw(vecmap[i]);
            }

            window.draw(entity);
            window.draw(sprite);

            window.display();
        #pragma endregion
    }
    return 0;
}