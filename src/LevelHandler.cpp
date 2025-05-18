#include "LevelHandler.h"

#include <iostream>

#include "Archer.h"
#include "ImageDisplay.h"
#include "Semi_obstacle.h"
#include "Sprinter.h"
#include "CheckpointManager.h"
#include "configuration.h"

unsigned int LevelHandler::level = 0;

Player* LevelHandler::player = nullptr;

std::vector<Obstacle*> LevelHandler::obstacles;
std::vector<Enemy*> LevelHandler::enemies;
std::vector<Checkpoint*> LevelHandler::l_checkpoints;

sf::Texture LevelHandler::stalker_texture;
sf::Texture LevelHandler::archer_texture;
sf::Texture LevelHandler::arrow_texture;
sf::Texture LevelHandler::sprinter_stay_texture;
sf::Texture LevelHandler::sprinter_run_texture;

sf::Texture LevelHandler::obstacle_texture;
sf::Texture LevelHandler::semi_obstacle_left_texture;
sf::Texture LevelHandler::semi_obstacle_middle_texture;
sf::Texture LevelHandler::semi_obstacle_right_texture;

sf::Texture LevelHandler::checkpoint_texture;

CheckpointManager LevelHandler::checkpoint_manager;
std::vector<Obstacle*>& LevelHandler::getObstacles() {
    return obstacles;
}

bool LevelHandler::load_textures() {
    if (!Obrazek(conf::stalkerImage, stalker_texture)) {
        return false;
    }
    if (!Obrazek(conf::archerImage, archer_texture)) {
        return false;
    }
    if (!Obrazek(conf::arrowImage, arrow_texture)) {
        return false;
    }
    if (!Obrazek(conf::sprinterImage, sprinter_stay_texture)) {
        return false;
    }
    if (!Obrazek(conf::sprinterImage2, sprinter_run_texture)) {
        return false;
    }

    if (!Obrazek(conf::wallImage, obstacle_texture)) {
        return false;
    }
    if (!Obrazek(conf::semiWallImage1, semi_obstacle_left_texture)) {
        return false;
    }
    if (!Obrazek(conf::semiWallImage2, semi_obstacle_right_texture)) {
        return false;
    }
    if (!Obrazek(conf::semiWallImage3, semi_obstacle_middle_texture)) {
        return false;
    }
    if (!Obrazek(conf::checkpointImage, checkpoint_texture)) {
        return false;
    }

    return true;
}


void LevelHandler::load_level() {
    obstacles.clear();
    enemies.clear();
    l_checkpoints.clear();

    switch(level) {
        case 0:
            load_tutorial();
            break;
        case 1:
            load_level_1();
            break;
    }

    for (const auto& obstacle : obstacles) {
        if ((*obstacle).getType() == "semi") {
            (*dynamic_cast<Semi_obstacle*>(obstacle)).setTextures(semi_obstacle_left_texture, semi_obstacle_middle_texture, semi_obstacle_right_texture);
        } else if ((*obstacle).getType() == "normal") {
            (*obstacle).setTexture(obstacle_texture);
        } else { // Default texture
            (*obstacle).setTexture(obstacle_texture);
        }
    }

    for (const auto& enemy : enemies) {
        if ((*enemy).getType() == "stalker") {
            (*enemy).setTexture(stalker_texture);
        } else if ((*enemy).getType() == "archer") {
            (*enemy).setTexture(archer_texture);
            (*dynamic_cast<Archer*>(enemy)).setArrowTexture(arrow_texture);
        } else if ((*enemy).getType() == "sprinter") {
            (*dynamic_cast<Sprinter*>(enemy)).setTextures(sprinter_stay_texture, sprinter_run_texture);
        }
    }

    for (const auto& checkpoint : l_checkpoints) {
        (*checkpoint).setTexture(checkpoint_texture);
    }
}

void LevelHandler::update(Player& player, std::vector<Obstacle*> obstacles, float dt) {
    for (int i = 0; i < enemies.size(); i++)  {
        (*enemies[i]).update(player, obstacles, dt);

        if ((*enemies[i]).getHealth() <= 0) {
            enemies.erase(enemies.begin() + i);
            i--;
        }
    }

    checkpoint_manager.update(dt, player);
}

void LevelHandler::show(sf::RenderWindow& window) {
    for (const auto& obstacle : obstacles) {
        (*obstacle).show(window);
    }

    for (const auto& enemy : enemies) {
        (*enemy).show(window);
    }

    for (const auto& checkpoint : l_checkpoints) {
        (*checkpoint).show(window);
    }
}

void LevelHandler::change_level(unsigned int level) {
    LevelHandler::level = level;
    resetCheckpoints();
}

void LevelHandler::unload() {
    for (auto enemy : enemies) {
        delete enemy;
    }

    for (auto obstacle : obstacles) {
        delete obstacle;
    }

    resetCheckpoints();
}

void LevelHandler::reference_player(Player& player) {
    LevelHandler::player = &player;
}

void LevelHandler::addObstacle(float x, float y, float width, float height) {
    obstacles.push_back(new Obstacle(x, y, width, height));
    (*obstacles.back()).setTexture(obstacle_texture);
}

void LevelHandler::addCheckpoint(float x, float y, int id, const sf::Vector2f& position) {
    checkpoint_manager.addCheckpoint(x, y, id, position);
}

bool LevelHandler::loadFromLastCheckpoint() {
    if (player && checkpoint_manager.hasActiveCheckpoint()) {
        return checkpoint_manager.loadFromLastCheckpoint(*player);
    }
    return false;
}

void LevelHandler::resetCheckpoints() {
    checkpoint_manager.resetCheckpoints();
}
