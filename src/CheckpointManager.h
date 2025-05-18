#pragma once
#include "Checkpoint.h"
#include <SFML/Graphics/RenderWindow.hpp>

class Entity;

class CheckpointManager {

    std::vector<Checkpoint> checkpoints;
    Checkpoint* activeCheckpoint;
    float messageTimer;
    bool showMessage;

public:
    CheckpointManager();

    void addCheckpoint(float x, float y, int id, const sf::Vector2f& position);
    void update(float dt, Player& player);
    bool loadFromLastCheckpoint(Player& player);
    void resetCheckpoints();
    bool hasActiveCheckpoint() const {return activeCheckpoint != nullptr;}

    void drawMessage(sf::RenderWindow& window);
};
