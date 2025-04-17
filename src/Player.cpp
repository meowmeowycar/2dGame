#include "Player.h"
#include <SFML/Graphics.hpp>
#include "ImageDisplay.h"


Player::Player() : position(0,0){
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
void Player::update(const float& dt) {

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    move(200.0f * dt, 0);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
    move(-200.0f * dt, 0);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
    move(0, -200.0f * dt);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
    move(0, 200.0f * dt);
  }
}