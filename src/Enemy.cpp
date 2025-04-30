#include "Enemy.h"
#include "configuration.h"
#include <SFML/Graphics.hpp>
#include "functions.h"


Enemy::Enemy(float x, float y, float width, float height) : Entity(x, y, width, height), see_player(false) {}

Enemy::Enemy(float width, float height) : Enemy(0, 0, width, height) {}


float Enemy::getHealth() {
  return health;
}

void Enemy::update(Player& player, std::vector<Obstacle>& obstacles, float dt) {
  Entity::update(obstacles, dt);
  check_vision(player, obstacles);
}

void Enemy::check_vision(Player& player, std::vector<Obstacle>& obstacles) {
  sf::Vector2f distance = {player.getPosition().x - position.x, player.getPosition().y - position.y};

  see_player = false;

  if(distance.length() < conf::vision_distance) {
    see_player = true;

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
        bool blocked_x = abs(checked_point.x - obstacles[j].getPosition().x) - obstacles[j].getSize().x / 2 <= 0;
        bool blocked_y = abs(checked_point.y - obstacles[j].getPosition().y) - obstacles[j].getSize().y / 2 <= 0;

        if(blocked_x && blocked_y) {
          see_player = false;
          i = steps;
          break;
        }
      }
    }
  }
}

void Enemy::draw_hitbox(sf::RenderWindow& window) {
  sf::RectangleShape hitbox_shape({hitbox.x - 2, hitbox.y - 2});
  hitbox_shape.setPosition(position);
  hitbox_shape.setOrigin({hitbox.x / 2, hitbox.y / 2});
  hitbox_shape.setFillColor(sf::Color::Transparent);
  if(see_player)
    hitbox_shape.setOutlineColor(sf::Color::Green);
  else
    hitbox_shape.setOutlineColor(sf::Color::Yellow);
  hitbox_shape.setOutlineThickness(1);
  window.draw(hitbox_shape);
}


void Enemy::show(sf::RenderWindow& window) {
  sf::Sprite player_sprite(entity_texture);
  player_sprite.setPosition(position);
  player_sprite.setOrigin({(float) entity_texture.getSize().x / 2, (float) entity_texture.getSize().y / 2});
  player_sprite.setScale({hitbox.x / conf::player_hitbox.x, hitbox.y / conf::player_hitbox.y});
  window.draw(player_sprite);

  if (conf::draw_hitboxes)
    draw_hitbox(window);
}
