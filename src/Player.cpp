#include "Player.h"
#include <SFML/Graphics.hpp>
#include "ImageDisplay.h"
#include "configuration.h"
#include "functions.h"
#include <iostream>
#include <cmath>


Player::Player(float x, float y) : Entity(x, y, conf::player_hitbox.x, conf::player_hitbox.y), health(100){
}

Player::Player() : Player(0, 0) {}

/*
bool Player::load_textures() {
  if (!Obrazek(conf::playerImage, player_texture)) {
    return false;
  }

  return true;
}
*/

float Player::getHealth() {
  return health;
}

void Player::reduce_health(float damage) {
  health -= damage;

  if (health <= 0)
    health = 0;
}

void Player::update(std::vector<Obstacle>& obstacles, float dt) {
  float on_the_floor = false;

  for (int i = 0; i < obstacles.size(); i++) {
    sf::Vector2f distance = {obstacles[i].getPosition().x - position.x, obstacles[i].getPosition().y - position.y};
    if ((abs(distance.x) - hitbox.x / 2 - obstacles[i].getSize().x / 2) < 0 && (abs(distance.y) - hitbox.y / 2 - obstacles[i].getSize().y / 2) < 2 && distance.y > 0) {
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
      velocity.y = -500;
      sliding = false;
    }
  }
  if (sliding) {
    force.x = -sign(velocity.x) / dt / dt * 0.75; // zmiana dlugosci slidu

    if (hitbox.x == conf::player_hitbox.x && hitbox.y == conf::player_hitbox.y) {
      hitbox = conf::player_sliding_hitbox;
      position.y += (conf::player_hitbox.y - conf::player_sliding_hitbox.y) / 2;
    }
  } else {
    force.x = 0;
    velocity.x = 0;

    if (isKeyPressed(sf::Keyboard::Key::D)) {
      if (velocity.x < 1) velocity.x += 200;
    }
    if (isKeyPressed(sf::Keyboard::Key::A)) {
      if (velocity.x > -1) velocity.x -= 200;
    }

    if (hitbox.x == conf::player_sliding_hitbox.x && hitbox.y == conf::player_sliding_hitbox.y) {
      hitbox = conf::player_hitbox;
      position.y -= (conf::player_hitbox.y - conf::player_sliding_hitbox.y) / 2;
    }
  }

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

/* NOT USED
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
*/
