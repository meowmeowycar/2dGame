#include <SFML/Graphics.hpp>
#include "events.h"
#include "HUD.h"
#include "Entity.h"

void processEvents(sf::Window& window) {
    while (const std::optional event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
            if (keyPressed->scancode == sf::Keyboard::Scan::Escape) {
                window.close();
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