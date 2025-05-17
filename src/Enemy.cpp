#include "Enemy.h"
#include "configuration.h"
#include <SFML/Graphics.hpp>
#include "functions.h"
#include "Sword.h"
#include <iostream>



Enemy::Enemy(float x, float y, float width, float height) : Entity(x, y, width, height), see_player(false), vision_direction(-1), max_health(35), health(max_health), type("none") {}

Enemy::Enemy(float width, float height) : Enemy(0, 0, width, height) {}


float Enemy::getHealth() {
  return health;
}

std::string Enemy::getType() {
  return type;
}

void Enemy::reduce_health(float damage) {
  health -= damage;
  hit_effect_delay.restart();
}

void Enemy::update(Player& player, std::vector<Obstacle*>& obstacles, float dt) {
  Entity::update(obstacles, dt);

  check_vision(player, obstacles);

  if (see_player) {
    hitbox_color = sf::Color::Green;
  } else {
    hitbox_color = sf::Color::Yellow;
  }

  if (hit_effect_delay.getElapsedTime().asSeconds() < 0.2f) {
    hitbox_color = sf::Color::Red;
  }

  Sword& sword = player.getSword();

  static sf::Clock damage_cooldown;


  if (sword.isActive()) {

    sf::Vector2f sword_pos = sword.getPosition();

    float dist_x = abs(sword_pos.x - position.x);
    float dist_y = abs(sword_pos.y - position.y);

    float max_dist_x = (sword.getSize().x + hitbox.x) / 2.0f;
    float max_dist_y = (sword.getSize().y + hitbox.y) / 2.0f;

    if (dist_x <= max_dist_x && dist_y <= max_dist_y) {
      bool correct_direction = (sword.getAttackDirection() == sign(position.x - player.getPosition().x));

      if (correct_direction && damage_cooldown.getElapsedTime().asSeconds() >= 0.5f) {
        reduce_health(sword.getDamage());

        std::cout << "Health: " << health;

        damage_cooldown.restart();

      }
    }
  }
}

void Enemy::check_vision(Player& player, std::vector<Obstacle*>& obstacles) {
  sf::Vector2f distance = {player.getPosition().x - position.x, player.getPosition().y - position.y};

  see_player = false;

  bool vision_blocked = false;

  if(distance.length() < conf::vision_distance) {
    float steps = 0;
    sf::Vector2f step = {0, 0};
    sf::Vector2f checked_point = {position.x, position.y};

    if(abs(distance.x) > abs(distance.y)) {
      steps = abs(distance.x);
      step.x = distance.x / abs(distance.x);
      step.y = distance.y / abs(distance.x);
    } else if(abs(distance.y) > abs(distance.x)) {
      steps = abs(distance.y);
      step.x = distance.x / abs(distance.y);
      step.y = distance.y / abs(distance.y);
    } else {
      steps = abs(distance.x);
      step.x = sign(distance.x);
      step.y = sign(distance.y);
    }

    for(int i = 0; i < steps; i++) {
      checked_point.x += step.x;
      checked_point.y += step.y;

      for(int j = 0; j < obstacles.size(); j++) {
        bool blocked_x = abs(checked_point.x - (*obstacles[j]).getPosition().x) - (*obstacles[j]).getSize().x / 2 <= 0;
        bool blocked_y = abs(checked_point.y - (*obstacles[j]).getPosition().y) - (*obstacles[j]).getSize().y / 2 <= 0;

        if(blocked_x && blocked_y) {
          vision_blocked = true;
          i = steps;
          break;
        }
      }
    }
  }

  if (distance.length() < conf::vision_distance && sign(distance.x) == vision_direction && !vision_blocked) {
    see_player = true;
  } else if (distance.length() < conf::back_vision_distance && sign(distance.x) != vision_direction && !vision_blocked) {
    if (turn_delay.getElapsedTime().asSeconds() > 0.5) {
      turn_delay.restart();
      vision_direction = sign(player.getPosition().x - position.x);
    }
  } else {
    turn_delay.restart();
  }
}

void Enemy::show(sf::RenderWindow& window) {
  Entity::show(window);

  if (health < max_health) {
    sf::RectangleShape enemy_healthbar({max_health, 5});
    enemy_healthbar.setFillColor(sf::Color::Black);
    enemy_healthbar.setPosition({position.x - max_health / 2 - 1, position.y - 70});
    enemy_healthbar.setOutlineColor(sf::Color::White);
    enemy_healthbar.setOutlineThickness(1);

    window.draw(enemy_healthbar);

    if (health > 0) {
      sf::RectangleShape enemy_health_level({health, 5});
      enemy_health_level.setFillColor(sf::Color::Red);
      enemy_health_level.setPosition({position.x - max_health / 2, position.y - 70});

      window.draw(enemy_health_level);
    }
  }

  if (draw_hitboxes) {
    sf::RectangleShape line({(conf::vision_distance + conf::back_vision_distance) * vision_direction, 1.0f});
    line.setPosition({position.x - conf::back_vision_distance * vision_direction, position.y});
    line.setFillColor(sf::Color::Red);

    window.draw(line);
  }
}