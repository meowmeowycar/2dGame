#pragma once
#include "Entity.h"
#include <SFMl/Graphics.hpp>
#include "MagicProjectile.h"

class MagicStaff : public Entity{
    sf::Texture staff_texture;
    bool isAttacking = false;
    float attackDuration = 0.4f;
    float attackTimer = 0.0f;
    float damage = 60.0f;

    float cooldownDuration = 0.1f;
    float cooldownTimer = 0.0f;
    bool isOnCooldown = false;

    short attackDirection = 1;

    bool acquired = false;

    std::vector<MagicProjectile> projectiles;
    sf::Texture projectile_texture;

public:
    MagicStaff(float x, float y);
    MagicStaff();
    bool loadTextures();
    void update(float dt, const sf::Vector2f& playerPos, short attackDir, std::vector<Obstacle*>& obstacles, sf::Vector2f mousePos);
    void draw(sf::RenderWindow& window);

    void startAttack();
    bool isActive() const;
    float getDamage() const;
    short getAttackDirection() const;

    sf::Vector2f getPosition() const;
    sf::Vector2f getSize() const;

    bool isAcquired() const;
    void setAcquired(bool acquired);

    void fireProjectile(const sf::Vector2f& playerPos);
    std::vector<MagicProjectile>& getProjectiles();
    void setProjectileTexture(sf::Texture texture);
};
