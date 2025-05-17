#include "Semi_obstacle.h"
#include "configuration.h"
#include "ImageDisplay.h"

Semi_obstacle::Semi_obstacle(float x1, float y1, float x2, float y2) : Obstacle(x1, y1, x2, y2) {
    type = "semi";
}

Semi_obstacle::Semi_obstacle(float width, float height) : Semi_obstacle(-width / 2, -height / 2, width / 2, height / 2) {}

bool Semi_obstacle::load_texture() {
    if (!Obrazek(conf::semiWallImage1, obstacle_left_texture)) {
        return false;
    }

    if (!Obrazek(conf::semiWallImage2, obstacle_right_texture)) {
        return false;
    }

    if (!Obrazek(conf::semiWallImage3, obstacle_texture)) {
        return false;
    }

    return true;
}

void Semi_obstacle::setTextures(sf::Texture& left_texture, sf::Texture& middle_texture, sf::Texture& right_texture) {
    this->obstacle_left_texture = left_texture;
    this->obstacle_texture = middle_texture;
    this->obstacle_right_texture = right_texture;
}


void Semi_obstacle::show(sf::RenderWindow &window) {
    float obstacle_scale = size.y / obstacle_left_texture.getSize().y;

    sf::Sprite obstacle_left_sprite(obstacle_left_texture);
    obstacle_left_sprite.setPosition(position);
    obstacle_left_sprite.setOrigin({size.x / obstacle_scale / 2, size.y / obstacle_scale / 2});
    if (size.x < obstacle_left_texture.getSize().x * obstacle_scale)
        obstacle_left_sprite.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(size.x / obstacle_scale, size.y / obstacle_scale)));
    obstacle_left_sprite.setScale({obstacle_scale, obstacle_scale});
    window.draw(obstacle_left_sprite);

    if (size.x > obstacle_left_texture.getSize().x * obstacle_scale) {
        sf::Sprite obstacle_right_sprite(obstacle_right_texture);
        obstacle_right_sprite.setPosition({position.x + size.x - obstacle_right_texture.getSize().x * obstacle_scale, position.y});
        obstacle_right_sprite.setOrigin({size.x / obstacle_scale / 2, size.y / obstacle_scale / 2});
        if (size.x < obstacle_right_texture.getSize().x * obstacle_scale + obstacle_left_texture.getSize().x * obstacle_scale) {
            obstacle_right_sprite.setPosition({position.x + obstacle_left_texture.getSize().x * obstacle_scale, position.y});
            obstacle_right_sprite.setTextureRect(sf::IntRect(sf::Vector2i(obstacle_left_texture.getSize().x + obstacle_right_texture.getSize().x - size.x / obstacle_scale, 0), sf::Vector2i(size.x / obstacle_scale - obstacle_left_texture.getSize().x, obstacle_right_texture.getSize().y)));
        }
        obstacle_right_sprite.setScale({obstacle_scale, obstacle_scale});
        window.draw(obstacle_right_sprite);
    }

    if (size.x > obstacle_left_texture.getSize().x * obstacle_scale + obstacle_right_texture.getSize().x * obstacle_scale) {
        obstacle_texture.setRepeated(true);

        sf::Sprite obstacle_sprite(obstacle_texture);
        obstacle_sprite.setPosition({position.x + obstacle_left_texture.getSize().x * obstacle_scale, position.y});
        obstacle_sprite.setOrigin({size.x / obstacle_scale / 2, size.y / obstacle_scale / 2});
        obstacle_sprite.setTextureRect(sf::IntRect({0, 0}, sf::Vector2i(size.x / obstacle_scale - obstacle_left_texture.getSize().x - obstacle_right_texture.getSize().x, obstacle_texture.getSize().y)));
        obstacle_sprite.setScale({obstacle_scale, obstacle_scale});
        window.draw(obstacle_sprite);
    }

    if (conf::draw_hitboxes)
        draw_hitbox(window);
}