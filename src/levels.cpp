#include "LevelHandler.h"
#include "Semi_obstacle.h"
#include "Archer.h"
#include "Boss.h"
#include "Sprinter.h"
#include "Stalker.h"

void LevelHandler::load_tutorial() {
    level_type = "normal";

    player->setPosition({-1000, -500});
    player->setVelocity({0, 0});
    player->setForce({0, 0});
    player->setHealth(100);

    obstacles.push_back(new Obstacle(-1900, 200, 1100, 1200));
    obstacles.push_back(new Obstacle(-1500, 100, 1500, 1100));
    obstacles.push_back(new Obstacle(-125, -400, -75, 0));
    obstacles.push_back(new Semi_obstacle(-1050, -45, -550, 5));
    enemies.push_back(new Archer(-400, -500));
    enemies.push_back(new Sprinter(-400, -500));
    enemies.push_back(new Stalker(-400, -500));

    addCheckpoint(0,0, 1,  sf::Vector2f(0.0f, 0.0f));
    l_checkpoints.push_back(new Checkpoint(0, 0, 1,  sf::Vector2f(0.0f, 0.0f)) );

    shopkeepers.push_back(new ShopKeeper(100, 0));
}

void LevelHandler::load_level_1() {
    level_type = "normal";

    player->setPosition({0, -conf::player_hitbox.y / 2});
    player->setVelocity({0, 0});
    player->setForce({0, 0});
    player->setHealth(100);

    // Obstacles

    obstacles.push_back(new Obstacle(-2250, -2000, -225, 0));

    obstacles.push_back(new Obstacle(-50000, 0, 50000, 1000));

    obstacles.push_back(new Obstacle(1425, -0, 2075, -250));

    obstacles.push_back(new Semi_obstacle(1425, -250, 1125, -200));

    obstacles.push_back(new Obstacle(1125, -200, 600, -575));

    obstacles.push_back(new Obstacle(2375, -200, 2875, -825));

    obstacles.push_back(new Semi_obstacle(2875, -250, 3125, -200));

    obstacles.push_back(new Obstacle(3125, -250, 3375, -200));

    obstacles.push_back(new Obstacle(3125, -450, 2875, -500));

    obstacles.push_back(new Semi_obstacle(3125, -500, 3375, -450));

    obstacles.push_back(new Semi_obstacle(2875, -750, 3125, -700));

    obstacles.push_back(new Obstacle(3125, -750, 3375, -700));

    obstacles.push_back(new Obstacle(3950, -0, 3375, -950));

    obstacles.push_back(new Obstacle(3125, -1000, 2725, -950));

    obstacles.push_back(new Obstacle(2875, -825, 2375, -1000));

    obstacles.push_back(new Semi_obstacle(3125, -1000, 3375, -950));

    obstacles.push_back(new Obstacle(2375, -825, 1625, -1000));

    obstacles.push_back(new Semi_obstacle(1775, -1200, 2200, -1150));

    obstacles.push_back(new Obstacle(1625, -825, 1150, -1400));

    obstacles.push_back(new Obstacle(1150, -825, 1050, -1400));

    obstacles.push_back(new Obstacle(1125, -575, 1050, -825));

    obstacles.push_back(new Obstacle(725, -2975, 800, -825));

    obstacles.push_back(new Obstacle(600, -575, -225, -425));

    obstacles.push_back(new Semi_obstacle(-125, -825, 150, -775));

    obstacles.push_back(new Semi_obstacle(600, -825, 325, -775));

    obstacles.push_back(new Semi_obstacle(50, -1075, 425, -1025));

    obstacles.push_back(new Semi_obstacle(-125, -1325, 150, -1275));

    obstacles.push_back(new Semi_obstacle(325, -1325, 600, -1275));

    obstacles.push_back(new Semi_obstacle(425, -1525, 50, -1575));

    obstacles.push_back(new Semi_obstacle(600, -1775, 325, -1825));

    obstacles.push_back(new Semi_obstacle(-125, -1825, 150, -1775));

    obstacles.push_back(new Obstacle(-225, -2025, -75, -2075));

    obstacles.push_back(new Semi_obstacle(50, -2075, 425, -2025));

    obstacles.push_back(new Obstacle(-225, -2000, -1675, -2075));

    obstacles.push_back(new Obstacle(-1675, -2075, -2250, -2000));

    obstacles.push_back(new Obstacle(-2250, -2075, -2125, -2825));

    obstacles.push_back(new Obstacle(-1875, -2325, -1200, -2275));

    obstacles.push_back(new Obstacle(-225, -2275, -325, -2850));

    obstacles.push_back(new Obstacle(-1200, -2325, -575, -2275));

    obstacles.push_back(new Obstacle(-1350, -2325, -1100, -2575));

    obstacles.push_back(new Semi_obstacle(-1100, -2575, -850, -2525));

    obstacles.push_back(new Semi_obstacle(-1350, -2575, -1600, -2525));

    obstacles.push_back(new Obstacle(-2250, -2825, -225, -2975));

    obstacles.push_back(new Obstacle(-225, -2825, 725, -2975));

    obstacles.push_back(new Obstacle(3375, -950, 3950, -3000));

    obstacles.push_back(new Semi_obstacle(725, -2275, 425, -2225));



    // Enemies

    enemies.push_back(new Archer(1000, -conf::archer_hitbox.y / 2));

    enemies.push_back(new Sprinter(1975, -350));

    enemies.push_back(new Stalker(2550, -100));

    enemies.push_back(new Stalker(2775, -100));

    enemies.push_back(new Stalker(3300, -875));

    enemies.push_back(new Archer(2150, -1375, 1));

    enemies.push_back(new Sprinter(1825, -1100, 1));

    enemies.push_back(new Sprinter(625, -725, 1));

    enemies.push_back(new Archer(100, -1475, 1));

    enemies.push_back(new Stalker(350, -1225));

    enemies.push_back(new Stalker(525, -1950));

    enemies.push_back(new Stalker(-25, -1950, 1));

    enemies.push_back(new Sprinter(100, -2225));

    enemies.push_back(new Sprinter(-1825, -2200, 1));

    enemies.push_back(new Sprinter(-1225, -2175, 1));

    enemies.push_back(new Stalker(-1825, -2450));

    enemies.push_back(new Stalker(-650, -2450, 1));

    enemies.push_back(new Archer(-900, -2700, 1));

    enemies.push_back(new Archer(-1550, -2700));

    // Checkpoints

    addCheckpoint(0,-conf::checkpoint_hitbox.y / 2, 2,  sf::Vector2f(0.0f, -conf::checkpoint_hitbox.y / 2));
    l_checkpoints.push_back(new Checkpoint(0, -conf::checkpoint_hitbox.y / 2, 2,  sf::Vector2f(0.0f, -conf::checkpoint_hitbox.y / 2)) );

    addCheckpoint(2625,-1000 - conf::checkpoint_hitbox.y / 2, 3,  sf::Vector2f(2625, -1000 - conf::checkpoint_hitbox.y / 2));
    l_checkpoints.push_back(new Checkpoint(2625, -1000 - conf::checkpoint_hitbox.y / 2, 3,  sf::Vector2f(2625, -1000 - conf::checkpoint_hitbox.y / 2)) );

    addCheckpoint(575,-2275 - conf::checkpoint_hitbox.y / 2, 4,  sf::Vector2f(575, -2275 - conf::checkpoint_hitbox.y / 2));
    l_checkpoints.push_back(new Checkpoint(575, -2275 - conf::checkpoint_hitbox.y / 2, 4,  sf::Vector2f(575, -2275 - conf::checkpoint_hitbox.y / 2)) );
}

