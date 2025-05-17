#pragma once
#include "Button.h"
#include <vector>
#include <SFML/Graphics.hpp>

class PauseMenu {
private:
    static bool show_pausemenu;
    static Button resumeButton;
    static Button restartButton;
    static Button backButton;

public:
    static const int PAUSE_RESUME = 0;
    static const int PAUSE_BACK = 1;
    static const int PAUSE_NONE = -1;


    static int handlePauseMenuSelection();
    static void display_pausemenu(sf::RenderWindow& window);
    static bool is_pausemenu_shown() {return show_pausemenu;}
    static void toggle_pausemenu() {show_pausemenu = !show_pausemenu;}
};