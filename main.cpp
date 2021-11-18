#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

#include "Tilemap.h"
#include "Entity.h"
#include "Player.h"
#include "Monster.h"
#include "Animation.h"
#include "LifeBar.h"

using namespace sf;
using namespace std;

// TODO
// 
// Epona
// Inventaire
// Despawn mob + drop d'objets
// Fix hp mob quand premier contact ?? Aucune idée de pk
// 

int main()
{
    //cout << "CONTROLES DISPONIBLES POUR LE MOMENT\n\n"
              "> ZQSD    : Deplacement\n"
              "> R_CTRL  : Degainer sa super baguette\n"
              "> L_SHIFT : Fuir tres vite\n"
              "> H       : Afficher les Hitboxes"
              "> M       : Utiliser sa monture";

    int fpsCap              = 144;
    float zoom              = 4;
    int windowWidth         = 1280;
    int windowHeight        = 720;
    int maxNbMonster        = 5;

    float playerHp          = 200;
    float monster1Hp        = 150;
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
        Texture monsterTexture;
        monsterTexture.loadFromFile("assets/characters.png");

        // PLAYER
        Player player(dim, playerHp, spawnPos, 30);
        Vector2f playerDir = { 0,0 };
        player.setSpeed(playerSpeed);

        const float pi = 3.14159265358979323846; 
        float masse = 50.f;
        float poussee = 0;
        float angle = 0;
        float friction = 60;

        bool isSprinting = false;
        bool isAttacking = false;
        bool isOnMount = false;

        // MONSTER
        vector<Monster*> monsterList;
        Monster *monster1 = new Monster(monsterTexture);
        Monster *monster2 = new Monster(monsterTexture);
        monsterList.push_back(monster1);
        monsterList.push_back(monster2);

        // VIEW
        sf::View view(Vector2f(player.getPosition().x + (float)(dim / 2),player.getPosition().y + (float)(dim / 2)), Vector2f(windowWidth, windowHeight));
        view.zoom(1.f/zoom);

        // TILEMAP
        Tilemap map(dim);
        vector<Sprite> borders = map.getMapBorders();
        bool toggleHitBoxes = false;

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
                    case Keyboard::H:
                        if (toggleHitBoxes) { toggleHitBoxes = false; }
                        else { toggleHitBoxes = true; }
                        break;
                    case Keyboard::M:
                        if (isOnMount) { isOnMount = false; player.setDirection(playerDir); playerDir = { 0,0 }; }
                        else { isOnMount = true; player.setDirection(playerDir); playerDir = { 0,0 }; }
                        break;
                }
            }
            if (event.type == Event::KeyReleased)
            {
                if (!isOnMount)
                {
                    switch (event.key.code)
                    {
                        case Keyboard::Z:
                        case Keyboard::W:
                            playerDir.y = 0;
                            break;
                        case Keyboard::Q:
                        case Keyboard::A:
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
                if (isOnMount)
                {
                    switch (event.key.code)
                    {
                        case Keyboard::Z:
                        case Keyboard::W:
                            poussee = 0;
                            break;
                        case Keyboard::S:
                            poussee = 0;
                            break;
                    }
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
        if (isOnMount)
        {
            if (Keyboard::isKeyPressed(Keyboard::Z)) { poussee = 5000; }
            if (Keyboard::isKeyPressed(Keyboard::W)) { poussee = 5000; }
            if (Keyboard::isKeyPressed(Keyboard::Q)) { angle -= 2 * pi / 180; }
            if (Keyboard::isKeyPressed(Keyboard::A)) { angle -= 2 * pi / 180; }
            if (Keyboard::isKeyPressed(Keyboard::S)) { poussee = -500; }
            if (Keyboard::isKeyPressed(Keyboard::D)) { angle += 2 * pi / 180; }

            playerDir = { cos(angle), sin(angle) };

            // TEST DE COLLISION
            Vector2f newpos = player.getPosition() + Vector2f{ ((float)dim / 2),((float)dim / 2) } + Vector2f{ playerDir.x, playerDir.y };
            FloatRect newposRect = FloatRect(newpos.x - dim / 2, newpos.y - dim / 2, dim, dim);
            for (int i = 0; i < borders.size(); i++)
            {
                if (newposRect.intersects(borders[i].getGlobalBounds()))
                {
                    player.setVelocityX(0);
                    player.setVelocityY(0);
                }
            }

            player.setDirection(playerDir, poussee, masse, angle, friction, dt);

        }
        else
        {
            if (Keyboard::isKeyPressed(Keyboard::LShift))
            {
                player.setSpeed(playerSprintSpeed);
                isSprinting = true;
            }
            if (Keyboard::isKeyPressed(Keyboard::Z)) { playerDir.y = -1; }
            if (Keyboard::isKeyPressed(Keyboard::W)) { playerDir.y = -1; }
            if (Keyboard::isKeyPressed(Keyboard::Q)) { playerDir.x = -1; }
            if (Keyboard::isKeyPressed(Keyboard::A)) { playerDir.x = -1; }
            if (Keyboard::isKeyPressed(Keyboard::S)) { playerDir.y = 1; }
            if (Keyboard::isKeyPressed(Keyboard::D)) { playerDir.x = 1; }

            // TEST DE COLLISION
            Vector2f newpos = player.getPosition() + Vector2f{ ((float)dim / 2),((float)dim / 2) } + Vector2f{ playerDir.x, playerDir.y };
            FloatRect newposRect = FloatRect(newpos.x - dim / 2, newpos.y - dim / 2, dim, dim);
            for (int i = 0; i < borders.size(); i++)
            {
                if (newposRect.intersects(borders[i].getGlobalBounds()))
                {
                    playerDir = { 0,0 };
                }
            }

            player.setDirection(playerDir);
        }
        #pragma endregion

        #pragma region Hitboxes
            /*Vertex vertices[] =
            {
                Vertex(monster1->getTarget(), Color::Red),
                Vertex(Vector2f(monster1->getTarget().x, monster1->getTarget().y + dim), Color::Red),
                Vertex(Vector2f(monster1->getTarget().x + dim, monster1->getTarget().y + dim), Color::Red),
                Vertex(Vector2f(monster1->getTarget().x + dim, monster1->getTarget().y), Color::Red)
            };*/
            Vertex pvertices[] = 
            { 
                Vertex(player.getPosition(), Color::Red),
                Vertex(Vector2f(player.getPosition().x, player.getPosition().y + dim), Color::Red),
                Vertex(Vector2f(player.getPosition().x + dim, player.getPosition().y + dim), Color::Red),
                Vertex(Vector2f(player.getPosition().x + dim, player.getPosition().y), Color::Red)
            };
            Vertex playerDirectionIndicator[] =
            {
                Vertex(Vector2f(player.getPosition().x + 8, player.getPosition().y + 8), Color::Blue),
                Vertex(Vector2f(((player.getPosition().x+8) + (playerDir.x)*20), ((player.getPosition().y+8) + (playerDir.y)*20)), Color::Blue)
            };
        #pragma endregion

        #pragma region Update
            for (auto& enemy : monsterList)
            {
                if (enemy->isAlive())
                {
                    enemy->update(dt, player, isAttacking);
                }
                else
                {
                    monsterList.erase(std::remove(monsterList.begin(), monsterList.end(), enemy), monsterList.end());
                }
            }
            player.update(dt, isSprinting, isAttacking, isOnMount);
        #pragma endregion

        #pragma region Draw
            window.clear();

            view.setCenter(Vector2f(player.getPosition().x + (float)(dim/2), player.getPosition().y + (float)(dim/2)));
            window.setView(view);

            map.drawTilemap(window);
            if (toggleHitBoxes) 
            {
                map.drawMapBorders(window);
                window.draw(pvertices, 4, Quads);
            }
            
            for (int i = 0; i < monsterList.size(); i++)
            {
                monsterList[i]->drawMonster(window);
            }
            if (isOnMount) 
            {
                window.draw(playerDirectionIndicator, 2, Lines);
            }
            player.drawPlayer(window, isAttacking);
            

            //monster1.drawMonster(window);
            window.display();
        #pragma endregion

        #pragma region Debug
            cout << 1 / dt << "\n";
            /*
            std::cout << "         dt | " + to_string(dt) + "\n\n" +
                         " Position X | " + to_string(player.getPosition().x) + "\n" +
                         " Position Y | " + to_string(player.getPosition().y) + "\n\n" +
                         " Velocity X | " + to_string(player.getVelocity().x) + "\n" +
                         " Velocity Y | " + to_string(player.getVelocity().y) + "\n\n" +
                         "MPosition X | " + to_string(monsterList[0]->getPosition().x) + "\n" +
                         "MPosition Y | " + to_string(monsterList[0]->getPosition().y) + "\n\n" +
                         "MVelocity X | " + to_string(monsterList[0]->getVelocity().x) + "\n" +
                         "MVelocity Y | " + to_string(monsterList[0]->getVelocity().y) + "\n" +
                         "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
            */
        #pragma endregion
        
        cout << 1 / dt << "\n";
        dt = clock.getElapsedTime().asSeconds();
    }
}