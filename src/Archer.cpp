#include "Archer.h"

#include <iostream>

#include "configuration.h"
#include "Enemy.h"
#include "ImageDisplay.h"

Archer::Archer(float x, float y) : Enemy(x, y, conf::archer_hitbox.x, conf::archer_hitbox.y) {}
Archer::Archer() : Archer(0, 0) {}

void Archer::update(Player& player, std::vector<Obstacle*>& obstacles, float dt) {
  Enemy::update(player, obstacles, dt);

  if (see_player) {
    velocity.x = 0;
    if (shooting_timer.getElapsedTime().asSeconds() > 2) {
      shooting_timer.restart();
      shoot(player);
    }
  }

  for (int i = 0; i < arrows.size(); i++) {
    arrows[i].update(obstacles, dt);


    if (arrows[i].getLifetime() > 1) {
      arrows.erase(arrows.begin() + i);
      i--;
    } else if (abs(arrows[i].getPosition().x - player.getPosition().x) < player.getHitbox().x / 2 + conf::arrow_hitbox.x / 2 && abs(arrows[i].getPosition().y - player.getPosition().y) < player.getHitbox().y / 2 + conf::arrow_hitbox.y / 2) {
      player.reduce_health(conf::archer_damage);
      arrows.erase(arrows.begin() + i);
      i--;
    }
  }
}

void Archer::shoot(Player& player) {
  arrows.push_back(*new Arrow(position.x, position.y));
  arrows.back().setTexture(arrow_texture);
  arrows.back().setVelocity(sf::Vector2f({player.getPosition().x - position.x, player.getPosition().y - position.y - (conf::player_hitbox.y / 4)}).normalized() * conf::arrow_speed);
  arrows.back().setRotation(sf::Vector2f({player.getPosition().x - position.x, player.getPosition().y - position.y - (conf::player_hitbox.y / 4)}).angle().asRadians());
  arrows.back().gravity(false);
}

bool Archer::load_textures() {
  if (!Obrazek(conf::archerImage, entity_texture)) {
    return false;
  }

  if (!Obrazek(conf::arrowImage, arrow_texture)) {
    return false;
  }

  return true;
}

void Archer::show(sf::RenderWindow& window) {
  Enemy::show(window);

  for (int i = 0; i < arrows.size(); i++) {
    arrows[i].show(window);
  }
}