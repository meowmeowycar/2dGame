#include "Editor.h"

#include <cmath>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "configuration.h"
#include "LevelHandler.h"
#include "../cmake-build-release/_deps/sfml-src/src/SFML/Window/InputImpl.hpp"


bool Editor::mouse_clicked = false;
bool Editor::F_clicked = false;

sf::Vector2f Editor::pos1;
sf::Vector2f Editor::pos2;

std::string Editor::type = "obstacle";

std::vector<std::string> Editor::obstacles_scripts;
std::vector<std::string> Editor::enemies_scripts;

void Editor::update(Player& player) {
    if (conf::edit_mode_enabled) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
        {
            pos1.x = sf::priv::InputImpl::getMousePosition().x - conf::window_size_f.x / 2 + player.getPosition().x;
            pos1.y = sf::priv::InputImpl::getMousePosition().y - (conf::window_size_f.y / 2 + 200) + player.getPosition().y;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
        {
            pos2.x = sf::priv::InputImpl::getMousePosition().x - conf::window_size_f.x / 2 + player.getPosition().x;
            pos2.y = sf::priv::InputImpl::getMousePosition().y - (conf::window_size_f.y / 2 + 200) + player.getPosition().y;

            pos1.x = round(pos1.x / 25) * 25;
            pos1.y = round(pos1.y / 25) * 25;
            pos2.x = round(pos2.x / 25) * 25;
            pos2.y = round(pos2.y / 25) * 25;

            if (!mouse_clicked) {
                std::stringstream script;
                if (type == "semi_obstacle") {
                    script<<"    obstacles.push_back(new Semi_obstacle("<<pos1.x<<", "<<pos1.y<<", "<<pos2.x<<", "<<pos2.y<<"));"<<std::endl;
                    obstacles_scripts.push_back(script.str().c_str());
                    LevelHandler::addSemiObstacle(pos1.x, pos1.y, pos2.x, pos2.y);
                } else if (type == "obstacle") {
                    script<<"    obstacles.push_back(new Obstacle("<<pos1.x<<", "<<pos1.y<<", "<<pos2.x<<", "<<pos2.y<<"));"<<std::endl;
                    obstacles_scripts.push_back(script.str().c_str());
                    LevelHandler::addObstacle(pos1.x, pos1.y, pos2.x, pos2.y);
                } else if (type == "stalker") {
                    script<<"    enemies.push_back(new Stalker("<<pos2.x<<", "<<pos2.y<<"));"<<std::endl;
                    enemies_scripts.push_back(script.str().c_str());
                    LevelHandler::addStalker(pos2.x, pos2.y);
                } else if (type == "archer") {
                    script<<"    enemies.push_back(new Archer("<<pos2.x<<", "<<pos2.y<<"));"<<std::endl;
                    enemies_scripts.push_back(script.str().c_str());
                    LevelHandler::addArcher(pos2.x, pos2.y);
                } else if (type == "sprinter") {
                    script<<"    enemies.push_back(new Sprinter("<<pos2.x<<", "<<pos2.y<<"));"<<std::endl;
                    enemies_scripts.push_back(script.str().c_str());
                    LevelHandler::addSprinter(pos2.x, pos2.y);
                }
            }
            mouse_clicked = true;
        } else
            mouse_clicked = false;


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F)) {
            if (!F_clicked) {
                sf::Vector2f mouse_pos;

                mouse_pos.x = sf::priv::InputImpl::getMousePosition().x - conf::window_size_f.x / 2 + player.getPosition().x;
                mouse_pos.y = sf::priv::InputImpl::getMousePosition().y - (conf::window_size_f.y / 2 + 200) + player.getPosition().y;

                if (!LevelHandler::removeEnemy(mouse_pos, enemies_scripts))
                    LevelHandler::removeObstacle(mouse_pos, obstacles_scripts);
            }
            F_clicked = true;
        } else
            F_clicked = false;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1)) {
            type = "obstacle";
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2)) {
            type = "semi_obstacle";
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3)) {
            type = "stalker";
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num4)) {
            type = "archer";
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num5)) {
            type = "sprinter";
        }
    }
}

void Editor::display_grid(int cell_size, Player& player, sf::RenderWindow& window) {
    for (int i = (int)(conf::window_size_f.x / 2 - player.getPosition().x) % cell_size; i < conf::window_size_f.x; i += cell_size) {
        sf::RectangleShape line1;
        line1.setPosition({(float)i, 0});
        line1.setSize({1, conf::window_size_f.y});
        line1.setFillColor(sf::Color(255, 255, 255, 25));

        window.draw(line1);
    }

    for (int i = (int)(conf::window_size_f.y / 2 - player.getPosition().y) % cell_size; i < conf::window_size_f.y; i += cell_size) {
        sf::RectangleShape line2;
        line2.setPosition({0, (float)i});
        line2.setSize({conf::window_size_f.x, 1});
        line2.setFillColor(sf::Color(255, 255, 255, 25));

        window.draw(line2);
    }
}

void Editor::reset(int number_of_obstacles, int number_of_enemies) {
    obstacles_scripts.clear();
    enemies_scripts.clear();

    for (int i = 0; i < number_of_obstacles; i++) {
        obstacles_scripts.push_back("obstacle_none");
    }

    for (int i = 0; i < number_of_enemies; i++) {
        enemies_scripts.push_back("enemy_none");
    }
}

void Editor::print_scripts() {
    for (auto& obstacles_script : obstacles_scripts) {
        std::cout << obstacles_script << std::endl;
    }

    for (auto& enemies_script : enemies_scripts) {
        std::cout << enemies_script << std::endl;
    }
}

void Editor::display_mouse_pos(Player& player, sf::RenderWindow& window) {
    sf::Vector2f mouse_pos;

    mouse_pos.x = sf::priv::InputImpl::getMousePosition().x - conf::window_size_f.x / 2 + player.getPosition().x;
    mouse_pos.y = sf::priv::InputImpl::getMousePosition().y - (conf::window_size_f.y / 2 + 200) + player.getPosition().y;


    mouse_pos.x = round(mouse_pos.x / 25) * 25;
    mouse_pos.y = round(mouse_pos.y / 25) * 25;

    std::stringstream mouse_string;
    mouse_string<<"x: "<<mouse_pos.x<<", y: "<<mouse_pos.y<<std::endl;

    sf::Text mouse_text(conf::arial);
    mouse_text.setString(mouse_string.str().c_str());
    mouse_text.setPosition({conf::window_size_f.x - 500, 0});
    mouse_text.setFillColor(sf::Color::Yellow);

    window.draw(mouse_text);
}

