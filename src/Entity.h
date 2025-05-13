#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include <vector>

class Entity {
protected:
    static bool draw_hitboxes;

    sf::Texture entity_texture;

    sf::Vector2f hitbox;
    float rotation;

    sf::Vector2f position;
    sf::Vector2f force;
    sf::Vector2f velocity;

    sf::Color hitbox_color;

    bool gravity_enabled;
public:
    Entity(float width, float height);
    Entity(float x, float y, float width, float height);

    virtual bool load_textures();
    void show(sf::RenderWindow& window);
    void draw_hitbox(sf::RenderWindow& window);
    void move(sf::Vector2f step);
    void update (std::vector<Obstacle>& obstacles, float dt);
    bool fix_collisions(std::vector<Obstacle>& obstacles, sf::Vector2f step, float dt);

    sf::Vector2f getPosition();
    sf::Vector2f getHitbox();
    void setTexture(sf::Texture texture);
    void setVelocity(sf::Vector2f new_velocity);
    void setForce(sf::Vector2f new_force);
    void setRotation(float new_rotation);

    void gravity(bool enabled);
    static void toogle_hitboxes();
};