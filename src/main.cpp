#include <SFML/Graphics.hpp>
#include "events.h"
#include "Player.h"
#include "configuration.h"
#include "FPS.h"

int main() {
    sf::Clock clock;
    sf::Time time;

    Player player;

    auto window = sf::RenderWindow(sf::VideoMode(conf::window_size), "2dGame", sf::State::Fullscreen);

    if (conf::limit_framerate)
        window.setFramerateLimit(conf::max_framerate);

    while (window.isOpen())
    {
        time = clock.restart();
        float actual_dt = time.asSeconds();

        processEvents(window);

        player.update(conf::dt);

        window.clear(sf::Color::White);

        if (!player.show(window)) {
            return -1;
        }

        if (conf::show_FPS)
            FPS::show_fps(window, actual_dt);

        window.display();
    }
}