#include "MagicProjectile.h"
#include "configuration.h"
#include "ImageDisplay.h"


MagicProjectile::MagicProjectile(float x, float y) : Entity(x, y, conf::magicProjectile_hitbox.x, conf::magicProjectile_hitbox.y), lifetime(0) {
    hitbox_color = sf::Color::Red;
    gravity(false);
}

MagicProjectile::MagicProjectile() : MagicProjectile(0, 0) {}

bool MagicProjectile::load_textures() {
    if (!Obrazek(conf::magicProjectileImage, entity_texture)) {
        return false;
    }
    return true;
}

void MagicProjectile::update(std::vector<Obstacle*>& obstacles, float dt) {
    lifetime += dt;


    Entity::update(obstacles, dt);


    for (auto obstacle : obstacles) {
        sf::Vector2f distance = {obstacle->getPosition().x - position.x, obstacle->getPosition().y - position.y};
        if ((abs(distance.x) - hitbox.x / 2 - obstacle->getSize().x / 2) < 0 &&
            (abs(distance.y) - hitbox.y / 2 - obstacle->getSize().y / 2) < 0) {
            lifetime = 10.0f;
            break;
            }
    }
}

float MagicProjectile::getLifetime() const {
    return lifetime;
}

float MagicProjectile::getDamage() const {
    return damage;
}

void MagicProjectile::setDamage(float value) {
    damage = value;
}

void MagicProjectile::setColor(sf::Color color) {
    projectileColor = color;
}