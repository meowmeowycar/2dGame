#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include <vector>

class Entity {
protected:
    sf::Texture entity_texture;

    sf::Vector2f hitbox;

    sf::Vector2f position;
    sf::Vector2f force;
    sf::Vector2f velocity;
public:
    Entity(float width, float height);
    Entity(float x, float y, float width, float height);

    bool load_textures();
    void show(sf::RenderWindow& window);
    void draw_hitbox(sf::RenderWindow& window);
    void move(sf::Vector2f step);
    void update (std::vector<Obstacle>& obstacles, float dt);
    bool fix_collisions(std::vector<Obstacle>& obstacles, sf::Vector2f step, float dt);

    sf::Vector2f getPosition();
};