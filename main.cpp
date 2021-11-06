#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>

#include "Tilemap.h"
#include "Entity.h"
#include "Player.h"

using namespace sf;
using namespace std;

int main()
{
    // Variables modifiables
    int scale = 4;
    float playerSpeed = 0.5;
    
    #pragma region INIT

        int dim = 16; // Fixe (lié à foresttiles2-t.png)
        sf::RenderWindow window(sf::VideoMode((dim*scale*12), (dim*scale*8)), "The game seems to be working..."); // La map possede 12 colones et 8 lignes
        window.setKeyRepeatEnabled(false);

        Player player(scale);
        player.setSpeed(playerSpeed);

        Tilemap map(dim,scale);

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

        #pragma region PlayerMovement
            if (Keyboard::isKeyPressed(Keyboard::Z)) { player.setVelocityY(-player.getSpeed()); }
            if (Keyboard::isKeyPressed(Keyboard::Q)) { player.setVelocityX(-player.getSpeed()); }
            if (Keyboard::isKeyPressed(Keyboard::S)) { player.setVelocityY(player.getSpeed()); }
            if (Keyboard::isKeyPressed(Keyboard::D)) { player.setVelocityX(player.getSpeed()); }
        #pragma endregion

        #pragma region Draw
            window.clear();
            map.drawTilemap(window);
            player.drawPlayer(window);
            window.display();
        #pragma endregion
    }
}
