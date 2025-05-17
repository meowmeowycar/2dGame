#include "PauseMenu.h"

#include <iostream>

#include "configuration.h"
#include "Button.h"
#include <SFML/Graphics.hpp>

#include "LevelHandler.h"

bool PauseMenu::show_pausemenu = false;

Button PauseMenu::resumeButton(conf::window_size_f.x / 2.0f, conf::window_size_f.y / 2.0f - 100, 400, 80, "RESUME");

Button PauseMenu::restartButton(conf::window_size_f.x / 2.0f, conf::window_size_f.y / 2.0f, 400, 80, "RESTART LEVEL");

Button PauseMenu::backButton(conf::window_size_f.x / 2.0f, conf::window_size_f.y / 2.0f + 100, 400, 80, "MAIN MENU");


void PauseMenu::display_pausemenu(sf::RenderWindow& window) {

    if (!show_pausemenu) return;

    resumeButton.setColor(sf::Color(70, 70, 70, 200));
    resumeButton.setTextColor(sf::Color::White);
    resumeButton.setTextSize(40);

    restartButton.setColor(sf::Color(70, 70, 70, 200));
    restartButton.setTextColor(sf::Color::White);
    restartButton.setTextSize(40);

    backButton.setColor(sf::Color(70, 70, 70, 200));
    backButton.setTextColor(sf::Color::White);
    backButton.setTextSize(40);

    sf::RectangleShape grey_screen(conf::window_size_f);
    grey_screen.setFillColor(sf::Color(100, 100, 100, 100));
    window.draw(grey_screen);

    resumeButton.update(window);
    restartButton.update(window);
    backButton.update(window);

    resumeButton.show(window);
    restartButton.show(window);
    backButton.show(window);
}
int PauseMenu::handlePauseMenuSelection() {
    if (show_pausemenu) {
        if (resumeButton.isReleased()) {
            show_pausemenu = false;
            return PAUSE_RESUME;
        }

        if (restartButton.isReleased()) {
            show_pausemenu = false;
            LevelHandler::load_level();
            return PAUSE_RESUME;
        }

        if (backButton.isReleased()) {
            show_pausemenu = false;
            return PAUSE_BACK;
        }

        return PAUSE_NONE;
    }

    return PAUSE_RESUME;
}
