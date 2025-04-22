#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include <vector>

class Player {
private:
    sf::Vector2f position;
    sf::Vector2f hitbox;

    sf::Texture player_texture;

    bool isLoaded;
    float gravity;
    float velocity;

    float health;

public:
    Player();
    Player(float x, float y);

    bool load_textures();
    void show(sf::RenderWindow& window);
    void draw_hitbox(sf::RenderWindow& window);
    void move(sf::Vector2f step);
    void update (std::vector<Obstacle>& obstacles, float dt);
    bool fix_collisions(std::vector<Obstacle>& obstacles, sf::Vector2f step, float dt);

    sf::Vector2f getPosition();
    float getHealth();
};