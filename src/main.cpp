#include <SFML/Graphics.hpp>
#include "events.h"
#include "Player.h"
#include "configuration.h"
#include "ImageDisplay.h"
#include "Obstacle.h"
#include "HUD.h"

int main() {
    sf::Clock clock;
    sf::Time time;

    Player player(-1000, -1000);

    if (!player.load_textures()) {
        return -1;
    }

    if (!HUD::load_graphics()) {
        return -1;
    }

    sf::Texture background1_textrue;
    if (!Obrazek(conf::backgroundImage, background1_textrue)) {
        return -1;
    }
    sf::Sprite background1(background1_textrue);

    std::vector<Obstacle> obstacles;
    obstacles.push_back(*(new Obstacle(0, 1700, 3000, 2000)));

    if (!obstacles[0].load_texture(conf::wallImage)) {
        return -1;
    }

    auto window = sf::RenderWindow(sf::VideoMode(conf::window_size), "2dGame", sf::State::Fullscreen);

    if (conf::limit_framerate)
        window.setFramerateLimit(conf::max_framerate);

    sf::View player_view({player.getPosition().x, player.getPosition().y - 200}, conf::window_size_f);
    //window.setView(player_view);

    while (window.isOpen())
    {
        // Logic

        time = clock.restart();
        float actual_dt = time.asSeconds();

        processEvents(window);

        player.update(obstacles, actual_dt);

        player_view.setCenter({player.getPosition().x, player.getPosition().y - 200});

        // Display

        window.clear();

        window.setView(window.getDefaultView());

        // Background view -----------------

        window.draw(background1);

        if (conf::show_hud)
            HUD::display_hud(window, actual_dt, player);

        //-----------------------------------

        window.setView(player_view);

        // Player view ----------------------

        player.show(window);
        player.draw_hitbox(window);

        obstacles[0].show(window);
        obstacles[0].draw_hitbox(window);

        window.display();
    }
}