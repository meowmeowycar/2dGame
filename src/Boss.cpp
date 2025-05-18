#include "Boss.h"


Boss::Boss(float x, float y, short vision_direction) : Archer(x, y, vision_direction) {
    type = "boss";
    vision_distance = conf::boss_vision_distance;
    back_vision_distance = conf::boss_back_vision_distance;
    hitbox = conf::boss_hitbox;
    health = conf::boss_max_health;
}

Boss::Boss(float x, float y) : Boss(x, y, -1) {}

Boss::Boss() : Boss(0, 0) {}


void Boss::update(Player& player, std::vector<Obstacle*>& obstacles, float dt) {
    Enemy::update(player, obstacles, dt);

    if (see_player) {
        velocity.x = 0;
        if (shooting_timer.getElapsedTime().asSeconds() > 0.1) {
            shooting_timer.restart();
            shoot(player);
        }
    }

    for (int i = 0; i < arrows.size(); i++) {
        arrows[i].update(obstacles, dt);


        if (arrows[i].getLifetime() > 2) {
            arrows.erase(arrows.begin() + i);
            i--;
        } else if (abs(arrows[i].getPosition().x - player.getPosition().x) < player.getHitbox().x / 2 + conf::arrow_hitbox.x / 2 && abs(arrows[i].getPosition().y - player.getPosition().y) < player.getHitbox().y / 2 + conf::arrow_hitbox.y / 2) {
            player.reduce_health(conf::boss_arrow_damage);
            arrows.erase(arrows.begin() + i);
            i--;
        }
    }
}

void Boss::show(sf::RenderWindow& window) {
    Archer::show(window);
}
