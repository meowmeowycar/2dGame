#include "Entity.h"
#include <SFML/Graphics.hpp>
#include "ImageDisplay.h"
#include "configuration.h"
#include "functions.h"
#include <iostream>
#include <cmath>


bool Entity::draw_hitboxes = conf::draw_hitboxes;

Entity::Entity(float x, float y, float width, float height) : position(x, y), velocity({0, 0}), force({0, 0}), hitbox(width, height), hitbox_color(sf::Color::Red), gravity_enabled(true), rotation(0) {}

Entity::Entity(float width, float height) : Entity(0, 0, width, height) {}

bool Entity::load_textures() {
  if (!Obrazek(conf::playerImage, entity_texture)) {
    return false;
  }

  return true;
}

sf::Vector2f Entity::getPosition() {
  return position;
}

void Entity::show(sf::RenderWindow& window) {
  sf::Sprite entity_sprite(entity_texture);
  entity_sprite.setPosition(position);
  entity_sprite.setOrigin({(float) entity_texture.getSize().x / 2, (float) entity_texture.getSize().y / 2});
  entity_sprite.setScale({hitbox.x / conf::player_hitbox.x, hitbox.y / conf::player_hitbox.y});
  entity_sprite.setRotation(sf::radians(rotation));
  window.draw(entity_sprite);

  if (draw_hitboxes)
    draw_hitbox(window);
}
void Entity::move(sf::Vector2f step) {
  position.x += step.x;
  position.y += step.y;
}
void Entity::update(std::vector<Obstacle>& obstacles, float dt) {
  velocity.x += force.x * dt * dt;

  if (gravity_enabled) {
    velocity.y += (force.y + conf::gravity_force) * dt * dt;
  } else {
    velocity.y += force.y * dt * dt;
  }

  float floorLevel = 1080 - hitbox.y / 2;

  if (position.y >= floorLevel) {
    //position.y = floorLevel;
    //velocity.y = 0;
  }

  sf::Vector2f step = {0, 0};
  float steps = 0;

  if(abs(velocity.x) > abs(velocity.y)) {
    steps = abs(velocity.x) * dt;
    step.x = velocity.x / abs(velocity.x);
    step.y = velocity.y / abs(velocity.x);
  } else if(abs(velocity.y) > abs(velocity.x)) {
    steps = abs(velocity.y) * dt;
    step.x = velocity.x / abs(velocity.y);
    step.y = velocity.y / abs(velocity.y);
  } else {
    steps = abs(velocity.x) * dt;
    step.x = sign(velocity.x);
    step.y = sign(velocity.y);
  }

  for (int j = 0; j <= steps; j++) {
    if((steps - j) < 1) {
      step.x *= steps - j;
      step.y *= steps - j;
    }

    bool collided_x = false;
    bool collided_y = false;
    for (int i = 0; i < obstacles.size(); i++) {
      sf::Vector2f distance = {obstacles[i].getPosition().x - position.x, obstacles[i].getPosition().y - position.y};
      if ((abs(distance.x - step.x) - hitbox.x / 2 - obstacles[i].getSize().x / 2) < 0 && (abs(distance.y) - hitbox.y / 2 - obstacles[i].getSize().y / 2) < 0) {
        collided_x = true;
        velocity.x = 0;
        step.x = 0;
      }
      if ((abs(distance.x) - hitbox.x / 2 - obstacles[i].getSize().x / 2) < 0 && (abs(distance.y - step.y) - hitbox.y / 2 - obstacles[i].getSize().y / 2) < 0) {
        collided_y = true;
        velocity.y = 0;
        step.y = 0;
      }
      if ((abs(distance.x - step.x) - hitbox.x / 2 - obstacles[i].getSize().x / 2) < 0 && (abs(distance.y - step.y) - hitbox.y / 2 - obstacles[i].getSize().y / 2) < 0 && !collided_x) {
        collided_y = true;
        velocity.y = 0;
        step.y = 0;
      }
    }

    if (collided_x && collided_y) break;

    sf::Vector2f step_copy = step;

    if (collided_x) step_copy.x = 0;
    if (collided_y) step_copy.y = 0;

    move(step_copy);
  }

}

void Entity::draw_hitbox(sf::RenderWindow& window) {
  sf::RectangleShape hitbox_shape({hitbox.x - 2, hitbox.y - 2});
  hitbox_shape.setPosition(position);
  hitbox_shape.setOrigin({hitbox.x / 2, hitbox.y / 2});
  hitbox_shape.setFillColor(sf::Color::Transparent);
  hitbox_shape.setOutlineColor(hitbox_color);
  hitbox_shape.setOutlineThickness(1);
  window.draw(hitbox_shape);
}

void Entity::setTexture(sf::Texture texture) {
  entity_texture = texture;
}

void Entity::setVelocity(sf::Vector2f new_velocity) {
  velocity.x = new_velocity.x;
  velocity.y = new_velocity.y;
}

void Entity::setForce(sf::Vector2f new_force) {
  force.x = new_force.x;
  force.y = new_force.y;
}

void Entity::setRotation(float new_rotation) {
  rotation = new_rotation;
}

void Entity::gravity(bool enabled) {
  gravity_enabled = enabled;
}

sf::Vector2f Entity::getHitbox() {
  return {hitbox.x, hitbox.y};
}

void Entity::toogle_hitboxes() {
  draw_hitboxes = !draw_hitboxes;
}