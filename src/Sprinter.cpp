#include "Sprinter.h"
#include "configuration.h"
#include "functions.h"
#include "ImageDisplay.h"


Sprinter::Sprinter(float x, float y) : Enemy(x, y, conf::sprinter_hitbox.x, conf::sprinter_hitbox.y), charging(false), dashing(false), dash_starting_position(0), attacked_player(false) {}

Sprinter::Sprinter() : Sprinter(0, 0) {}

bool Sprinter::load_textures() {
  if (!Obrazek(conf::sprinterImage, entity_texture)) {
    return false;
  }

  return true;
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
    velocity.x = 5000 * vision_direction;
  }

  if(dashing && (abs(position.x - dash_starting_position) > conf::dash_distance || velocity.x == 0)) {
    if (velocity.x != 0) {
      position.x = dash_starting_position + conf::dash_distance * vision_direction;
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
}