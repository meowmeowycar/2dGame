#include "LevelHandler.h"

#include <iostream>

#include "Archer.h"
#include "Boss.h"
#include "Editor.h"
#include "ImageDisplay.h"
#include "Semi_obstacle.h"
#include "Sprinter.h"
#include "CheckpointManager.h"
#include "configuration.h"
#include "ShopKeeper.h"

#include "Stalker.h"

unsigned int LevelHandler::level = 0;

std::string LevelHandler::level_type = "normal";

Player* LevelHandler::player = nullptr;

std::vector<Obstacle*> LevelHandler::obstacles;
std::vector<Enemy*> LevelHandler::enemies;
std::vector<Checkpoint*> LevelHandler::l_checkpoints;
std::vector<ShopKeeper*> LevelHandler::shopkeepers;

sf::Texture LevelHandler::stalker_texture;
sf::Texture LevelHandler::archer_texture;
sf::Texture LevelHandler::arrow_texture;
sf::Texture LevelHandler::sprinter_stay_texture;
sf::Texture LevelHandler::sprinter_run_texture;
sf::Texture LevelHandler::boss_texture;

sf::Texture LevelHandler::obstacle_texture;
sf::Texture LevelHandler::semi_obstacle_left_texture;
sf::Texture LevelHandler::semi_obstacle_middle_texture;
sf::Texture LevelHandler::semi_obstacle_right_texture;

sf::Texture LevelHandler::checkpoint_texture;

sf::Texture LevelHandler::shopkeeper_texture;

CheckpointManager LevelHandler::checkpoint_manager;
ShopKeeper LevelHandler::shop_keeper;
std::vector<Obstacle*>& LevelHandler::getObstacles() {
    return obstacles;
}

std::string LevelHandler::getLevelType() {
    return level_type;
}

unsigned int LevelHandler::getLevel() {
    return level;
}

unsigned int LevelHandler::getEnemiesNumber() {
    return enemies.size();
}

float LevelHandler::getBossHealth() {
    for (const auto& enemy : enemies) {
        if (enemy->getType() == "boss")
            return enemy->getHealth();
    }
    return 0;
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
    if (!Obrazek(conf::bossImage, boss_texture)) {
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
    if (!Obrazek(conf::shopkeeperImage, shopkeeper_texture)) {
        return false;
    }

    return true;
}


void LevelHandler::load_level() {
    obstacles.clear();
    enemies.clear();
    l_checkpoints.clear();
    shopkeepers.clear();

    switch(level) {
        case 0:
            load_tutorial();
            break;
        case 1:
            load_level_1();
            break;
        case 2:
            load_level_2();
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
        } else if ((*enemy).getType() == "boss") {
            (*enemy).setTexture(boss_texture);
            (*dynamic_cast<Boss*>(enemy)).setArrowTexture(arrow_texture);
        }
    }

    for (const auto& checkpoint : l_checkpoints) {
        (*checkpoint).setTexture(checkpoint_texture);
    }

    for (const auto& shopkeeper : shopkeepers) {
        (*shopkeeper).setTexture(shopkeeper_texture);
    }

    Editor::reset(obstacles.size(), enemies.size());
}

void LevelHandler::update(Player& player, std::vector<Obstacle*> obstacles, float dt) {
    for (int i = 0; i < enemies.size(); i++)  {
        (*enemies[i]).update(player, obstacles, dt);

        if ((*enemies[i]).getHealth() <= 0) {
            enemies.erase(enemies.begin() + i);
            i--;
        }
    }

    for (auto& shopkeeper : shopkeepers) {
        (*shopkeeper).update(player, obstacles, dt);
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

    for (const auto& shopkeeper : shopkeepers) {
        (*shopkeeper).show(window);
    }
}

void LevelHandler::change_level(unsigned int level) {
    LevelHandler::level = level;
    resetCheckpoints();
    load_level();
}

void LevelHandler::next_level() {
    level++;
    load_level();
}

void LevelHandler::unload() {
    for (auto obstacle : obstacles) {
        delete obstacle;
    }

    for (auto enemy : enemies) {
        delete enemy;
    }

    for (auto shopkeeper : shopkeepers) {
        delete shopkeeper;
    }

    resetCheckpoints();
}

void LevelHandler::reference_player(Player& player) {
    LevelHandler::player = &player;
}

void LevelHandler::addObstacle(float x1, float y1, float x2, float y2) {
    obstacles.push_back(new Obstacle(x1, y1, x2, y2));
    (*obstacles.back()).setTexture(obstacle_texture);
}

void LevelHandler::addSemiObstacle(float x1, float y1, float x2, float y2) {
    obstacles.push_back(new Semi_obstacle(x1, y1, x2, y2));
    dynamic_cast<Semi_obstacle*>(obstacles.back())->setTextures(semi_obstacle_left_texture, semi_obstacle_middle_texture, semi_obstacle_right_texture);
}

void LevelHandler::addStalker(float x, float y) {
    enemies.push_back(new Stalker(x, y));
    dynamic_cast<Stalker*>(enemies.back())->setTexture(stalker_texture);
}

void LevelHandler::addArcher(float x, float y) {
    enemies.push_back(new Archer(x, y));
    dynamic_cast<Archer*>(enemies.back())->setTexture(archer_texture);
}

void LevelHandler::addSprinter(float x, float y) {
    enemies.push_back(new Sprinter(x, y));
    dynamic_cast<Sprinter*>(enemies.back())->setTextures(sprinter_stay_texture, sprinter_run_texture);
}

bool LevelHandler::removeObstacle(sf::Vector2f mouse_pos, std::vector<std::string>& scripts) {
    for (int i = obstacles.size() - 1; i >= 0; i--) {
        if (abs(mouse_pos.x - obstacles[i]->getPosition().x) < obstacles[i]->getSize().x / 2 && abs(mouse_pos.y - obstacles[i]->getPosition().y) < obstacles[i]->getSize().y / 2) {
            obstacles.erase(obstacles.begin() + i);
            scripts.erase(scripts.begin() + i);
            return true;
        }
    }

    return false;
}

bool LevelHandler::removeEnemy(sf::Vector2f mouse_pos, std::vector<std::string>& scripts) {
    for (int i = enemies.size() - 1; i >= 0; i--) {
        if (abs(mouse_pos.x - enemies[i]->getPosition().x) < enemies[i]->getHitbox().x / 2 && abs(mouse_pos.y - enemies[i]->getPosition().y) < enemies[i]->getHitbox().y / 2) {
            enemies.erase(enemies.begin() + i);
            scripts.erase(scripts.begin() + i);
            return true;
        }
    }

    return false;
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
