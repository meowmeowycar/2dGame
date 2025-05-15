#pragma once
#include "MainMenu.h"


class OptionsMenu : public MainMenu {
public :
    static const int OPTIONS_NONE = -1;
    static const int OPTIONS_BACK = 0;

    OptionsMenu();

    //override
    bool load_resources();
    //override
    void update(sf::RenderWindow& window);
    //override
    void show(sf::RenderWindow& window);
    //override
    int handleMenuSelection();
};
