#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <Windows.h>

#include "Tilemap.h"
#include "Entity.h"
#include "Player.h"
#include "Monster.h"
#include "Animation.h"
#include "LifeBar.h"
#include "Inventory.h"
#include "Item.h"

using namespace sf;
using namespace std;

void game(int fpsCap, float zoom, float windowWidth, float windowHeight, float playerHp, float playerSpeed, float playerSprintSpeed, Vector2f spawnPos, int monsterQuantity)
{
    #pragma region INIT

        // WINDOW
        int dim = 16; // Fixe (lié aux assets 16bits)
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Samurai simulator is UP !");
        window.setKeyRepeatEnabled(false);
        window.setFramerateLimit(fpsCap);

        // SOUND
        SoundBuffer buffer;
        buffer.loadFromFile("assets/Island.ogg");
        Sound sound;
        sound.setBuffer(buffer);
        sound.setVolume(50.f);
        sound.setLoop(true);
        sound.play();

        // TEXTURE
        Texture monsterTexture;
        monsterTexture.loadFromFile("assets/characters.png");

        // PLAYER
        Player player(dim, playerHp, spawnPos, 30);
        Vector2f playerDir = { 0,0 };
        player.setSpeed(playerSpeed);

        const float PI = 3.14159265358979323846;
        float masse = 500;
        float poussee = 0;
        float angle = 0;
        float friction = 500;

        bool isSprinting = false;
        bool isAttacking = false;
        bool isOnMount = false;

        // MONSTER
        vector<Monster*> monsterList;
        for (int i = 0; i < monsterQuantity; i++)
        {
            Monster* monster = new Monster(monsterTexture);
            monsterList.push_back(monster);
        }

        // INVENTORY
        Inventory playerInventory(player, dim);
        vector<Item*> mapItemList;

        // VIEW
        sf::View view(Vector2f(player.getPosition().x + (float)(dim / 2), player.getPosition().y + (float)(dim / 2)), Vector2f(windowWidth, windowHeight));
        view.zoom(1.f / zoom);

        // TILEMAP
        Tilemap map(dim);
        vector<Sprite> borders = map.getMapBorders();
        bool toggleHitBoxes = false;

        // CLOCK
        Clock clock;
        float dt = 0;

    #pragma endregion
    
    while (window.isOpen() && player.getEntityHP() > 0)
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
                    if (!isOnMount) { isAttacking = true; }
                    break;
                case Keyboard::H:
                    if (toggleHitBoxes) { toggleHitBoxes = false; }
                    else { toggleHitBoxes = true; }
                    break;
                case Keyboard::M:
                    if (isOnMount) { isOnMount = false; player.setDirection(playerDir); playerDir = { 0,0 }; }
                    else { isOnMount = true; player.setDirection(playerDir); playerDir = { 0,0 }; }
                    break;
                case Keyboard::P:
                    if (player.getEntityHP() < 200)
                    {
                        unsigned int i = 0; // unsigned pour éviter un warning
                        if (player.getInventory()[i] != 0)
                        {
                            while (player.getInventory()[i] != nullptr) { i++; }
                            player.setHP(player.getEntityHP() + player.getInventory().at(i - 1)->getHealAmount());
                            player.removeItem(i - 1);
                        }
                    }
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
                if (Keyboard::isKeyPressed(Keyboard::Z)) { poussee = 50000; }
                if (Keyboard::isKeyPressed(Keyboard::W)) { poussee = 50000; }
                if (Keyboard::isKeyPressed(Keyboard::Q)) { angle -= 2 * PI / 180; }
                if (Keyboard::isKeyPressed(Keyboard::A)) { angle -= 2 * PI / 180; }
                if (Keyboard::isKeyPressed(Keyboard::S)) { poussee = -500; }
                if (Keyboard::isKeyPressed(Keyboard::D)) { angle += 2 * PI / 180; }

                playerDir = { cos(angle), sin(angle) };

                // TEST DE COLLISION
                Vector2f newposX = player.getPosition() + Vector2f{ ((float)dim / 2),((float)dim / 2) } + Vector2f{ playerDir.x,0 };
                Vector2f newposY = player.getPosition() + Vector2f{ ((float)dim / 2),((float)dim / 2) } + Vector2f{ 0,playerDir.y };
                FloatRect newposRectX = FloatRect(newposX.x - dim / 2, newposX.y - dim / 2, dim, dim);
                FloatRect newposRectY = FloatRect(newposY.x - dim / 2, newposY.y - dim / 2, dim, dim);
                for (int i = 0; i < borders.size(); i++)
                {
                    if (newposRectX.intersects(borders[i].getGlobalBounds()))
                    {
                        player.setVelocityX(0);
                    }
                    if (newposRectY.intersects(borders[i].getGlobalBounds()))
                    {
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
                Vector2f newposX = player.getPosition() + Vector2f{ ((float)dim / 2),((float)dim / 2) } + Vector2f{ playerDir.x,0 };
                Vector2f newposY = player.getPosition() + Vector2f{ ((float)dim / 2),((float)dim / 2) } + Vector2f{ 0,playerDir.y };
                FloatRect newposRectX = FloatRect(newposX.x - dim / 2, newposX.y - dim / 2, dim, dim);
                FloatRect newposRectY = FloatRect(newposY.x - dim / 2, newposY.y - dim / 2, dim, dim);
                for (int i = 0; i < borders.size(); i++)
                {
                    if (newposRectX.intersects(borders[i].getGlobalBounds()))
                    {
                        playerDir.x = 0;
                    }
                    if (newposRectY.intersects(borders[i].getGlobalBounds()))
                    {
                        playerDir.y = 0;
                    }
                }

                player.setDirection(playerDir);
            }
        #pragma endregion

        #pragma region Hitboxes
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
                Vertex(Vector2f(((player.getPosition().x + 8) + (playerDir.x) * 20), ((player.getPosition().y + 8) + (playerDir.y) * 20)), Color::Blue)
            };
        #pragma endregion

        #pragma region Update
            // MONSTER
            for (int i = 0; i < monsterList.size(); i++)
            {
                if (monsterList[i]->isAlive())
                {
                    monsterList[i]->update(dt, player, isAttacking);
                }
                else
                {
                    Item* item = new Item();
                    item->setPosition(monsterList[i]->getPosition());
                    mapItemList.push_back(item);
                    monsterList.erase(monsterList.begin() + i);
                }
            }

            // ITEM
            for (int i = 0; i < mapItemList.size(); i++)
            {
                if (player.getSprite().getGlobalBounds().intersects(mapItemList[i]->getSprite().getGlobalBounds()))
                {
                    for (int j = 0; j < player.getInventory().size(); j++)
                    {
                        if (player.getInventory()[j] == nullptr)
                        {
                            player.addItem(mapItemList[i], j);
                            mapItemList.erase(mapItemList.begin() + i);
                            break;
                        }
                    }
                }
            }

            // PLAYER
            player.update(dt, isSprinting, isAttacking, isOnMount);
        #pragma endregion

        #pragma region Draw
            window.clear();

            // VIEW
            view.setCenter(Vector2f(player.getPosition().x + (float)(dim / 2), player.getPosition().y + (float)(dim / 2)));
            window.setView(view);

            // MAP
            map.drawTilemap(window);

            // DEBUG MODE
            if (toggleHitBoxes) { map.drawMapBorders(window); window.draw(pvertices, 4, Quads); }

            // MONSTER
            for (int i = 0; i < monsterList.size(); i++) { monsterList[i]->drawMonster(window); }

            // ITEM
            for (int i = 0; i < mapItemList.size(); i++) { mapItemList[i]->drawItem(window); }

            // PLAYER
            if (isOnMount) { window.draw(playerDirectionIndicator, 2, Lines); }
            player.drawPlayer(window, isAttacking);
            playerInventory.update(player, dim, window, windowWidth, windowHeight, zoom);
            playerInventory.drawInventory(window);

            window.display();
        #pragma endregion

        #pragma region Console
            ///*
            cout << "        fps | " + to_string(int(1 / dt)) + "\n" +
                    "         dt | " + to_string(dt) + "\n\n" +
                    " Position X | " + to_string(player.getPosition().x) + "\n" +
                    " Position Y | " + to_string(player.getPosition().y) + "\n\n" +
                    " Velocity X | " + to_string(player.getVelocity().x) + "\n" +
                    " Velocity Y | " + to_string(player.getVelocity().y) + "\n\n" +
                    "CONTROLES DISPONIBLES POUR LE MOMENT\n\n" +
                    "> ZQSD    : Deplacement\n" +
                    "> R_CTRL  : Degainer sa super baguette\n" +
                    "> L_SHIFT : Fuir tres vite\n" +
                    "> H       : Afficher les Hitboxes\n" +
                    "> M       : Utiliser sa monture\n" +
                    "> P       : Utiliser une potion" +
                    "\n\n\n\n\n\n\n\n\n\n\n\n";
            //*/
        #pragma endregion

        dt = clock.getElapsedTime().asSeconds();
    }
}

