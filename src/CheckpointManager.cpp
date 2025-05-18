#include "CheckpointManager.h"
#include "Player.h"
#include "configuration.h"
#include <iostream>
#include "char_lengths.h"

CheckpointManager::CheckpointManager() : activeCheckpoint(nullptr), messageTimer(0.0f), showMessage(false) {}

void CheckpointManager::addCheckpoint(float x, float y, int id, const sf::Vector2f& position) {
    checkpoints.emplace_back(x, y,  id, position);
}

void CheckpointManager::update(float dt, Player& player) {
    if (showMessage) {
        messageTimer -= dt;
        if (messageTimer <= 0.0f) {
            showMessage = false;
        }
    }

    for (auto& checkpoint : checkpoints) {

        checkpoint.update(dt);

        if (!checkpoint.isTriggered() && checkpoint.checkCollision(player)) {
            for (auto& cp : checkpoints) {
                cp.deactivate();
            }

            checkpoint.activate();
            activeCheckpoint = &checkpoint;

            if (checkpoint.saveGameState(player)) {
                std::cout << "Checkpoint saved" << checkpoint.getId() <<std::endl;


                showMessage = true;
                messageTimer = 3.0f;
            }
        }
    }
}

bool CheckpointManager::loadFromLastCheckpoint(Player& player) {
    if (activeCheckpoint) {
        return activeCheckpoint -> loadGameState(player);
    }
    return false;
}

void CheckpointManager::resetCheckpoints() {
    for (auto& checkpoint : checkpoints) {
        checkpoint.reset();
    }

    activeCheckpoint = nullptr;
    showMessage = false;
}


void CheckpointManager::drawMessage(sf::RenderWindow& window) {
    if (showMessage && activeCheckpoint) {

        sf::Text message(conf::arial,"Checkpoint zapisany!");
        message.setCharacterSize(30);
        message.setFillColor(sf::Color::Red);
        message.setOutlineColor(sf::Color::Black);
        message.setOutlineThickness(2);

        message.setPosition({(conf::window_size_f.x - calculate_string_length("arial", "Checkpoint zapisany", 30)) / 2, 200});

        window.draw(message);
    }
}

