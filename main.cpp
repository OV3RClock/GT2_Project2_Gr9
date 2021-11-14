#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

#include "Tilemap.h"
#include "Entity.h"
#include "Player.h"
#include "Monster.h"
#include "Animation.h"

using namespace sf;
using namespace std;

// TODO
//
// Animation du monstre
// Dégats d'épée
// Hitboxes
//

int main()
{
    wcout << "CONTROLES DISPONIBLES POUR LE MOMENT\n\n"
             "ZQSD    : Deplacement\n"
             "R_CTRL  : Degainer sa super baguette\n"
             "L_SHIFT : Fuir tres vite\n";

    int fpsCap              = 144;
    float zoom              = 5;
    int windowWidth         = 1280;
    int windowHeight        = 720;

    float playerSpeed       = 100;
    float playerSprintSpeed = 200;
    float monsterSpeed      = 30;
    Vector2f spawnPos       = { 416,196 };
    Vector2f spawnPosM      = { 300,420 };

    #pragma region INIT

        // WINDOW
        int dim = 16; // Fixe (lié aux assets 16bits)
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "The game seems to be working...");
        window.setKeyRepeatEnabled(false);
        window.setFramerateLimit(fpsCap);

        // TEXTURE
        Texture characterTexture;
        characterTexture.loadFromFile("assets/characters.png");

        // WEAPON
        Weapon w(100);

        // PLAYER
        Player player(dim, characterTexture, spawnPos, w);
        Vector2f playerDir = { 0,0 };
        player.setSpeed(playerSpeed);
        bool isSprinting = false;
        bool isAttacking = false;

        // MONSTER
        Monster monster(dim, characterTexture, spawnPosM);
        monster.setSpeed(monsterSpeed);

        // VIEW
        sf::View view(Vector2f(player.getPosition().x + (float)(dim / 2),player.getPosition().y + (float)(dim / 2)), Vector2f(windowWidth, windowHeight));
        view.zoom(1.f/zoom);

        // TILEMAP
        Tilemap map(dim);

        // CLOCK
        Clock clock;
        float dt = 0;

    #pragma endregion

    while (window.isOpen())
    {
        Event event;

        clock.restart();

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed) { window.close(); }
            if (event.type == Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case Keyboard::RControl:
                        isAttacking = true;
                        break;
                }
            }
            if (event.type == Event::KeyReleased)
            {
                switch (event.key.code)
                {
                    case Keyboard::Z:
                        playerDir.y = 0;
                        break;
                    case Keyboard::Q:
                        playerDir.x = 0;
                        break;
                    case Keyboard::S:
                        playerDir.y = 0;
                        break;
                    case Keyboard::D:
                        playerDir.x = 0;
                        break;
                    case Keyboard::LShift:
                        player.setSpeed(playerSpeed);
                        isSprinting = false;
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

        #pragma region PlayerInput
            if (Keyboard::isKeyPressed(Keyboard::LShift)) 
            { 
                player.setSpeed(playerSprintSpeed);
                isSprinting = true;
            }
            if (Keyboard::isKeyPressed(Keyboard::Z)) { playerDir.y = -1; }
            if (Keyboard::isKeyPressed(Keyboard::Q)) { playerDir.x = -1; }
            if (Keyboard::isKeyPressed(Keyboard::S)) { playerDir.y = 1; }
            if (Keyboard::isKeyPressed(Keyboard::D)) { playerDir.x = 1; }
            player.setDirection(playerDir);
        #pragma endregion

        #pragma region MonsterMovementIndicator
            sf::Vertex vertices[] =
            {
                sf::Vertex(monster.getTarget(), sf::Color::Red),
                sf::Vertex(sf::Vector2f(monster.getTarget().x, monster.getTarget().y + dim), sf::Color::Red),
                sf::Vertex(sf::Vector2f(monster.getTarget().x + dim, monster.getTarget().y + dim), sf::Color::Red),
                sf::Vertex(sf::Vector2f(monster.getTarget().x + dim, monster.getTarget().y), sf::Color::Red)
            };
        #pragma endregion

        #pragma region Update
            player.update(dt, isSprinting, isAttacking);
            monster.update(dt, player.getPosition());
        #pragma endregion

        #pragma region Draw
            window.clear();

            view.setCenter(Vector2f(player.getPosition().x + (float)(dim/2), player.getPosition().y + (float)(dim/2)));
            window.setView(view);

            map.drawTilemap(window);
            window.draw(vertices, 4, sf::Quads);
            monster.drawMonster(window);
            player.drawPlayer(window, isAttacking);

            window.display();
        #pragma endregion

        #pragma region Debug
            /*
            std::cout << "         dt | " + to_string(dt) + "\n\n" +
                         " Position X | " + to_string(player.getPosition().x) + "\n" +
                         " Position Y | " + to_string(player.getPosition().y) + "\n\n" +
                         " Velocity X | " + to_string(player.getVelocity().x) + "\n" +
                         " Velocity Y | " + to_string(player.getVelocity().y) + "\n\n" +
                         "MPosition X | " + to_string(monster.getPosition().x) + "\n" +
                         "MPosition Y | " + to_string(monster.getPosition().y) + "\n\n" +
                         "MVelocity X | " + to_string(monster.getVelocity().x) + "\n" +
                         "MVelocity Y | " + to_string(monster.getVelocity().y) + "\n" +
                         "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            */
        #pragma endregion

        dt = clock.getElapsedTime().asSeconds();
    }
}