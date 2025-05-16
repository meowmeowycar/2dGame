#pragma once
#include "Obstacle.h"

class Semi_obstacle : public Obstacle {
  sf::Texture obstacle_left_texture;
  sf::Texture obstacle_right_texture;
public:
  Semi_obstacle(float x, float y, float width, float height);
  Semi_obstacle(float width, float height);

  bool load_texture() override;
  void show(sf::RenderWindow& window) override;
};