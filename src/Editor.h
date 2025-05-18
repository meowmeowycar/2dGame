#pragma once
#include "Player.h"

class Editor {
    static bool mouse_clicked;
    static bool F_clicked;

    static sf::Vector2f pos1, pos2;

    static std::vector<std::string> obstacles_scripts;
    static std::vector<std::string> enemies_scripts;

    static std::string type;
public:
    static void update(Player& player);
    static void display_grid(int cell_size, Player& player, sf::RenderWindow& window);
    static void reset(int number_of_obstacles, int number_of_enemies);
    static void print_scripts();
    static void display_mouse_pos(Player& player, sf::RenderWindow& window);
};
