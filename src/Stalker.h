#pragma once
#include "Enemy.h"

class Stalker : public Enemy {
    bool is_touching_player;

    sf::Clock attack_timer;
public:
    Stalker(float x, float y);
    Stalker();

    bool load_textures() override;
    void update(Player& player, std::vector<Obstacle*>& obstacles, float dt) override;
    void check_touching(Player& player);
    void move_to_player(Player& player);
    void attack(Player& player);
};