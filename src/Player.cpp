#include "Player.h"
#include <SFML/Graphics.hpp>
#include "ImageDisplay.h"


Player::Player() {
}

bool Player::show(sf::RenderWindow& window) const {
  sf::Texture texture;
  if (!Obrazek("../../Media/Ludzik.png", texture)) {
    return false;
  }
  sf::Sprite sprite(texture);
  window.draw(sprite);
  return true;
}