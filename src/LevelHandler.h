#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Obstacle.h"
#include "SFML/Graphics/RenderWindow.hpp"

class LevelHandler {
    static unsigned int level;

    static Player* player;

    static sf::Texture stalker_texture;
    static sf::Texture archer_texture;
    static sf::Texture arrow_texture;
    static sf::Texture sprinter_stay_texture;
    static sf::Texture sprinter_run_texture;

    static sf::Texture obstacle_texture;
    static sf::Texture semi_obstacle_left_texture;
    static sf::Texture semi_obstacle_middle_texture;
    static sf::Texture semi_obstacle_right_texture;

    static std::vector<Obstacle*> obstacles;
    static std::vector<Enemy*> enemies;
public:
    static std::vector<Obstacle*>& getObstacles();

    static bool load_textures();
    static void load_level();
    static void update(Player& player, std::vector<Obstacle*> obstacles, float dt);
    static void show(sf::RenderWindow& window);
    static void change_level(unsigned int level);
    static void unload();
    static void reference_player(Player& player);
    static void addObstacle(float x, float y, float width, float height);

    static void load_tutorial();
    static void load_level_1();
};
