#pragma once
#include "Archer.h"

class Boss : public Archer {
public:
    Boss(float x, float y, short vision_directino);
    Boss(float x, float y);
    Boss();

    void update(Player& player, std::vector<Obstacle*>& obstacles, float dt) override;
    void show(sf::RenderWindow& window) override;
};