void LevelHandler::load_level_2() {
    level_type = "boss_fight";

    player->setPosition({125, -conf::player_hitbox.y / 2});
    player->setVelocity({0, 0});
    player->setForce({0, 0});
    player->setHealth(100);


    // Obstacles

    obstacles.push_back(new Obstacle(-2250, -2000, -675, 0));

    obstacles.push_back(new Obstacle(-50000, 0, 50000, 1000));

    obstacles.push_back(new Obstacle(475, -200, 425, -2000));

    obstacles.push_back(new Obstacle(425, -250, -225, -2000));

    obstacles.push_back(new Obstacle(1100, -125, 1125, 0));

    obstacles.push_back(new Obstacle(1125, -100, 1150, -0));

    obstacles.push_back(new Obstacle(1150, -75, 1175, -0));

    obstacles.push_back(new Obstacle(1175, -50, 1200, -0));

    obstacles.push_back(new Obstacle(1200, -25, 1225, 0));

    obstacles.push_back(new Semi_obstacle(900, -450, 675, -400));

    obstacles.push_back(new Obstacle(650, -200, 1000, -150));

    obstacles.push_back(new Obstacle(950, -325, 900, -550));

    obstacles.push_back(new Obstacle(1200, -800, 1800, -775));

    obstacles.push_back(new Obstacle(-225, -2000, -675, -450));

    obstacles.push_back(new Semi_obstacle(975, -725, 1175, -675));

    obstacles.push_back(new Obstacle(475, -1025, 1975, -1125));

    obstacles.push_back(new Obstacle(1975, -2000, 2075, -0));


    // Enemies

    enemies.push_back(new Boss(1500, -conf::boss_hitbox.y / 2));


    // NPCs

    shopkeepers.push_back(new ShopKeeper(-450, -conf::shopkeeper_hitbox.y / 2));


    // Checkpoints

    addCheckpoint(125, -conf::checkpoint_hitbox.y / 2, 5,  sf::Vector2f(125, -conf::checkpoint_hitbox.y / 2));
    l_checkpoints.push_back(new Checkpoint(125, -conf::checkpoint_hitbox.y / 2, 5,  sf::Vector2f(125, -conf::checkpoint_hitbox.y / 2)) );
}
