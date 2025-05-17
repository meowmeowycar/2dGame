#pragma once
#include <SFML\Graphics.hpp>

#include "configuration.h"

class Obstacle {
protected:
    std::string type;

    sf::Vector2f position;
    sf::Vector2f size;

    sf::Texture obstacle_texture;

public:
    Obstacle(float x, float y, float x2, float y2);
    Obstacle(float width, float height);

    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    std::string getType();

    void setTexture(sf::Texture texture);

    virtual bool load_texture();
    virtual void show(sf::RenderWindow& window);
    void draw_hitbox(sf::RenderWindow& window);
};
