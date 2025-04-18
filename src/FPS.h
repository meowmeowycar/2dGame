#pragma once
#include <SFML/Graphics.hpp>


class FPS {
  float static fps_sum;
  int static fps_count;
  float static fps_array[];
  sf::Text static fps_text;

  public:
  static void show_fps(sf::RenderWindow& window, float dt);
};
