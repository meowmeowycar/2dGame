#include "arrow.h"
#include "configuration.h"
#include "ImageDisplay.h"

Arrow::Arrow(float x, float y) : Entity(x, y, conf::arrow_hitbox.x, conf::arrow_hitbox.y) {}

void Arrow::update(std::vector<Obstacle*>& obstacles, float dt) {
  Entity::update(obstacles, dt);

  if(velocity.x == 0)
    velocity.y = 0;
}

bool Arrow::load_textures() {
  if (!Obrazek(conf::arrowImage, entity_texture)) {
    return false;
  }

  return true;
}

float Arrow::getLifetime() {
  return lifetime.getElapsedTime().asSeconds();
}