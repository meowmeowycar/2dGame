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

void Arrow::show(sf::RenderWindow& window) {
  sf::Sprite entity_sprite(entity_texture);
  entity_sprite.setPosition(position);

  entity_sprite.setOrigin({ (float)entity_texture.getSize().x / 2, (float)entity_texture.getSize().y / 2});

  float scale = hitbox.y / entity_texture.getSize().y;
  entity_sprite.setScale({scale, scale});


  window.draw(entity_sprite);

  if (draw_hitboxes) {
    draw_hitbox(window);
  }

}