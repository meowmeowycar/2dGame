#pragma once
#include "Entity.h"
#include <SFML/Graphics.hpp>

class MagicProjectile : public Entity {
private:
    float lifetime;
    float damage = 20.0f;
    sf::Color projectileColor;

public:
    MagicProjectile(float x, float y);
    MagicProjectile();

    void update(std::vector<Obstacle*>& obstacles, float dt) override;
    bool load_textures() override;

    float getLifetime() const;
    float getDamage() const;
    void setDamage(float value);
    void setColor(sf::Color color);
};