#include "Sword.h"
#include "configuration.h"
#include <iostream>
#include "ImageDisplay.h"
#include <cmath>

Sword::Sword(float x, float y) : Entity(x, y,conf::sword_hitbox.x, conf::sword_hitbox.y) {
    loadTexture();
}
Sword::Sword() : Sword(0, 0) {}



bool Sword::loadTexture() {
    if (!Obrazek(conf::swordImage, sword_texture)) {
        std::cerr << "Error loading texture" << std::endl;
        return false;
    }
    return true;
}

void Sword::update(float dt, const sf::Vector2f& playerPos, short attackDir) {

    if (isOnCooldown) {
        cooldownTimer += dt;
        if (cooldownTimer >= cooldownDuration) {
            isOnCooldown = false;
            cooldownTimer = 0.0f;
        }
    }

    if (isAttacking) {
        attackTimer += dt;

        float swingProgress = attackTimer / attackDuration;
        if (swingProgress > 1.0f) swingProgress = 1.0f;

        swingAngle = swingStartAngle + (swingEndAngle - swingStartAngle) * swingProgress;

         float swingRadius = 60.0f;

        float radians = swingAngle * 3.14159f / 180.0f;

        float swingX = cos(radians) * swingRadius;
        float swingY = sin(radians) * swingRadius;

        position = sf::Vector2f(playerPos.x + swingX * attackDir, playerPos.y + swingY);

        if (attackTimer >= attackDuration) {
            isAttacking = false;
            attackTimer = 0.0f;
            isOnCooldown = true;
            cooldownTimer = 0.0f;
            swingAngle = 0.0f;
        }
    }else {
        attackDirection = attackDir;
        float offsetX = 40.f * attackDir;
        float offsetY = -20.0f;
        position = sf::Vector2f(playerPos.x + offsetX, playerPos.y + offsetY);
    }
}

void Sword::draw(sf::RenderWindow& window) {
    if (!isAttacking && !draw_hitboxes) return;

    sf::Sprite sprite(sword_texture);

    sprite.setPosition(position);
    sprite.setOrigin({(float)sword_texture.getSize().x / 2, (float)sword_texture.getSize().y / 2});

    float scale_x = hitbox.x / sword_texture.getSize().x;
    float scale_y = hitbox.y / sword_texture.getSize().y;

    sprite.setScale({ scale_x, scale_y});

    sprite.setRotation(sf::radians(swingAngle));

    if (isAttacking) {
        window.draw(sprite);
    }
    if (draw_hitboxes) {
        draw_hitbox(window);
    }
}

void Sword::startAttack() {
    if (!isAttacking && !isOnCooldown) {
        isAttacking = true;
        attackTimer = 0.0f;
    }
}
bool Sword::isActive() const {
    return isAttacking;
}

sf::Vector2f Sword::getPosition() const {
    return position;
}

sf::Vector2f Sword::getSize() const {
    return hitbox;
}

float Sword::getDamage() const {
    return damage;
}

short Sword::getAttackDirection() const {
    return attackDirection;
}