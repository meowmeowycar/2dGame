#include "PauseMenu.h"
#include "configuration.h"
#include "Button.h"
#include <SFML/Graphics.hpp>

bool PauseMenu::show_pausemenu = conf::show_pausemenu;
std::vector<Button> PauseMenu::pauseButtons;


void PauseMenu::display_pausemenu(sf::RenderWindow& window) {

    if (!show_pausemenu) return;

    Button resume_button(300, 80, "RESUME");
    resume_button.setPosition(conf::window_size_f.x / 2.0f, conf::window_size_f.y / 2.0f - 100);
    resume_button.setColor(sf::Color(70, 70, 70, 200));
    resume_button.setTextColor(sf::Color::White);
    resume_button.setTextSize(40);
    pauseButtons.push_back(resume_button);

    Button exit_button(300, 80, "EXIT");
    exit_button.setPosition(conf::window_size_f.x / 2.0f, conf::window_size_f.y / 2.0f + 100);
    exit_button.setColor(sf::Color(70, 70, 70, 200));
    exit_button.setTextColor(sf::Color::White);
    exit_button.setTextSize(40);
    pauseButtons.push_back(exit_button);

    sf::RectangleShape grey_screen(conf::window_size_f);
    grey_screen.setFillColor(sf::Color(100, 100, 100, 100));
    window.draw(grey_screen);

    for (auto& button : pauseButtons) {
        button.show(window);
    }

    for (auto& button : pauseButtons) {
        button.update(window);
    }

    if (pauseButtons.size() >= 2) {
        if (pauseButtons[0].isReleased()) {
            toggle_pausemenu();
        }
        if (pauseButtons[1].isReleased()) {
            window.close();
        }
    }
}
void PauseMenu::toggle_pausemenu() {
    show_pausemenu = !show_pausemenu;

    if (!show_pausemenu) {
        pauseButtons.clear();
    }
}
