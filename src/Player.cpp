#include "Player.h"
#include <SFML/Graphics.hpp>
#include "ImageDisplay.h"


Player::Player() {
}

void Player::show(sf::RenderWindow& window) const {
  sf::Texture texture;
  Obrazek("../../Media/Ludzik.png", texture);
  sf::Sprite sprite(texture);
  window.draw(sprite);
}