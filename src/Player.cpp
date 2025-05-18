#include "Player.h"
#include <SFML/Graphics.hpp>
#include "ImageDisplay.h"
#include "configuration.h"
#include "functions.h"
#include <iostream>
#include <cmath>
#include "../cmake-build-release/_deps/sfml-src/src/SFML/Window/InputImpl.hpp"

#include "HUD.h"


Player::Player(float x, float y) : Entity(x, y, conf::player_hitbox.x, conf::player_hitbox.y), health(100000), dead(false), hit(false), attack_direction(1) {
}

Player::Player() : Player(0, 0) {}


bool Player::load_textures() {
  if (!Obrazek(conf::playerImage, entity_texture)) {
    return false;
  }

  return true;
}


bool Player::attack() {
  if (hit)
    return true;

  return false;
}

short Player::getAttackDirection() {
  return attack_direction;
}

float Player::getHealth() {
  return health;
}

void Player::setHealth(float new_health) {
  health = new_health;
}

void Player::respawn() {
  position = {0, -conf::player_hitbox.y / 2};
  dead = false;
  health = 100;
}

bool Player::isDead() {
  return dead;
}

void Player::reduce_health(float damage) {
  health -= damage;

  if (health <= 0)
    health = 0;
}

void Player::update(std::vector<Obstacle*>& obstacles, float dt) {
  if (health <= 0) {
    dead = true;
    velocity.x = 0;
    force.x = 0;
  }

  if (velocity.x != 0)
    attack_direction = sign(velocity.x);

  if (!dead) {
    if (isKeyPressed(sf::Keyboard::Key::S)) {
      descend = true;
    } else
      descend = false;

    if (isKeyPressed(sf::Keyboard::Key::Space)) {
      if (hit_reset) {
        hit_reset = false;
        hit = true;
      } else {
        hit = false;
      }
    } else {
      hit_reset = true;
      hit = false;
    }

    float on_the_floor = false;

    for (int i = 0; i < obstacles.size(); i++) {
      sf::Vector2f distance = {(*obstacles[i]).getPosition().x - position.x, (*obstacles[i]).getPosition().y - position.y};
      bool on_obstacle_x = (abs(distance.x) - hitbox.x / 2 - (*obstacles[i]).getSize().x / 2) < 0;
      bool on_obstacle_y = (abs(distance.y) - hitbox.y / 2 - (*obstacles[i]).getSize().y / 2) < 2;
      bool not_in_obstacle_y = (abs(distance.y) - hitbox.y / 2 - (*obstacles[i]).getSize().y / 2) >= 0;
      if (on_obstacle_x && on_obstacle_y && not_in_obstacle_y && distance.y > 0 && abs(velocity.y) < 0.1) {
        on_the_floor = true;
        break;
      }
    }

    if (sliding && abs(velocity.x) < 1 && abs(velocity.y) < 1) {
      velocity.x = 0;
      sliding = false;
    }

    if (on_the_floor && isKeyPressed(sf::Keyboard::Key::LControl)) {
      sliding = true;
    }

    if ((!isKeyPressed(sf::Keyboard::Key::A) && !isKeyPressed(sf::Keyboard::Key::D)))
      sliding = false;

    if (isKeyPressed(sf::Keyboard::Key::W)) {
      if (on_the_floor) {
        velocity.y = -conf::jump_strength;
        sliding = false;
      }
    }
    if (sliding) {
      force.x = -sign(velocity.x) * 125; // zmiana dlugosci slidu

      if (hitbox.x == conf::player_hitbox.x && hitbox.y == conf::player_hitbox.y) {
        hitbox = conf::player_sliding_hitbox;
        position.y += (conf::player_hitbox.y - conf::player_sliding_hitbox.y) / 2;
      }
    } else {
      force.x = 0;
      velocity.x = 0;

      if (isKeyPressed(sf::Keyboard::Key::D)) {
        if (velocity.x < 1) velocity.x += conf::player_speed;
      }
      if (isKeyPressed(sf::Keyboard::Key::A)) {
        if (velocity.x > -1) velocity.x -= conf::player_speed;
      }

      if (hitbox.x == conf::player_sliding_hitbox.x && hitbox.y == conf::player_sliding_hitbox.y) {
        hitbox = conf::player_hitbox;
        position.y -= (conf::player_hitbox.y - conf::player_sliding_hitbox.y) / 2;
      }
    }
  }

  if (isKeyPressed(sf::Keyboard::Key::Space)) {
    sword.startAttack();
  }

  if (isKeyPressed(sf::Keyboard::Key::C)) {
    magic_staff.startAttack();
  }



  sword.update(dt, position, attack_direction);

  sf::Vector2f mouse_pos;
  mouse_pos.x = sf::priv::InputImpl::getMousePosition().x - conf::window_size_f.x / 2 + position.x;
  mouse_pos.y = sf::priv::InputImpl::getMousePosition().y - (conf::window_size_f.y / 2 + 200) + position.y;
  magic_staff.update(dt, position, attack_direction, obstacles, mouse_pos);

  Entity::update(obstacles, dt);
}
void Player::show(sf::RenderWindow& window) {
  sf::Sprite entity_sprite(entity_texture);
  entity_sprite.setPosition(position);
  entity_sprite.setOrigin({(float) entity_texture.getSize().x / 2, (float) entity_texture.getSize().y / 2});
  entity_sprite.setScale({attack_direction * hitbox.x / entity_texture.getSize().x, hitbox.y / entity_texture.getSize().y});
  entity_sprite.setRotation(sf::radians(rotation));
  window.draw(entity_sprite);

  sword.draw(window);
  magic_staff.draw(window);

  if (draw_hitboxes) {
    draw_hitbox(window);
  }
}

void Player::swordAttack() {
  sword.startAttack();
}

Sword& Player::getSword() {
  return sword;
}

void Player::staffAttack() {
  magic_staff.startAttack();
}

MagicStaff& Player::getStaff() {
  return magic_staff;
}

void Player::acquiredMagicStaff() {
  magic_staff.setAcquired(true);
}