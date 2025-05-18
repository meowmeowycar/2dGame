#include "MagicStaff.h"
#include "configuration.h"
#include "ImageDisplay.h"
#include "LevelHandler.h"
#include <cmath>

MagicStaff::MagicStaff(float x, float y) : Entity(x, y, conf::magicStaff_hitbox.x, conf::magicStaff_hitbox.y) {
    loadTextures();
}
MagicStaff::MagicStaff() : MagicStaff(0, 0) {}

bool MagicStaff::loadTextures() {
    if (!Obrazek(conf::magicStaffImage, entity_texture)) {
        std::cerr << "Error loading texture" << std::endl;
        return false;
    }

    if (!Obrazek(conf::magicProjectileImage, projectile_texture)) {
        std::cerr << "Error loading texture" << std::endl;
        return false;
    }

    return true;
}

void MagicStaff::update(float dt, const sf::Vector2f& playerPos, short attackDir, std::vector<Obstacle*>& obstacles, sf::Vector2f mousePos) {
    if (!acquired) return;

    if (isOnCooldown) {
        cooldownTimer += dt;
        if (cooldownTimer >= cooldownDuration) {
            isOnCooldown = false;
            cooldownTimer = 0;
        }
    }

    if (isAttacking) {
        attackTimer += dt;
        if (attackTimer >= attackDuration) {
            isAttacking = false;
            attackTimer = 0.0f;
            isOnCooldown = true;
            cooldownTimer = 0.0f;

            //pozycja wystrzelenia pocisku
            float offsetX = 50.0f * attackDir;
            float offsetY = -5.0f;
            sf::Vector2f projectilePos = sf::Vector2f(playerPos.x + offsetX, playerPos.y + offsetY);

            sf::Vector2f targetPos = sf::Vector2f(playerPos.x + 100.0f * attackDir, playerPos.y);


            fireProjectile(mousePos);
        }
    }

    for (int i = 0; i < projectiles.size(); i++) {
        projectiles[i].update(obstacles, dt);

        if (projectiles[i].getLifetime() > 2.0f) {
            projectiles.erase(projectiles.begin() + i);
            i--;
        }
    }

    attackDirection = attackDir;

    float offsetX = 30.f * attackDir;
    float offsetY = -10.0f;
    position = sf::Vector2f(playerPos.x + offsetX, playerPos.y + offsetY);
}

void MagicStaff::draw(sf::RenderWindow& window) {
    if (!acquired) return;

    sf::Sprite staff_sprite(entity_texture);

    staff_sprite.setPosition(position);
    staff_sprite.setOrigin({ (float)entity_texture.getSize().x / 2, (float)entity_texture.getSize().y / 2});

    float scale_x = hitbox.x / entity_texture.getSize().x;
    float scale_y = hitbox.y / entity_texture.getSize().y;

    staff_sprite.setScale({ scale_x * attackDirection, scale_y});


    window.draw(staff_sprite);

    for (auto& projectile : projectiles) {
        projectile.show(window);
    }

    if (draw_hitboxes) {
        draw_hitbox(window);
    }
}

void MagicStaff::startAttack() {
    if (!acquired) return;

    if (!isAttacking && !isOnCooldown) {
        isAttacking = true;
        attackTimer = 0.0f;
    }
}

bool MagicStaff::isActive() const {
    return isAttacking && acquired;
}

sf::Vector2f MagicStaff::getPosition() const {
    return position;
}

sf::Vector2f MagicStaff::getSize() const {
    return hitbox;
}

float MagicStaff::getDamage() const {
    return damage;
}

short MagicStaff::getAttackDirection() const {
    return attackDirection;
}

bool MagicStaff::isAcquired() const {
    return acquired;
}

void MagicStaff::setAcquired(bool value) {
    acquired = value;
}

void MagicStaff::fireProjectile(const sf::Vector2f& targetPos) {
    MagicProjectile projectile(position.x, position.y);
    projectile.setTexture(projectile_texture);

    sf::Vector2f direction = {targetPos.x - position.x, targetPos.y - position.y};
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length > 0) {
        direction.x /= length;
        direction.y /= length;
    }


    projectile.setVelocity({direction.x * conf::magic_projectile_speed, direction.y * conf::magic_projectile_speed});


    float angle = std::atan2(direction.y, direction.x) * 180.0f / 3.14159f;
    projectile.setRotation(angle);


    projectile.setDamage(damage);

    projectiles.push_back(projectile);
}

std::vector<MagicProjectile>& MagicStaff::getProjectiles() {
    return projectiles;
}

void MagicStaff::setProjectileTexture(sf::Texture texture) {
    projectile_texture = texture;
}