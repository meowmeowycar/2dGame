#include "Player.h"
#include <SFML/Graphics.hpp>
#include "ImageDisplay.h"
#include "configuration.h"


Player::Player() : position(0,0), velocity(0), gravity(980.0f), hitbox(conf::player_hitbox){
}

bool Player::load_textures() {
  if (!Obrazek(conf::playerImage, player_texture)) {
    return false;
  }

  return true;
}


void Player::show(sf::RenderWindow& window) {
  sf::Sprite player_sprite(player_texture);
  player_sprite.setPosition(position);
  player_sprite.setOrigin({(float) player_texture.getSize().x / 2, (float) player_texture.getSize().y / 2});
  window.draw(player_sprite);
}
void Player::move(float x,float y) {
  position.x += x;
  position.y += y;
}
void Player::update(float dt) {

  velocity += gravity * dt;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    move(200.0f * dt, 0);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
    move(-200.0f * dt, 0);
  }

  position.y += velocity * dt;

  float floorLevel = 1080 - 100;

  if (position.y >= floorLevel) {
    position.y = floorLevel;
  }
}

void Player::draw_hitbox(sf::RenderWindow& window) {
  sf::RectangleShape hitbox_shape(hitbox);
  hitbox_shape.setPosition(position);
  hitbox_shape.setOrigin({hitbox.x / 2, hitbox.y / 2});
  hitbox_shape.setFillColor(sf::Color::Transparent);
  hitbox_shape.setOutlineColor(sf::Color::Red);
  hitbox_shape.setOutlineThickness(1);
  window.draw(hitbox_shape);
}

sf::Vector2f Player::getPosition() {
  return position;
}
