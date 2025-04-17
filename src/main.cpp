#include <cmath>
#include <SFML/Graphics.hpp>
#include "events.h"
#include "Player.h"
#include "configuration.h"

int main() {
    sf::Clock clock;
    sf::Time time;

    Player player;

    auto window = sf::RenderWindow(sf::VideoMode(conf::window_size), "2dGame", sf::State::Fullscreen);

    if (conf::limit_framerate)
        window.setFramerateLimit(conf::max_framerate);

    sf::Text fps_text(conf::arial);
    std::stringstream ss;
    fps_text.setCharacterSize(30);
    fps_text.setFillColor(sf::Color::Red);
    fps_text.setPosition({conf::window_size_f.x - 170, 0});
    int frame = 0;
    float fps_array[conf::fps_accuracy];
    float fps_sum = 0;

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

        if (conf::show_FPS) {
            fps_sum += 1 / actual_dt;

            ss.str("");
            if (frame < conf::fps_accuracy) {
                ss<<"FPS: "<<std::round(fps_sum / frame);
            } else {
                fps_sum -= fps_array[frame%conf::fps_accuracy];
                ss<<"FPS: "<<std::round(fps_sum / conf::fps_accuracy);
            }

            fps_array[frame%conf::fps_accuracy] = 1 / actual_dt;

            fps_text.setString(ss.str().c_str());
            window.draw(fps_text);
        }

        window.display();

        frame++;
    }
}