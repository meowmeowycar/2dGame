#include "Player.h"
#include <SFML/Graphics.hpp>
#include "ImageDisplay.h"
#include "configuration.h"
#include "functions.h"
#include <iostream>


Player::Player() : position(0,0), velocity(0), gravity(980.0f), hitbox(conf::player_hitbox){
}

Player::Player(float x, float y) : position(x, y), hitbox(conf::player_hitbox){
}

bool Player::load_textures() {
  if (!Obrazek(conf::playerImage, player_texture)) {
    return false;
  }

  return true;
}

sf::Vector2f Player::getPosition() {
  return position;
}


void Player::show(sf::RenderWindow& window) {
  sf::Sprite player_sprite(player_texture);
  player_sprite.setPosition(position);
  player_sprite.setOrigin({(float) player_texture.getSize().x / 2, (float) player_texture.getSize().y / 2});
  window.draw(player_sprite);
}
void Player::move(sf::Vector2f step) {
  position.x += step.x;
  position.y += step.y;
}
void Player::update(std::vector<Obstacle>& obstacles, float dt) {
  sf::Vector2f step = {0, 0};

  velocity += gravity * dt;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    step.x += 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
    step.x -= 1;
  }

  position.y += velocity * dt;

  float floorLevel = 1080 - 100;

  if (position.y >= floorLevel) {
    position.y = floorLevel;
  }
  /*
  if (!fix_collisions(obstacles, step, dt)) {
    move(step.x, step.y);
  }
  */
  for (int j = 0; j < conf::player_speed * dt; j++) {
    bool collided_x = false;
    bool collided_y = false;
    for (int i = 0; i < obstacles.size(); i++) {
      sf::Vector2f distance = {obstacles[i].getPosition().x - position.x, obstacles[i].getPosition().y - position.y};
      if ((abs(distance.x - sign(step.x)) - hitbox.x / 2 - obstacles[i].getSize().x / 2) < 0 && (abs(distance.y) - hitbox.y / 2 - obstacles[i].getSize().y / 2) < 0) {
        collided_x = true;
      }
      if ((abs(distance.x) - hitbox.x / 2 - obstacles[i].getSize().x / 2) < 0 && (abs(distance.y - sign(step.y)) - hitbox.y / 2 - obstacles[i].getSize().y / 2) < 0) {
        collided_y = true;
      }
      if ((abs(distance.x - sign(step.x)) - hitbox.x / 2 - obstacles[i].getSize().x / 2) < 0 && (abs(distance.y - sign(step.y)) - hitbox.y / 2 - obstacles[i].getSize().y / 2) < 0 && !collided_x) {
        collided_y = true;
      }
    }

    if (collided_x && collided_y) break;

    sf::Vector2f step_copy = step;

    if (collided_x) step_copy.x = 0;
    if (collided_y) step_copy.y = 0;

    if (step_copy.length() != 0)
      move(step_copy.normalized());
  }

}

void Player::draw_hitbox(sf::RenderWindow& window) {
  sf::RectangleShape hitbox_shape({hitbox.x - 2, hitbox.y - 2});
  hitbox_shape.setPosition(position);
  hitbox_shape.setOrigin({hitbox.x / 2, hitbox.y / 2});
  hitbox_shape.setFillColor(sf::Color::Transparent);
  hitbox_shape.setOutlineColor(sf::Color::Red);
  hitbox_shape.setOutlineThickness(1);
  window.draw(hitbox_shape);
}

bool Player::fix_collisions(std::vector<Obstacle>& obstacles, sf::Vector2f step, float dt) {
  for (int i = 0; i < obstacles.size(); i++) {
    sf::Vector2f distance = {obstacles[i].getPosition().x - position.x, obstacles[i].getPosition().y - position.y};

    bool collided_x = sign(step.x) == sign(distance.x) && abs(step.x) > (abs(distance.x) - hitbox.x / 2 - obstacles[i].getSize().x / 2);
    collided_x = collided_x && (abs(distance.y) - hitbox.y / 2 - obstacles[i].getSize().y / 2) < 0;

    bool collided_y = sign(step.y) == sign(distance.y) && abs(step.y) > (abs(distance.y) - hitbox.y / 2 - obstacles[i].getSize().y / 2);
    collided_y = collided_y && (abs(distance.x) - hitbox.x / 2 - obstacles[i].getSize().x / 2) < 0;

    if (collided_x || collided_y) {
      for (int j = 0; j < conf::player_speed * dt; j++) {
        distance = {obstacles[i].getPosition().x - position.x - sign(step.x), obstacles[i].getPosition().y - position.y - sign(step.y)};
        if ((abs(distance.x) - hitbox.x / 2 - obstacles[i].getSize().x / 2) < 0 && (abs(distance.y) - hitbox.y / 2 - obstacles[i].getSize().y / 2) < 0)
          return true;

        position.x += sign(step.x);
        position.y += sign(step.y);
      }
      return true;
    }
  }
  return false;
}

