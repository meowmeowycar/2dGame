#pragma once
#include "Button.h"
#include <vector>
#include <SFML/Graphics.hpp>

class PauseMenu {
private:
    static bool show_pausemenu;
    static std::vector<Button> pauseButtons;

public:
    static const int PAUSE_RESUME = 0;
    static const int PAUSE_EXIT = 1;
    static const int PAUSE_NONE = -1;


    static void toggle_pausemenu();
    static void display_pausemenu(sf::RenderWindow& window);
    static bool is_pausemenu_shown() {return show_pausemenu;}
};