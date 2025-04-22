#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"

class HUD {
  static sf::Texture healthbar_texture1;
  static sf::Texture healthbar_texture2;
  static sf::Texture healthbar_texture3;

  static void display_healthbar(sf::RenderWindow& window, Player& player);
public:
  static bool load_graphics();
  static void display_hud(sf::RenderWindow& window, float dt, Player& player);
};
