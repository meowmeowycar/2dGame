#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Button.h"

class MainMenu {
protected:
    sf::Texture background_texture;
    std::vector<Button> buttons;
    sf::Text title;

public:

    static const int MENU_PLAY = 0;
    static const int MENU_OPTIONS = 1;
    static const int MENU_EXIT = 2;
    static const int MENU_NONE = -1;

    MainMenu();
    ///~MainMenu(); jakby ktos chcial hehe

    bool load_resources();
    void update(sf::RenderWindow& window);
    void show(sf::RenderWindow& window);

    int handleMenuSelection();

};