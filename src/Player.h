#pragma once
#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Vector2f position;
    sf::Texture texture;
    bool isLoaded;
    float gravity;
    float velocity;

public:
    Player();

    bool show(sf::RenderWindow& window) const;
    void move(float x, float y);
    void update (float dt);
};