#include "Checkpoint.h"
#include "functions.h"
#include <iostream>
#include <fstream>
#include "configuration.h"
#include "Player.h"
#include "LevelHandler.h"
#include "ImageDisplay.h"
#include <sys/stat.h>

Checkpoint::Checkpoint(float x, float y, int id, const sf::Vector2f& position) : Entity(x, y, conf::checkpoint_hitbox.x, conf::checkpoint_hitbox.y), m_id(id), m_position(position),
                                                               m_isActive(false), m_isTriggered(false) {
    m_savePath = "../../saves/checkpoint_" + std::to_string(m_id) + ".save";
}

bool Checkpoint::load_textures() {
    if (!Obrazek(conf::checkpointImage, m_texture)) {
        return false;
    }
    return true;
}


void Checkpoint::activate() {
    m_isActive = true;
    m_isTriggered = true;

    //jakis kolor moze na aktywacje
}

void Checkpoint::deactivate() {
    m_isActive = false;

    //oraz kolor deaktywacji
}

void Checkpoint::reset() {
    m_isTriggered = false;
    deactivate();
}

bool Checkpoint::checkCollision(Player& player) {
    sf::Vector2f playerPos = player.getPosition();
    sf::Vector2f playerHitbox = player.getHitbox();

    float dx = abs(playerPos.x - position.x);
    float dy = abs(playerPos.y - position.y);

    if (dx < playerHitbox.x / 2 + hitbox.x / 2 && dy < playerHitbox.y / 2 + hitbox.y / 2) {
        if (!m_isTriggered) {
            activate();
            saveGameState(player);
            return true;
        }
    }
    return false;
}

bool Checkpoint::saveGameState(Player& player) {
    try {
        #ifdef _WIN32
        mkdir("Saves");
        #else
        mkdir("saves", 0755);
        #endif

        std::ofstream saveFile(m_savePath, std::ios::binary);
        if (!saveFile.is_open()) {
            std::cerr << "Error opening save file" << m_savePath <<std::endl;
            return false;
        }

        sf::Vector2f playerPos = player.getPosition();
        float playerHealth = player.getHealth();

        saveFile.write(reinterpret_cast<const char*>(&playerPos.x), sizeof(float));
        saveFile.write(reinterpret_cast<const char*>(&playerPos.y), sizeof(float));
        saveFile.write(reinterpret_cast<const char*>(&playerHealth), sizeof(float));

        unsigned int currentLevel = LevelHandler::getCurrentLevel();
        saveFile.write(reinterpret_cast<const char*>(&currentLevel), sizeof(unsigned int));

        saveFile.close();
        return true;
    } catch (const std::exception& e) {
        std::cerr << "Blad zapisu podczas: " << e.what() <<std::endl;
        return false;
    }
}

bool Checkpoint::loadGameState(Player& player) {
    try {
        std::ifstream checkFile(m_savePath);
        if (!checkFile.good()) {
            std::cerr << "plik nie istnieje" << m_savePath <<std::endl;
            return false;
        }
        checkFile.close();

        std::ifstream saveFile(m_savePath, std::ios::binary);
        if (!saveFile.is_open()) {
            std::cerr << "Error opening save file" << m_savePath <<std::endl;
            return false;
        }

        sf::Vector2f playerPos;
        float playerHealth;

        saveFile.read(reinterpret_cast<char*>(&playerPos.x), sizeof(float));
        saveFile.read(reinterpret_cast<char*>(&playerPos.y), sizeof(float));
        saveFile.read(reinterpret_cast<char*>(&playerHealth), sizeof(float));

        unsigned int savedLevel;
        saveFile.read(reinterpret_cast<char*>(&savedLevel), sizeof(unsigned int));

        player.setPosition(playerPos);
        player.setHealth(playerHealth);

        if (LevelHandler::getCurrentLevel() != savedLevel) {
            LevelHandler::change_level(savedLevel);
            LevelHandler::load_level();
        }

        saveFile.close();
        return true;
    }catch (const std::exception& e) {
        std::cerr << "Blad wczytania gry: " << e.what() <<std::endl;
        return false;
    }
}

void Checkpoint::update(float dt) {}


void Checkpoint::show(sf::RenderWindow& window) {
    sf::Sprite entity_sprite(entity_texture);

    entity_sprite.setPosition(position);
    entity_sprite.setOrigin({(float)entity_texture.getSize().x / 2, (float)entity_texture.getSize().y / 2});

    float scale_x = hitbox.x / entity_texture.getSize().x;
    float scale_y = hitbox.y / entity_texture.getSize().y;

    entity_sprite.setScale({scale_x, scale_y});

    window.draw(entity_sprite);

    if (draw_hitboxes) {
        draw_hitbox(window);
    }
}

