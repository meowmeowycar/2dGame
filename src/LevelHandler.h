#pragma once
#include "CheckpointManager.h"
#include "Enemy.h"
#include "Player.h"
#include "Obstacle.h"
#include "ShopKeeper.h"
#include "SFML/Graphics/RenderWindow.hpp"

class LevelHandler {
    static unsigned int level;

    static std::string level_type;

    static Player* player;

    static sf::Texture stalker_texture;
    static sf::Texture archer_texture;
    static sf::Texture arrow_texture;
    static sf::Texture sprinter_stay_texture;
    static sf::Texture sprinter_run_texture;
    static sf::Texture boss_texture;

    static sf::Texture obstacle_texture;
    static sf::Texture semi_obstacle_left_texture;
    static sf::Texture semi_obstacle_middle_texture;
    static sf::Texture semi_obstacle_right_texture;

    static sf::Texture checkpoint_texture;

    static sf::Texture shopkeeper_texture;

    static std::vector<Obstacle*> obstacles;
    static std::vector<Enemy*> enemies;
    static std::vector<Checkpoint*> l_checkpoints;
    static std::vector<ShopKeeper*> shopkeepers;


public:
    static ShopKeeper shop_keeper;
    static CheckpointManager checkpoint_manager;
    static std::vector<Obstacle*>& getObstacles();
    static std::string getLevelType();
    static unsigned int getLevel();
    static unsigned int getEnemiesNumber();
    static float getBossHealth();

    static bool load_textures();
    static void load_level();
    static void update(Player& player, std::vector<Obstacle*> obstacles, float dt);
    static void show(sf::RenderWindow& window);
    static void change_level(unsigned int level);
    static void next_level();
    static void unload();
    static void reference_player(Player& player);
    static void addObstacle(float x1, float y1, float x2, float y2);
    static void addSemiObstacle(float x1, float y1, float x2, float y2);
    static void addStalker(float x, float y);
    static void addArcher(float x, float y);
    static void addSprinter(float x, float y);
    static bool removeObstacle(sf::Vector2f mouse_pos, std::vector<std::string>& scripts);
    static bool removeEnemy(sf::Vector2f mouse_pos, std::vector<std::string>& scripts);

    static void addCheckpoint(float x, float y, int id, const sf::Vector2f& position);
    static bool loadFromLastCheckpoint();
    static void resetCheckpoints();

    static unsigned int getCurrentLevel() {return level;}

    static void load_tutorial();
    static void load_level_1();
    static void load_level_2();
};
