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
#include "Sprinter.h"
#include "../cmake-build-release/_deps/sfml-src/src/SFML/Window/InputImpl.hpp"
#include "MainMenu.h"
#include "OptionsMenu.h"

int main() {
    sf::Clock clock;
    sf::Time time;

    auto window = sf::RenderWindow(sf::VideoMode(conf::window_size), "2dGame", sf::State::Windowed);

    if (conf::limit_framerate)
        window.setFramerateLimit(conf::max_framerate);

    MainMenu mainMenu;
    OptionsMenu optionsMenu;
    if (!mainMenu.load_resources() || !optionsMenu.load_resources()) {
        return -1;
    }

    bool showingOptions = false; //do sledzenia czy opcje czy menu glowne
    int menuResult = MainMenu::MENU_NONE;

    while (window.isOpen() && menuResult != MainMenu::MENU_PLAY && menuResult != MainMenu::MENU_EXIT) {
        processEvents(window);

        if (showingOptions) {
            optionsMenu.update(window);

            //back w options klikniete
            if (optionsMenu.handleMenuSelection() == OptionsMenu::OPTIONS_BACK) {
                showingOptions = false;
            }

            window.clear();
            optionsMenu.show(window);
            window.display();
        } else {
            mainMenu.update(window);
            menuResult = mainMenu.handleMenuSelection();

            if (menuResult == MainMenu::MENU_OPTIONS) {
                showingOptions = true;
                menuResult = MainMenu::MENU_NONE;  //reset petli
            }

            window.clear();
            mainMenu.show(window);
            window.display();
        }

        if (menuResult == MainMenu::MENU_EXIT) {
            window.close();
            return 0;
        }
    }

    if (menuResult == MainMenu::MENU_PLAY) {
        Player player(-1000, -100);

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
        obstacles.push_back(*(new Obstacle(0, 1100, 3000, 2000)));
        obstacles.push_back(*(new Obstacle(-400, 1200, 3000, 2000)));

        if (!obstacles[0].load_texture(conf::wallImage)) {
            return -1;
        }
        if (!obstacles[1].load_texture(conf::wallImage)) {
            return -1;
        }


        //std::vector<Enemy*> enemies;
        //enemies.push_back(new Archer(-400, -500));

        // for (const auto& enemy : enemies) {
        //     if (!(*enemy).load_textures()) {
        //         return -1;
        //     }
        // }


        Stalker stalker(-400, -500);

        if (!stalker.load_textures()) {
            return -1;
        }


        Archer archer(-400, -500);

        if (!archer.load_textures()) {
            return -1;
        }


        Sprinter sprinter(-400, -500);

        if (!sprinter.load_textures()) {
            return -1;
        }


        sf::Text test_text(conf::arial);
        test_text.setCharacterSize(100);
        test_text.setString("9999999999");

        sf::Text mouse_pos_x(conf::arial);
        mouse_pos_x.setCharacterSize(100);
        mouse_pos_x.setPosition({1600, 0});


        sf::View player_view({player.getPosition().x, player.getPosition().y - 200}, conf::window_size_f);
        //window.setView(player_view);

        time = clock.restart();
        float actual_dt = conf::dt;

        while (window.isOpen())
        {
            // Logic
            //actual_dt = conf::dt;

            processEvents(window);

            player.update(obstacles, actual_dt);
            //enemy.update(player, obstacles, actual_dt);
            //stalker.update(player, obstacles, actual_dt);
            //archer.update(player, obstacles, actual_dt);
            sprinter.update(player, obstacles, actual_dt);

            // for (const auto& enemy : enemies) {
            //     (*enemy).update(player, obstacles, actual_dt);
            // }


            std::stringstream ss;
            ss<<sf::priv::InputImpl::getMousePosition().x - 10;
            mouse_pos_x.setString(ss.str().c_str());

            player_view.setCenter({player.getPosition().x, player.getPosition().y - 200});

            // Display

            window.clear();

            window.setView(window.getDefaultView());

            // Background view -----------------

            window.draw(background1);

            //-----------------------------------

            window.setView(player_view);

            // Player view ----------------------

            obstacles[1].show(window);
            obstacles[0].show(window);

            //enemy.show(window);
            //stalker.show(window);
            //archer.show(window);
            sprinter.show(window);
            player.show(window);

            // for (const auto& enemy : enemies) {
            //     (*enemy).show(window);
            // }

            //-----------------------------------

            window.setView(window.getDefaultView());

            // Foreground view -----------------

            HUD::display_hud(window, actual_dt, player);




            // CHARACTER LENGTH TEST
            //window.draw(test_text);
            //window.draw(mouse_pos_x);

            //-----------------------------------

            window.display();

            time = clock.restart();
            actual_dt = time.asSeconds();
        }

        // for (auto enemy : enemies) {
        //     delete enemy;
        // }
    }
}
