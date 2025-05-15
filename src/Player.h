#pragma once
#include <SFML/Graphics.hpp>
#include "Obstacle.h"
#include <vector>
#include "Entity.h"

class Player : public Entity {
    float health;
    bool sliding;

    bool dead;

    short attack_direction;

    bool hit;
    bool hit_reset;
public:
    Player(float x, float y);
    Player();


    bool attack();

    void update(std::vector<Obstacle>& obstacles, float dt);
    void reduce_health(float damage);
    void respawn();

    float getHealth();
    void setHealth(float new_health);
    bool isDead();
    short getAttackDirection();
};