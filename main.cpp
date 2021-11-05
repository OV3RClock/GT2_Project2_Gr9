#include <SFML/Graphics.hpp>
#include <iostream>

#include "Tilemap.h"

using namespace sf;
using namespace std;

int main()
{
    int dim = 16; // Ne pas changer
    int scale = 6;
    #pragma region INIT
        sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
        window.setKeyRepeatEnabled(false);
        #pragma region Player
            sf::RectangleShape entity(sf::Vector2f(((dim-4)*scale), (dim*scale)));
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
                    break;
                case Keyboard::Q:
                    velocity.x -= speed;
                    break;
                case Keyboard::S:
                    velocity.y += speed;
                    break;
                case Keyboard::D:
                    velocity.x += speed;
                    break;
                }
            }
            entity.move(velocity);
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