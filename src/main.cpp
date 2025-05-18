#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>
#include "Archer.h"
#include "events.h"
#include "Player.h"
#include "configuration.h"
#include "Editor.h"
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
#include "CheckpointManager.h"

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
    LevelHandler::change_level(1);


    sf::Text test_text(conf::arial);
    test_text.setCharacterSize(100);
    test_text.setString("eeeeeeeeeeW");

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

        Editor::update(player);

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
        } else if (menuResult == MainMenu::MENU_PLAY) {
            // Logic

            processEvents(window);

            pauseMenuResult = PauseMenu::handlePauseMenuSelection();

            if (pauseMenuResult == PauseMenu::PAUSE_RESUME && LevelHandler::getEnemiesNumber() > 0) {
                player.update(LevelHandler::getObstacles(), actual_dt);

                LevelHandler::update(player, LevelHandler::getObstacles(), actual_dt);

                if (player.isDead() || isKeyPressed(sf::Keyboard::Key::R)) {
                    if (LevelHandler::loadFromLastCheckpoint()) {
                        std::cout<<"Load from last checkpoint"<<std::endl;
                    }
                    else {
                        std::cout<< "brak zapisanego checkpointu" << std::endl;
                        player.respawn();
                    }
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

            player.show(window);

            LevelHandler::show(window);

            //-----------------------------------

            window.setView(window.getDefaultView());

            // Foreground view -----------------

            HUD::display_hud(window, actual_dt, player);
            PauseMenu::display_pausemenu(window);

            LevelHandler::checkpoint_manager.drawMessage(window);

            LevelHandler::shop_keeper.show(window);


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
    if (conf::edit_mode_enabled)
        Editor::print_scripts();
    LevelHandler::unload();
}
