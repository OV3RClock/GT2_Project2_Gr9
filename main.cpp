#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

#include "Tilemap.h"
#include "Entity.h"
#include "Player.h"
#include "Monster.h"

using namespace sf;
using namespace std;

int main()
{
    int fpsCap = 144;
    float zoom = 4;
    int width = 1280; //128
    int height = 720; //72

    float playerSpeed = 300;
    Vector2f spawnPos = { 20,20 };
    Vector2f spawnPosM = { 100,50 };

    #pragma region INIT

        // PLAYER
        Player player(spawnPos);
        player.setSpeed(playerSpeed);

        // MONSTER
        Monster monster(spawnPosM);
        monster.setSpeed(playerSpeed);

        // WINDOW
        int dim = 16; // Fixe (lié à foresttiles2-t.png)
        sf::RenderWindow window(sf::VideoMode(width, height), "The game seems to be working..."); // La map possede 12 colones et 8 lignes
        window.setKeyRepeatEnabled(false);
        window.setFramerateLimit(fpsCap);
        float dt = (1.f / (float)fpsCap);

        // VIEW
        sf::View view(Vector2f(player.getPosition().x + (float)(dim / 2),player.getPosition().y + (float)(dim / 2)), Vector2f(width, height));
        view.zoom(1.f/zoom);

        sf::View minimapView(player.getPosition(), Vector2f(width, height));
        minimapView.zoom(1.f / zoom);

        // TILEMAP
        Tilemap map(dim);

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
                        player.setVelocityY(0);
                        break;
                    case Keyboard::Q:
                        player.setVelocityX(0);
                        break;
                    case Keyboard::S:
                        player.setVelocityY(0);
                        break;
                    case Keyboard::D:
                        player.setVelocityX(0);
                        break;
                }
            }
        }

        if (event.type == sf::Event::Resized)
        {
            // on met à jour la vue, avec la nouvelle taille de la fenêtre
            sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
            window.setView(sf::View(visibleArea));
        }

        #pragma region PlayerMovement
            if (Keyboard::isKeyPressed(Keyboard::Z)) { player.setVelocityY(-player.getSpeed()); }
            if (Keyboard::isKeyPressed(Keyboard::Q)) { player.setVelocityX(-player.getSpeed()); }
            if (Keyboard::isKeyPressed(Keyboard::S)) { player.setVelocityY(player.getSpeed()); }
            if (Keyboard::isKeyPressed(Keyboard::D)) { player.setVelocityX(player.getSpeed()); }
            player.update(dt);
        #pragma endregion

        //test moove monster hugo
        monster.mooveMonster(monster.setGetPositionMoove(), monster.getPosition());
        monster.update(dt);

        #pragma region Draw
            window.clear();
            view.setCenter(Vector2f(player.getPosition().x + (float)(dim/2), player.getPosition().y + (float)(dim/2)));

            window.setView(view);
            map.drawTilemap(window);
            monster.drawMonster(window);
            player.drawPlayer(window);

            window.display();
            /*
            cout << "Position X | " + to_string(player.getPosition().x) + "\n" +
                    "Position Y | " + to_string(player.getPosition().y) + "\n\n" +
                    "Velocity X | " + to_string(player.getVelocity().x) + "\n" +
                    "Velocity Y | " + to_string(player.getVelocity().y) + "\n\n" +
                    "MPosition X | " + to_string(monster.getPosition().x) + "\n" +
                    "MPosition Y | " + to_string(monster.getPosition().y) + "\n\n" +
                    "MVelocity X | " + to_string(monster.getVelocity().x) + "\n" +
                    "MVelocity Y | " + to_string(monster.getVelocity().y) + "\n" +
                    "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";*/
        #pragma endregion
    }
}
