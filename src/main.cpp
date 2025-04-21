#include <SFML/Graphics.hpp>
#include "events.h"
#include "Player.h"
#include "configuration.h"
#include "FPS.h"
#include "ImageDisplay.h"

int main() {
    sf::Clock clock;
    sf::Time time;

    Player player;

    if (!player.load_textures()) {
        return -1;
    }

    auto window = sf::RenderWindow(sf::VideoMode(conf::window_size), "2dGame", sf::State::Fullscreen);

    sf::Texture background1_textrue;
    if (!Obrazek(conf::backgroundImage, background1_textrue)) {
        return -1;
    }
    sf::Sprite background1(background1_textrue);

    if (conf::limit_framerate)
        window.setFramerateLimit(conf::max_framerate);


    sf::View player_view(player.getPosition(), conf::window_size_f);
    //window.setView(player_view);

    while (window.isOpen())
    {
        // Logic

        time = clock.restart();
        float actual_dt = time.asSeconds();

        processEvents(window);


        player.update(conf::dt);

        player_view.setCenter(player.getPosition());

        // Display

        window.clear();

        window.setView(window.getDefaultView());

        // Background view -----------------

        window.draw(background1);

        if (conf::show_FPS)
            FPS::show_fps(window, actual_dt);

        //-----------------------------------

        window.setView(player_view);

        // Player view ----------------------

        player.show(window);
        player.draw_hitbox(window);

        window.display();
    }
}