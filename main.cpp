#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

#include "Tilemap.h"
#include "Entity.h"

using namespace sf;
using namespace std;

void normalize(Vector2f& velocity, float speed) {
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

        sf::RenderWindow window(sf::VideoMode((dim*scale*12), (dim*scale*8)), "The game seems to be working...");
        window.setKeyRepeatEnabled(false);

        #pragma region Player
            sf::RectangleShape entity(sf::Vector2f(((dim-4)*scale), (dim*scale)));
            Texture texture;
            texture.loadFromFile("ghost.png");
            Sprite sprite;
            entity.setTexture(&texture);
            float speed = 0.5;
            sf::Vector2f velocity;
            bool z = false;
            bool q = false;
            bool s = false;
            bool d = false;
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
            /*
            if (Keyboard::isKeyPressed(Keyboard::Z)) { velocity.y -= speed; }
            if (Keyboard::isKeyPressed(Keyboard::Q)) { velocity.x -= speed; }
            if (Keyboard::isKeyPressed(Keyboard::S)) { velocity.y += speed; }
            if (Keyboard::isKeyPressed(Keyboard::D)) { velocity.x += speed; }
            
            if (!Keyboard::isKeyPressed(Keyboard::Z)) { velocity.y += abs(velocity.y); }
            if (!Keyboard::isKeyPressed(Keyboard::Q)) { velocity.x += abs(velocity.x); }
            if (!Keyboard::isKeyPressed(Keyboard::S)) { velocity.y -= velocity.y; }
            if (!Keyboard::isKeyPressed(Keyboard::D)) { velocity.x -= velocity.x; }
            */
            
            if (event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case Keyboard::Z:
                        z = true;
                        break;
                    case Keyboard::Q:
                        q = true;
                        break;
                    case Keyboard::S:
                        s = true;
                        break;
                    case Keyboard::D:
                        d = true;
                        break;
                }
            }
            if (event.type == Event::KeyReleased)
            {
                switch (event.key.code)
                {
                    case Keyboard::Z:
                        z = false;
                        break;
                    case Keyboard::Q:
                        q = false;
                        break;
                    case Keyboard::S:
                        s = false;
                        break;
                    case Keyboard::D:
                        d = false;
                        break;
                }
            }

            if (z) { velocity.y -= speed; }
            if (q) { velocity.x -= speed; }
            if (s) { velocity.y += speed; }
            if (d) { velocity.x += speed; }

            if (!z) { velocity.y = 0; }
            if (!q) { velocity.x = 0; }
            if (!s) { velocity.y = 0; }
            if (!d) { velocity.x = 0; }
        }

        normalize(velocity, speed);
        entity.move(velocity);
        cout << "Velocity " + to_string(velocity.x) + " | " + to_string(velocity.y) + "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";

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

/*
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Q) { activeKeys[LEFT] = true; }
            if (event.key.code == sf::Keyboard::Z) { activeKeys[UP] = true; }
            if (event.key.code == sf::Keyboard::S) { activeKeys[DOWN] = true; }
            if (event.key.code == sf::Keyboard::D) { activeKeys[RIGHT] = true; }
        }

        if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::Q) { activeKeys[LEFT] = false; }
            if (event.key.code == sf::Keyboard::Z) { activeKeys[UP] = false; }
            if (event.key.code == sf::Keyboard::S) { activeKeys[DOWN] = false; }
            if (event.key.code == sf::Keyboard::D) { activeKeys[RIGHT] = false; }
        }

        if (activeKeys[UP]) { sprite.move(0, -vit); }
        if (!activeKeys[UP]) { sprite.move(0, 0); }

        if (activeKeys[LEFT]) { sprite.move(-vit, 0); }
        if (!activeKeys[LEFT]) { sprite.move(0, 0); }

        if (activeKeys[RIGHT]) { sprite.move(vit, 0); }
        if (!activeKeys[RIGHT]) { sprite.move(0, 0); }

        if (activeKeys[DOWN]) { sprite.move(0, vit); }
        if (!activeKeys[DOWN]) { sprite.move(0, 0); }
*/