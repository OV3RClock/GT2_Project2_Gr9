#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

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
            float speed = 0.5;
            sf::Vector2f velocity;
            #pragma endregion
        #pragma region Map
            Tilemap T;
            Texture maptexture;
            maptexture.loadFromFile("foresttiles2-t.png");
            vector<Sprite> vecground = T.loadGround(dim, scale, maptexture);
            vector<Sprite> vecmap = T.loadLevel(dim, scale, maptexture);
        #pragma endregion
    #pragma endregion

    while (window.isOpen())
    {
        sf::Event event;

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
            if (event.type == sf::Event::KeyReleased)
            {
                switch (event.key.code)
                {
                case Keyboard::Z:
                    velocity.y = 0;
                    break;
                case Keyboard::Q:
                    velocity.x = 0;
                    break;
                case Keyboard::S:
                    velocity.y = 0;
                    break;
                case Keyboard::D:
                    velocity.x = 0;
                    break;
                }
            }
        }

        float z = sqrt((velocity.x*velocity.x) + (velocity.y*velocity.y));
        if (z != 0) {
            velocity.x = ((velocity.x) / z) * speed;
            velocity.y = ((velocity.y) / z) * speed;
            entity.move(velocity);
            cout << "Velocity : " + to_string(z) + "\n";
        }

        #pragma region Draw
            window.clear();
            for (int i = 0; i < vecground.size(); i++)
            {
                window.draw(vecground[i]);
            }
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