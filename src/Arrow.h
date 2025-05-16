#pragma once
#include "Entity.h"

class Arrow : public Entity {
  sf::Clock lifetime;
public:
  Arrow(float x, float y);

  void update(std::vector<Obstacle*>& obstacles, float dt) override;

  bool load_textures() override;
  float getLifetime();
};