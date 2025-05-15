#include "MainMenu.h"
#include "configuration.h"
#include "Button.h"
#include <iostream>
#include "ImageDisplay.h"
#include "OptionsMenu.h"

OptionsMenu::OptionsMenu() : MainMenu() {

    buttons.clear();

    Button back_button(300, 80, "BACK");
    back_button.setPosition(conf::window_size_f.x / 2.0f, conf::window_size_f.y / 2.0f + 150);
    back_button.setColor(sf::Color(70, 70, 70, 200));
    back_button.setTextColor(sf::Color::White);
    back_button.setTextSize(40);
    buttons.push_back(back_button);

}
bool OptionsMenu::load_resources() {

    if (!Obrazek(conf::optionsMenuBackgroundImage, background_texture)) {
        std::cerr << "Nie mozna zaladowac tla menu opcji" << std::endl;
        return false;
    }

    return true;

}
void OptionsMenu::update(sf::RenderWindow& window) {

    for (auto& button : buttons) {
        button.update(window);
    }

}

void OptionsMenu::show(sf::RenderWindow& window) {
    sf::Sprite background(background_texture);
    background.setScale({conf::window_size_f.x / background_texture.getSize().x, conf::window_size_f.y / background_texture.getSize().y});

    window.draw(background);

    for (auto& button : buttons) {
        button.show(window);
    }

}

int OptionsMenu::handleMenuSelection() {
    for (int i = 0; i < buttons.size(); i++) {
        if (buttons[i].isReleased()) {
            return i;
        }
    }
    return OPTIONS_NONE;
}