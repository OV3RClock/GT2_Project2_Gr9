#include <SFML/Graphics.hpp>
using namespace sf;
int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!");
    sf::CircleShape shape(50);
    sf::CircleShape carre(80, 3);

    shape.setFillColor(sf::Color::Red);
    shape.setOutlineThickness(10);
    shape.setOutlineColor(sf::Color::Green);
    Texture texture;
    //texture.loadFromFile("ghost.png");
    carre.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(shape);
        window.draw(carre);
        window.display();
    }

    return 0;
}