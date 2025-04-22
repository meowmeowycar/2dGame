#pragma once
#include <SFML\Graphics.hpp>

class Obstacle {
    sf::Vector2f position;
    sf::Vector2f size;

    sf::Texture obstacle_texture;

public:
    Obstacle(float width, float height);
    Obstacle(float x, float y, float width, float height);

    sf::Vector2f getPosition();
    sf::Vector2f getSize();

    bool load_texture(std::string texturePath);
    void show(sf::RenderWindow& window);
    void draw_hitbox(sf::RenderWindow& window);
};