#include "LevelHandler.h"
#include "Semi_obstacle.h"
#include "Archer.h"
#include "Sprinter.h"
#include "Stalker.h"

void LevelHandler::load_tutorial() {
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
}

void LevelHandler::load_level_1() {
    player->setPosition({0, -conf::player_hitbox.y / 2});
    player->setVelocity({0, 0});
    player->setForce({0, 0});
    player->setHealth(100);

    // Obstacles

    obstacles.push_back(new Obstacle(-2250, -2000, -225, 0));
    obstacles.push_back(new Obstacle(-50000, 0, 50000, 1000));


    // Enemies

    enemies.push_back(new Archer(1000, -conf::archer_hitbox.y / 2));


}
