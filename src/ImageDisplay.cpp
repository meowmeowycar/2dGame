#include "ImageDisplay.h"

#include <iostream>
#include <SFML/Graphics.hpp>

bool Obrazek(const std::string& Uerel, sf::Texture& Tex) {

    sf::Image image;
    if (!image.loadFromFile(Uerel)) {
        std::cout << "Error loading texture" << std::endl;
        return false;
    }

    if (!Tex.loadFromImage(image)) {
        std::cout << "Error loading texture" << std::endl;
        return false;
    }

    return true;
}