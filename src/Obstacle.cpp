#include "Obstacle.h"
#include "ImageDisplay.h"
#include "configuration.h"
#include "Entity.h"

Obstacle::Obstacle(float x1, float y1, float x2, float y2) : position((x1 + x2) / 2, (y1 + y2) / 2), size(abs(x2 - x1), abs(y2 - y1)), type("normal") {}
Obstacle::Obstacle(float width, float height) : Obstacle(-width / 2, -height / 2, width / 2, height / 2) {}

sf::Vector2f Obstacle::getPosition() {
  return position;
}

sf::Vector2f Obstacle::getSize() {
  return size;
}

std::string Obstacle::getType() {
  return type;
}

bool Obstacle::load_texture() {
  if (!Obrazek(conf::wallImage, obstacle_texture)) {
    return false;
  }

  return true;
}

void Obstacle::setTexture(sf::Texture texture) {
  obstacle_texture = texture;
}

void Obstacle::show(sf::RenderWindow& window) {
  obstacle_texture.setRepeated(true);

  sf::Sprite obstacle_sprite(obstacle_texture);
  obstacle_sprite.setPosition(position);
  obstacle_sprite.setOrigin({size.x / 2, size.y / 2});
  obstacle_sprite.setTextureRect(sf::IntRect({0, 0}, static_cast<sf::Vector2i>(size)));
  window.draw(obstacle_sprite);

  if (conf::draw_hitboxes)
    draw_hitbox(window);
}

void Obstacle::draw_hitbox(sf::RenderWindow& window) {
  if (Entity::drawing_hitboxes()) {
    sf::RectangleShape hitbox_shape({size.x - 2, size.y - 2});
    hitbox_shape.setPosition(position);
    hitbox_shape.setOrigin({size.x / 2, size.y / 2});
    hitbox_shape.setFillColor(sf::Color::Transparent);
    hitbox_shape.setOutlineColor(sf::Color::Blue);
    hitbox_shape.setOutlineThickness(1);
    window.draw(hitbox_shape);
  }
}