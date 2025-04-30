#include "Player.h"
#include <SFML/Graphics.hpp>
#include "ImageDisplay.h"
#include "configuration.h"
#include "functions.h"
#include <iostream>
#include <cmath>


Player::Player() : position(0,0), velocity({0, 0}), gravity(980.0f * 144), hitbox(conf::player_hitbox), health(100){
}

Player::Player(float x, float y) : Player(){
  position = sf::Vector2f(x, y);
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

float Player::getHealth() {
  return health;
}

void Player::show(sf::RenderWindow& window) {
  sf::Sprite player_sprite(player_texture);
  player_sprite.setPosition(position);
  player_sprite.setOrigin({(float) player_texture.getSize().x / 2, (float) player_texture.getSize().y / 2});
  player_sprite.setScale({1, hitbox.y / conf::player_hitbox.y});
  window.draw(player_sprite);

  if (conf::draw_hitboxes)
    draw_hitbox(window);
}
void Player::move(sf::Vector2f step) {
  position.x += step.x;
  position.y += step.y;
}
void Player::update(std::vector<Obstacle>& obstacles, float dt) {
  sf::Vector2f step = {0, 0};

  float on_the_floor = false;

  for (int i = 0; i < obstacles.size(); i++) {
    sf::Vector2f distance = {obstacles[i].getPosition().x - position.x, obstacles[i].getPosition().y - position.y};
    if ((abs(distance.x) - hitbox.x / 2 - obstacles[i].getSize().x / 2) < 0 && (abs(distance.y) - hitbox.y / 2 - obstacles[i].getSize().y / 2) < 2 && distance.y > 0) {
      on_the_floor = true;
      break;
    }
  }

  if (abs(velocity.x) < 0.2 && abs(velocity.y) < 0.2)
    sliding = false;

  if (on_the_floor && isKeyPressed(sf::Keyboard::Key::LControl)) {
    sliding = true;
  }

  if ((!isKeyPressed(sf::Keyboard::Key::A) && !isKeyPressed(sf::Keyboard::Key::D)))
    sliding = false;

  if (isKeyPressed(sf::Keyboard::Key::W)) {
    if (on_the_floor) {
      velocity.y = -500;
      sliding = false;
      health -= 10;
    }
  }
  if (sliding) {
    velocity.x -= sign(velocity.x) * 0.005; // zmiana dlugosci slidu

    if (hitbox.x == conf::player_hitbox.x && hitbox.y == conf::player_hitbox.y) {
      hitbox = conf::player_sliding_hitbox;
      position.y += (conf::player_hitbox.y - conf::player_sliding_hitbox.y) / 2;
    }
  } else {
    velocity.x = 0;

    if (isKeyPressed(sf::Keyboard::Key::D)) {
      if (velocity.x < 1) velocity.x += 1;
    }
    if (isKeyPressed(sf::Keyboard::Key::A)) {
      if (velocity.x > -1) velocity.x -= 1;
    }

    if (hitbox.x == conf::player_sliding_hitbox.x && hitbox.y == conf::player_sliding_hitbox.y) {
      hitbox = conf::player_hitbox;
      position.y -= (conf::player_hitbox.y - conf::player_sliding_hitbox.y) / 2;
    }
  }

  float floorLevel = 1080 - hitbox.y / 2;

  if (position.y >= floorLevel) {
    //position.y = floorLevel;
    //velocity.y = 0;
  }

  velocity.y += gravity * dt * dt;

  step.x = velocity.x;
  step.y = sign(velocity.y);

  if (ceil(abs(velocity.y) * dt)) step.x *= 2 / ceil(abs(velocity.y) * dt);
  else step.x *= 2;


  for (int j = 0; j < ceil(abs(velocity.y) * dt); j++) {
    bool collided_x = false;
    bool collided_y = false;
    for (int i = 0; i < obstacles.size(); i++) {
      sf::Vector2f distance = {obstacles[i].getPosition().x - position.x, obstacles[i].getPosition().y - position.y};
      if ((abs(distance.x - step.x) - hitbox.x / 2 - obstacles[i].getSize().x / 2) < 0 && (abs(distance.y) - hitbox.y / 2 - obstacles[i].getSize().y / 2) < 0) {
        collided_x = true;
        velocity.x = 0;
      }
      if ((abs(distance.x) - hitbox.x / 2 - obstacles[i].getSize().x / 2) < 0 && (abs(distance.y - step.y) - hitbox.y / 2 - obstacles[i].getSize().y / 2) < 0) {
        collided_y = true;
        velocity.y = 0;
      }
      if ((abs(distance.x - step.x) - hitbox.x / 2 - obstacles[i].getSize().x / 2) < 0 && (abs(distance.y - step.y) - hitbox.y / 2 - obstacles[i].getSize().y / 2) < 0 && !collided_x) {
        collided_y = true;
        velocity.y = 0;
      }
    }

    if (collided_x && collided_y) break;

    sf::Vector2f step_copy = step;

    if (collided_x) step_copy.x = 0;
    if (collided_y) step_copy.y = 0;

    if (step_copy.length() != 0)
      move(step_copy);
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
