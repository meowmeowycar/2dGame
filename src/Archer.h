#pragma once
#include "Enemy.h"
#include "Arrow.h"
#include <vector>

class Archer : public Enemy {
protected:
  sf::Clock shooting_timer;

  sf::Texture arrow_texture;
  std::vector<Arrow> arrows;

  float s;
public:
  Archer(float x, float y, short vision_direction);
  Archer(float x, float y);
  Archer();

  void update(Player& player, std::vector<Obstacle*>& obstacles, float dt) override;
  void shoot(Player& player);
  bool load_textures() override;
  void show(sf::RenderWindow& window) override;

  void setArrowTexture(sf::Texture texture);
};