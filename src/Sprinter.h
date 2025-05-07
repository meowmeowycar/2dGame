#pragma once
#include "Enemy.h"

class Sprinter : public Enemy {
  bool charging;
  bool dashing;
  float dash_starting_position;

  bool attacked_player;

  sf::Clock charge_time;
public:
  Sprinter(float x, float y);
  Sprinter();

  void update(Player& player, std::vector<Obstacle>& obstacles, float dt);
};