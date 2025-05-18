#include "Sprinter.h"
#include "configuration.h"
#include "functions.h"
#include "ImageDisplay.h"


Sprinter::Sprinter(float x, float y, short vision_direction) : Enemy(x, y, conf::sprinter_hitbox.x, conf::sprinter_hitbox.y, vision_direction), charging(false), dashing(false), dash_starting_position(0), attacked_player(false) {
  type = "sprinter";
  vision_distance = conf::sprinter_vision_distance;
  back_vision_distance = conf::sprinter_back_vision_distance;
}

Sprinter::Sprinter(float x, float y) : Sprinter(x, y, -1) {}

Sprinter::Sprinter() : Sprinter(0, 0) {}

bool Sprinter::load_textures() {
  if (!Obrazek(conf::sprinterImage, stay_texture)) {
    return false;
  }

  if (!Obrazek(conf::sprinterImage2, run_texture)) {
    return false;
  }

  entity_texture = stay_texture;

  return true;
}

void Sprinter::update_state() {

  if (charging || dashing) {
      entity_texture = run_texture;
  }
  else {
      entity_texture = stay_texture;
  }
}

void Sprinter::update(Player& player, std::vector<Obstacle*>& obstacles, float dt) {
  Enemy::update(player, obstacles, dt);

  if(see_player) {
    // ZATRZYMAJ SIE

    if(!charging && !dashing) { // CHARGE
      charging = true;
      charge_time.restart();
      dash_starting_position = position.x;
      attacked_player = false;
    }
  }

  if(charging && charge_time.getElapsedTime().asSeconds() > conf::charge_time) { // DASH
    charging = false;
    dashing = true;
    gravity(false);
    dash_target_position = position.x + vision_direction * conf::dash_distance;
    velocity.x = 2000 * vision_direction;
  }

  if (dashing)
    turn_delay.restart();

  if(dashing && (abs(position.x - dash_starting_position) > conf::dash_distance || velocity.x == 0)) {
    if (abs(position.x - dash_starting_position) > conf::dash_distance) {
      position.x = dash_target_position;
      velocity.x = 0;
    }
    dashing = false;
    gravity(true);
  }

  sf::Vector2f distance = {player.getPosition().x - position.x, player.getPosition().y - position.y};

  bool touching_x = abs(distance.x) < conf::player_hitbox.x / 2 + conf::sprinter_hitbox.x / 2;
  bool touching_y = abs(distance.y) < conf::player_hitbox.y / 2 + conf::sprinter_hitbox.y / 2;

  if(!attacked_player && touching_x && touching_y && dashing) {
    attacked_player = true;
    player.reduce_health(conf::sprinter_damage);
  }

  update_state();
}
void Sprinter::show(sf::RenderWindow& window) {
  Enemy::show(window);

  if (draw_hitboxes) {
    draw_hitbox(window);
  }
}

void Sprinter::setTextures(sf::Texture& stay_texture, sf::Texture& run_texture) {
  this->stay_texture = stay_texture;
  this->run_texture = run_texture;
}