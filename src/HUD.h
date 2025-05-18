#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Button.h"

class HUD {
  static bool show_hud;

  static sf::Texture healthbar_texture1;
  static sf::Texture healthbar_texture2;
  static sf::Texture healthbar_texture3;

  static sf::Texture boss_healthbar_texture1;
  static sf::Texture boss_healthbar_texture2;
  static sf::Texture boss_healthbar_texture3;

  static Button respawn_button;
  static Button next_level_button;
  static Button exit_button;

  static void display_healthbar(sf::RenderWindow& window, Player& player);
  static void display_deathscreen(sf::RenderWindow& window, Player& player);
  static void display_enemies_number(sf::RenderWindow& window);
  static void display_complete_screen(sf::RenderWindow& window);
  static void display_end_screen(sf::RenderWindow& window);
  static void display_boss_healthbar(sf::RenderWindow& window, float boss_health);
public:
  static bool load_graphics();
  static void display_hud(sf::RenderWindow& window, float dt, Player& player);
  static void toogle_HUD();
};
