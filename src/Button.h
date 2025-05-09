#pragma once
#include <string>
#include <SFML/Graphics.hpp>

class Button {
  sf::Vector2f position;
  sf::Vector2f size;
  std::string text;
  sf::Color color;
  sf::Color text_color;

  bool pressed;
  bool released;
public:
  Button(float x, float y, float width, float height, std::string text);
  Button(float width, float height, std::string text);
  Button(float width, float height);
  Button();

  void setPosition(float x, float y);
  void setSize(float width, float height);
  void setText(std::string text);
  void setColor(sf::Color color);
  void setTextColor(sf::Color text_color);

  sf::Vector2f getPosition();
  sf::Vector2f getSize();
  std::string getText();

  void updateAndShow(sf::RenderWindow& window);
  void update(sf::RenderWindow& window);
  void show(sf::RenderWindow& window);
  bool isPressed();
  bool isRealesed();
};