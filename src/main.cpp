#include <SFML/Graphics.hpp>
#include "ImageDisplay.h"

int main()
{
    sf:: Texture backgroundTexture;
    if (!Obrazek("../../Media/Ludzik.png", backgroundTexture)) {
        return -1;
    }
    sf::Sprite Spirite(backgroundTexture);

    auto window = sf::RenderWindow(sf::VideoMode({640u, 480u}), "Game");
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear(sf::Color::Red);
        window.draw(Spirite);
        window.display();
    }
}