#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "Archer.h"
#include "events.h"
#include "Player.h"
#include "configuration.h"
#include "ImageDisplay.h"
#include "Obstacle.h"
#include "HUD.h"
#include "Entity.h"
#include "Stalker.h"
#include "Enemy.h"
#include "Semi_obstacle.h"
#include "Sprinter.h"
#include "../cmake-build-release/_deps/sfml-src/src/SFML/Window/InputImpl.hpp"
#include "MainMenu.h"
#include "OptionsMenu.h"
#include "PauseMenu.h"

int main() {
    auto window = sf::RenderWindow(sf::VideoMode(conf::window_size), "2dGame", sf::State::Windowed);

    if (conf::limit_framerate)
        window.setFramerateLimit(conf::max_framerate);

    sf::Clock clock;
    sf::Time time;

    Player player(-1000, -500 - conf::player_hitbox.y / 2);

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

    std::vector<Obstacle*> obstacles;
    obstacles.push_back(new Obstacle(-400, 1200, 3000, 2000));
    obstacles.push_back(new Obstacle(0, 1100, 3000, 2000));
    obstacles.push_back(new Obstacle(-100, -200, 50, 400));
    obstacles.push_back(new Semi_obstacle(-800, -20, 500, 50));

    for (const auto& obstacle : obstacles) {
        if (!(*obstacle).load_texture()) {
            return -1;
        }
    }


    std::vector<Enemy*> enemies;
    enemies.push_back(new Archer(-400, -500));
    enemies.push_back(new Sprinter(-400, -500));
    enemies.push_back(new Stalker(-400, -500));

    for (const auto& enemy : enemies) {
        if (!(*enemy).load_textures()) {
            return -1;
        }
    }


    sf::Text test_text(conf::arial);
    test_text.setCharacterSize(100);
    test_text.setString("          WWW");

    sf::Text mouse_pos_x(conf::arial);
    mouse_pos_x.setCharacterSize(100);
    mouse_pos_x.setPosition({1600, 0});


    sf::View player_view({player.getPosition().x, player.getPosition().y - 200}, conf::window_size_f);

    time = clock.restart();
    float actual_dt = conf::dt;

    MainMenu mainMenu;
    OptionsMenu optionsMenu;
    if (!mainMenu.load_resources() || !optionsMenu.load_resources()) {
        return -1;
    }

    int menuResult = MainMenu::MENU_NONE;
    int pauseMenuResult = PauseMenu::PAUSE_RESUME;

    while (window.isOpen()) {
        processEvents(window);

        if (menuResult == MainMenu::MENU_NONE) {
            mainMenu.update(window);
            menuResult = mainMenu.handleMenuSelection();

            window.clear();
            mainMenu.show(window);
            window.display();
        } else if (menuResult == MainMenu::MENU_OPTIONS) {
            optionsMenu.update(window);

            //back w options klikniete
            if (optionsMenu.handleMenuSelection() == OptionsMenu::OPTIONS_BACK) {
                menuResult = MainMenu::MENU_NONE;
            }

            window.clear();
            optionsMenu.show(window);
            window.display();
        } else if (menuResult == MainMenu::MENU_EXIT) {
            window.close();
            return 0;
        } else if (menuResult == MainMenu::MENU_PLAY) {
            // Logic

            //actual_dt = conf::dt;

            processEvents(window);

            pauseMenuResult = PauseMenu::handlePauseMenuSelection();

            if (pauseMenuResult == PauseMenu::PAUSE_RESUME) {
                player.update(obstacles, actual_dt);

                for (const auto& enemy : enemies) {
                    (*enemy).update(player, obstacles, actual_dt);
                }


                std::stringstream ss;
                ss<<sf::priv::InputImpl::getMousePosition().x - 10;
                mouse_pos_x.setString(ss.str().c_str());

                player_view.setCenter({player.getPosition().x, player.getPosition().y - 200});
            } else if (pauseMenuResult == PauseMenu::PAUSE_BACK) {
                menuResult = MainMenu::MENU_NONE;
            }

            // Display

            window.clear();

            window.setView(window.getDefaultView());

            // Background view -----------------

            window.draw(background1);

            //-----------------------------------

            window.setView(player_view);

            // Player view ----------------------

            for (const auto& obstacle : obstacles) {
                (*obstacle).show(window);
            }

            player.show(window);

            for (const auto& enemy : enemies) {
                (*enemy).show(window);
            }

            //-----------------------------------

            window.setView(window.getDefaultView());

            // Foreground view -----------------

            HUD::display_hud(window, actual_dt, player);
            PauseMenu::display_pausemenu(window);


            // CHARACTER LENGTH TEST
            //window.draw(test_text);
            //window.draw(mouse_pos_x);

            //-----------------------------------

            window.display();

            time = clock.restart();
            actual_dt = time.asSeconds();
        }
    }

    for (auto enemy : enemies) {
        delete enemy;
    }

    for (auto obstacle : obstacles) {
        delete obstacle;
    }
}
