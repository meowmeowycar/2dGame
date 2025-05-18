#pragma once
#include "Enemy.h"

class Sprinter : public Enemy {
  bool charging;
  bool dashing;
  float dash_starting_position;
  float dash_target_position;

  bool attacked_player;

  sf::Texture stay_texture;
  sf::Texture run_texture;

  sf::Clock charge_time;

public:
  Sprinter(float x, float y, short vision_direction);
  Sprinter(float x, float y);
  Sprinter();

  bool load_textures() override;
  void update(Player& player, std::vector<Obstacle*>& obstacles, float dt) override;
  void show(sf::RenderWindow& window) override;
  void setTextures(sf::Texture& stay_texture, sf::Texture& run_texture);

  void update_state();
};