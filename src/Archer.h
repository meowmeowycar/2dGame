#pragma once
#include "Enemy.h"
#include <vector>

class Archer : public Enemy {
  sf::Clock shooting_timer;

  sf::Texture arrow_texture;
  std::vector<Entity> arrows;
public:
  Archer(float x, float y);
  Archer();

  void update(Player& player, std::vector<Obstacle>& obstacles, float dt) override;
  void shoot(Player& player);
  bool load_textures() override;
  void show(sf::RenderWindow& window) override;
};