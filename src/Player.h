#pragma once
#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    void show(sf::RenderWindow& window) const;
};