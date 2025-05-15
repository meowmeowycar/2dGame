#include "MainMenu.h"
#include "configuration.h"
#include "Button.h"
#include <iostream>
#include "ImageDisplay.h"

MainMenu::MainMenu() : title(conf::arial , "2D GAME", 30) {
    Button play_button(300, 80, "PLAY");
    play_button.setPosition(conf::window_size_f.x / 2.0f, conf::window_size_f.y / 2.0f - 100);
    play_button.setColor(sf::Color(70, 70, 70, 200));
    play_button.setTextColor(sf::Color::White);
    play_button.setTextSize(40);
    buttons.push_back(play_button);

    Button options_button(300, 80, "OPTIONS");
    options_button.setPosition(conf::window_size_f.x / 2.0f, conf::window_size_f.y / 2.0f);
    options_button.setColor(sf::Color(70, 70, 70, 200));
    options_button.setTextColor(sf::Color::White);
    options_button.setTextSize(40);
    buttons.push_back(options_button);

    Button exit_button(300, 80, "EXIT");
    exit_button.setPosition(conf::window_size_f.x / 2.0f, conf::window_size_f.y / 2.0f + 100);
    exit_button.setColor(sf::Color(70, 70, 70, 200));
    exit_button.setTextColor(sf::Color::White);
    exit_button.setTextSize(40);
    buttons.push_back(exit_button);

    sf::FloatRect textRect  = title.getLocalBounds();
    title.setCharacterSize(50);
    title.setFillColor(sf::Color::Black);
    title.setOrigin({textRect.size.x / 2.0f, textRect.size.y / 2.0f});
    title.setPosition({conf::window_size_f.x / 2.0f - 50, conf::window_size_f.y / 2.0f - 250});
}

bool MainMenu::load_resources() {
    if (!Obrazek(conf::mainMenuBackgroundImage, background_texture)) {
        std::cerr << "Nied mozna zalodawc tla menui" << std::endl;
        return false;
    }

    return true;
}

void MainMenu::update(sf::RenderWindow& window) {
    for (auto& button : buttons) {
        button.update(window);
    }
}

void MainMenu::show(sf::RenderWindow& window) {
    sf::Sprite background(background_texture);
    background.setScale({conf::window_size_f.x / background_texture.getSize().x, conf::window_size_f.y / background_texture.getSize().y});

    window.draw(background);
    window.draw(title);

    for (auto& button : buttons) {
        button.show(window);
    }
}

int MainMenu::handleMenuSelection() {
    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i].isReleased()) {
            return i;
        }
    }
    return MENU_NONE;
}

