#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include "Entity.h"



class Player;
class LevelHandler;

class Checkpoint : public Entity{

    sf::Texture m_texture;
    sf::Vector2f m_position;
    sf::FloatRect m_hitbox;
    bool m_isActive;
    bool m_isTriggered;
    int m_id;

    std::string m_savePath;

public:
    Checkpoint(float x, float y, int id, const sf::Vector2f& position);
    ~Checkpoint() = default;

    bool isActive() const {return m_isActive;};;
    bool isTriggered() const {return m_isTriggered;};
    int getId() const {return m_id;};

    void activate();
    void deactivate();
    void reset();

    bool load_textures();

    bool checkCollision(Player& player);

    bool saveGameState(Player& player);

    bool loadGameState(Player& player);

    void update(float dt);

    void show(sf::RenderWindow& window);
};