int main()
{
    #pragma region Variables
        int fpsCap = 144;
        float zoom = 5;
        float windowWidth = 1280;
        float windowHeight = 720;

        float playerHp = 200;
        float playerSpeed = 100;
        float playerSprintSpeed = 200;
        int monsterQuantity = 5;
        Vector2f spawnPos = { 416,196 };
    #pragma endregion
       
    game(fpsCap, zoom, windowWidth, windowHeight, playerHp, playerSpeed, playerSprintSpeed, spawnPos, monsterQuantity);

    #pragma region Endgame
        sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "RIP...");
        window.setKeyRepeatEnabled(false);
        window.setFramerateLimit(fpsCap);
        
        SoundBuffer buffer;
        buffer.loadFromFile("assets/End Credits.ogg");
        Sound sound;
        sound.setBuffer(buffer);
        sound.setVolume(50.f);
        sound.setLoop(true);
        sound.play();

        Texture endCreditTexture;
        endCreditTexture.loadFromFile("assets/sky.png");
        Sprite endCredit;
        endCredit.setTexture(endCreditTexture);

        while (window.isOpen())
        {
            Event event;
            while (window.pollEvent(event))
            {
                if (event.type == Event::Closed) { window.close(); }
            }
            window.clear();
            window.draw(endCredit);
            window.display();
        }
    #pragma endregion
}