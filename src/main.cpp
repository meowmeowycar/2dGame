#include <SFML/Graphics.hpp>
#include "events.h"
#include "Player.h"
#include "configuration.h"

int main() {
    sf::Clock clock;
    sf::Time time;

    Player player;

    auto window = sf::RenderWindow(sf::VideoMode(conf::window_size), "Game", sf::State::Fullscreen);
    window.setFramerateLimit(conf::max_framerate);

    while (window.isOpen())
    {
        time = clock.restart();
        float dt = time.asSeconds();

        processEvents(window);

        player.update(conf::dt);

        window.clear(sf::Color::Red);

        if (!player.show(window)) {
            return -1;
        }

        window.display();
    }
}