#include "Player.h"
#include <SFML/Graphics.hpp>
#include "ImageDisplay.h"


Player::Player() : position(0,0), velocity(0), gravity(980.0f){
}

bool Player::show(sf::RenderWindow& window) const {
  sf::Texture texture;
  if (!Obrazek("../../Media/Ludzik.png", texture)) {
    return false;
  }
  sf::Sprite sprite(texture);
  sprite.setPosition(position);
  window.draw(sprite);
  return true;
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