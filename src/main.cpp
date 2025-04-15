#include <SFML/Graphics.hpp>
#include "events.h"
#include "ImageDisplay.h"
  int main()
{
    sf:: Texture backgroundTexture;
    if (!Obrazek("../../Media/Ludzik.png", backgroundTexture)) {
        return -1;
    }
    
    sf::Sprite Spirite(backgroundTexture);
  
  auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Game", sf::State::Fullscreen);
    window.setFramerateLimit(144);
  

    while (window.isOpen())
    {
        processEvents(window);

        window.clear(sf::Color::Red);
        window.draw(Spirite);
        window.display();
    }
}