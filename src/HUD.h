#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Button.h"

class HUD {
  static bool show_hud;

  static sf::Texture healthbar_texture1;
  static sf::Texture healthbar_texture2;
  static sf::Texture healthbar_texture3;

  static Button respawn_button;

  static void display_healthbar(sf::RenderWindow& window, Player& player);
  static void display_deathscreen(sf::RenderWindow& window, Player& player);

public:
  static bool load_graphics();
  static void display_hud(sf::RenderWindow& window, float dt, Player& player);
  static void toogle_HUD();
};
