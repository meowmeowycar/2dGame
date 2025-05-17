#include <cmath>
#include <iostream>
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
#include "LevelHandler.h"
#include "Semi_obstacle.h"
#include "Sprinter.h"
#include "../cmake-build-release/_deps/sfml-src/src/SFML/Window/InputImpl.hpp"
#include "MainMenu.h"
#include "OptionsMenu.h"
#include "PauseMenu.h"

int main() {
    auto window = sf::RenderWindow(sf::VideoMode(conf::window_size), "2dGame", sf::State::Fullscreen);

    window.setMouseCursorVisible(false);

    if (conf::limit_framerate)
        window.setFramerateLimit(conf::max_framerate);

    sf::Clock clock;
    sf::Time time;

    sf::Texture cursor_texture;
    if (!Obrazek(conf::cursorImage, cursor_texture))
        return -1;
    sf::Sprite cursor(cursor_texture);
    float cursor_scale = 0.15;
    cursor.setScale({cursor_scale, cursor_scale});

    Player player(0, -conf::player_hitbox.y / 2);

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


    if (!LevelHandler::load_textures()) {
        return -1;
    }

    LevelHandler::reference_player(player);
    //LevelHandler::change_level(1);
    LevelHandler::load_level();


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

    float clicked = false;

    while (window.isOpen()) {
        processEvents(window);

        if (conf::edit_mode_enabled) {

            float x1, y1;

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                x1 = sf::priv::InputImpl::getMousePosition().x - conf::window_size_f.x / 2 + player.getPosition().x;
                y1 = sf::priv::InputImpl::getMousePosition().y - (conf::window_size_f.y / 2 + 200) + player.getPosition().y;
            }

            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
            {
                float x2, y2;
                x2 = sf::priv::InputImpl::getMousePosition().x - conf::window_size_f.x / 2 + player.getPosition().x;
                y2 = sf::priv::InputImpl::getMousePosition().y - (conf::window_size_f.y / 2 + 200) + player.getPosition().y;

                x1 = round(x1 / 25) * 25;
                y1 = round(y1 / 25) * 25;
                x2 = round(x2 / 25) * 25;
                y2 = round(y2 / 25) * 25;

                if (!clicked) {
                    std::cout<<"    obstacles.push_back(new Obstacle("<<x1<<", "<<y1<<", "<<x2<<", "<<y2<<"));"<<std::endl;
                    LevelHandler::addObstacle(x1, y1, x2, y2);
                }
                clicked = true;
            } else
                clicked = false;
        }

        sf::Vector2f mouse_position = static_cast<sf::Vector2f>(sf::priv::InputImpl::getMousePosition());
        cursor.setPosition(sf::Vector2f(mouse_position.x - 60 * cursor_scale, mouse_position.y - 1));

        if (menuResult == MainMenu::MENU_NONE) {
            mainMenu.update(window);
            menuResult = mainMenu.handleMenuSelection();

            window.clear();
            mainMenu.show(window);
            window.draw(cursor);
            window.display();
        } else if (menuResult == MainMenu::MENU_OPTIONS) {
            optionsMenu.update(window);

            //back w options klikniete
            if (optionsMenu.handleMenuSelection() == OptionsMenu::OPTIONS_BACK) {
                menuResult = MainMenu::MENU_NONE;
            }

            window.clear();
            optionsMenu.show(window);
            window.draw(cursor);
            window.display();
        } else if (menuResult == MainMenu::MENU_EXIT) {
            window.close();
            return 0;
        } else if (menuResult == MainMenu::MENU_PLAY) {
            // Logic

            processEvents(window);

            pauseMenuResult = PauseMenu::handlePauseMenuSelection();

            if (pauseMenuResult == PauseMenu::PAUSE_RESUME) {
                player.update(LevelHandler::getObstacles(), actual_dt);

                LevelHandler::update(player, LevelHandler::getObstacles(), actual_dt);

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

            player.show(window);

            LevelHandler::show(window);

            //-----------------------------------

            window.setView(window.getDefaultView());

            // Foreground view -----------------

            HUD::display_hud(window, actual_dt, player);
            PauseMenu::display_pausemenu(window);


            // CHARACTER LENGTH TEST
            //window.draw(test_text);
            //window.draw(mouse_pos_x);

            window.draw(cursor);

            //-----------------------------------

            window.display();
        }

        time = clock.restart();
        actual_dt = time.asSeconds();
    }

    LevelHandler::unload();
}
