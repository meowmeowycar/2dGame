#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    bool show(sf::RenderWindow& window) const;
};