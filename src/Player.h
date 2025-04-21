#pragma once
#include <SFML/Graphics.hpp>

class Player {
private:
    sf::Vector2f position;
    sf::Vector2f hitbox;

    sf::Texture player_texture;

    bool isLoaded;
    float gravity;
    float velocity;

public:
    Player();

    void show(sf::RenderWindow& window);
    void draw_hitbox(sf::RenderWindow& window);
    void move(float x, float y);
    void update (float dt);
    bool load_textures();

    sf::Vector2f getPosition();
};