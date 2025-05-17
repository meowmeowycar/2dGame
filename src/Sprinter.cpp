#include "Sprinter.h"
#include "configuration.h"
#include "functions.h"
#include "ImageDisplay.h"


Sprinter::Sprinter(float x, float y) : Enemy(x, y, conf::sprinter_hitbox.x, conf::sprinter_hitbox.y), charging(false), dashing(false), dash_starting_position(0), attacked_player(false) {
  type = "sprinter";
}

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

  State new_state;

  if (charging || dashing) {
    new_state = State::RUNNING;
  }
  else {
    new_state = State::IDLE;
  }

  if (new_state != current_state) {
    current_state = new_state;

    if (current_state == State::IDLE) {
      entity_texture = stay_texture;
    }
    else {
      entity_texture = run_texture;
    }
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
  sf::Sprite entity_sprite(entity_texture);

  entity_sprite.setPosition(position);

  entity_sprite.setOrigin({(float)entity_texture.getSize().x / 2, (float)entity_texture.getSize().y / 2});

  float scale_x = hitbox.x / entity_texture.getSize().x;
  float scale_y = hitbox.y / entity_texture.getSize().y;


  entity_sprite.setScale({scale_x * vision_direction, scale_y});

  entity_sprite.setRotation(sf::radians(rotation));

  window.draw(entity_sprite);

  if (draw_hitboxes) {
    draw_hitbox(window);
  }
}