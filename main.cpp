#include <SFML/Graphics.hpp>

using namespace sf;

int main()
{
    #pragma region INIT
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");
    sf::RectangleShape entity(sf::Vector2f(100.f, 100.f));
    Texture texture;
    texture.loadFromFile("ghost.png");
    Sprite sprite;
    entity.setTexture(&texture);
    #pragma endregion

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){window.close();}  
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case Keyboard::Z:
                        entity.move(sf::Vector2f(0.f, -20.f));
                        break;
                    case Keyboard::Q:
                        entity.move(sf::Vector2f(-20.f, 0.f));
                        break;
                    case Keyboard::S:
                        entity.move(sf::Vector2f(0.f, 20.f));
                        break;
                    case Keyboard::D:
                        entity.move(sf::Vector2f(20.f, 0.f));
                        break;
                }
            }
        }

        window.clear();
        window.draw(entity);
        window.draw(sprite);
        window.display();
    }

    return 0;
}
/*
float speed = 0.f;
sf::Vector2f v;
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    v.y -= speed;
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    v.y += speed;
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    v.x -= speed;
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    v.x += speed;
*/