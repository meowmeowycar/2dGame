#include <SFML/Graphics.hpp>
#include "events.h"

#include <iostream>

#include "HUD.h"
#include "Entity.h"
#include "PauseMenu.h"
#include "../cmake-build-release/_deps/sfml-src/src/SFML/Window/InputImpl.hpp"

void processEvents(sf::Window& window) {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {

            if (keyPressed->scancode == sf::Keyboard::Scan::Escape) {
                PauseMenu::toggle_pausemenu();
            }

            if (keyPressed->scancode == sf::Keyboard::Scan::F1) {
                HUD::toogle_HUD();
            }

            if (keyPressed->scancode == sf::Keyboard::Scan::F2) {
                Entity::toogle_hitboxes();
            }
        }
    }
}