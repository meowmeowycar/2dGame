#include "Stalker.h"
#include "configuration.h"
#include "functions.h"

Stalker::Stalker(float x, float y) : Enemy(x, y, conf::stalker_hitbox.x, conf::stalker_hitbox.y), is_touching_player(false) {
  vision_direction = -1;
}
Stalker::Stalker() : Stalker(0, 0) {}

void Stalker::update(Player& player, std::vector<Obstacle>& obstacles, float dt) {
  Enemy::update(player, obstacles, dt);
  check_touching(player);

  if (see_player) {
    move_to_player(player);
  } else {
    velocity.x = 0;
  }

  if (is_touching_player && attack_timer.getElapsedTime().asSeconds() > 1) {
    attack_timer.restart();
    attack(player);
  }
}

void Stalker::check_touching(Player& player) {
  sf::Vector2f distance = {player.getPosition().x - position.x, player.getPosition().y - position.y};

  is_touching_player = false;

  if (distance.length() < conf::player_hitbox.x / 2 + hitbox.x / 2)
    is_touching_player = true;
}


void Stalker::move_to_player(Player& player) {
  if (!is_touching_player) {
    velocity.x = sign(player.getPosition().x - position.x) * 150;
  } else
    velocity.x = 0;
}

void Stalker::attack(Player& player) {
  player.reduce_health(conf::stalker_damage);
}