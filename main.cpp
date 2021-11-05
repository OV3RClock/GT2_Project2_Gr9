#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

#include "Tilemap.h"
#include "Entity.h"

using namespace sf;
using namespace std;

void normalize(Vector2f &velocity, float speed) {
    float norme = sqrt((velocity.x * velocity.x) + (velocity.y * velocity.y));
    if (norme != 0)
    {
        velocity.x = ((velocity.x) / norme) * speed;
        velocity.y = ((velocity.y) / norme) * speed;
    }
}

int main()
{
    int dim = 16; // Ne pas changer (taille des tiles de foresttiles2-t.png)
    int scale = 4;

    #pragma region INIT

        sf::RenderWindow window(sf::VideoMode((dim*scale*12), (dim*scale*8)), "The game seems to be working..."); // La map possede 12 colones et 8 lignes
        window.setKeyRepeatEnabled(false);

        #pragma region Player
            sf::RectangleShape entity(sf::Vector2f(((dim-4)*scale), (dim*scale)));
            Texture texture;
            texture.loadFromFile("ghost.png");
            Sprite sprite;
            entity.setTexture(&texture);
            sf::Vector2f velocity;
            float speed = 0.5;
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
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) { window.close(); }
            if (event.type == Event::KeyReleased)
            {
                switch (event.key.code)
                {
                    case Keyboard::Z:
                        velocity.y -= velocity.y;
                        break;
                    case Keyboard::Q:
                        velocity.x -= velocity.x;
                        break;
                    case Keyboard::S:
                        velocity.y -= velocity.y;
                        break;
                    case Keyboard::D:
                        velocity.x -= velocity.x;
                        break;
                }
            }
        }

        if (Keyboard::isKeyPressed(Keyboard::Z)) { velocity.y -= speed; }
        if (Keyboard::isKeyPressed(Keyboard::Q)) { velocity.x -= speed; }
        if (Keyboard::isKeyPressed(Keyboard::S)) { velocity.y += speed; }
        if (Keyboard::isKeyPressed(Keyboard::D)) { velocity.x += speed; }

        normalize(velocity, speed);
        entity.move(velocity);
        cout << "Velocity " + to_string(velocity.x) + " | " + to_string(velocity.y) + "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

        #pragma region Draw
            window.clear();
            for (int i = 0; i < vecground.size(); i++) { window.draw(vecground[i]); }
            for (int i = 0; i < vecmap.size(); i++) { window.draw(vecmap[i]); }
            window.draw(entity);
            window.draw(sprite);
            window.display();
        #pragma endregion
    }
    return 0;
}