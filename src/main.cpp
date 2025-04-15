#include <SFML/Graphics.hpp>
#include "events.h"

int main()
{
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project", sf::State::Fullscreen);
    window.setFramerateLimit(144);

    while (window.isOpen())
    {
        processEvents(window);

        window.clear(sf::Color::Red);
        window.display();
    }
}