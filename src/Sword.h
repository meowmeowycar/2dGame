#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"


class Sword : public Entity{
  sf::Texture sword_texture;
  bool isAttacking = false;
  float attackDuration = 0.3f;
  float attackTimer = 0.0f;
  short attackDirection = 1;
  float scale = 0.8f;
  float damage = 30.0f;

  float cooldownDuration = 0.5f;
  float cooldownTimer = 0.0f;
  bool isOnCooldown = false;


  float swingAngle = 0.0f;
  float swingStartAngle = -60.0f;
  float swingEndAngle = 60.0f;

public:
  Sword(float x, float y);
  Sword();
  bool loadTexture();
  void update(float dt, const sf::Vector2f& playerPos, short attackDir);
  void draw(sf::RenderWindow& window);
  void startAttack();
  bool isActive() const;

  sf::Vector2f getPosition() const;
  sf::Vector2f getSize() const;

  float getDamage() const;

  short getAttackDirection() const;

};
