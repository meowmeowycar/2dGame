#pragma once
#include "Entity.h"

class Arrow : public Entity {
  sf::Clock lifetime;

  float s;
public:
  Arrow(float x, float y);

  void update(std::vector<Obstacle*>& obstacles, float dt) override;
  void show(sf::RenderWindow& window);

  bool load_textures() override;
  float getLifetime();

};