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

        float speed = 20.f;
        sf::Vector2f v;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){window.close();}  
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                    case Keyboard::Z:
                        v.y -= speed;
                        entity.move(v);
                        break;
                    case Keyboard::Q:
                        v.x -= speed;
                        entity.move(v);
                        break;
                    case Keyboard::S:
                        v.y += speed;
                        entity.move(v);
                        break;
                    case Keyboard::D:
                        v.x += speed;
                        entity.move(v);
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