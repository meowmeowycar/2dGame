#include "Button.h"
#include "configuration.h"

Button::Button(float x, float y, float width, float height, std::string text) : position({x, y}), size(width, height), text(text)  {}

Button::Button(float width, float height, std::string text) : Button(0, 0, width, height, text) {}

Button::Button(float width, float height): Button(width, height, "Text") {}

Button::Button(): Button(100, 100) {}


void Button::setPosition(float x, float y) {
  this->position = sf::Vector2f(x, y);
}

void Button::setSize(float width, float height) {
  this->size = sf::Vector2f(width, height);
}

void Button::setText(std::string text) {
  this->text = text;
}

void Button::setColor(sf::Color color) {
  this->color = color;
}

void Button::setTextColor(sf::Color text_color) {
  this->text_color = text_color;
}


sf::Vector2f Button::getPosition() {
  return position;
}

sf::Vector2f Button::getSize() {
  return size;
}

std::string Button::getText() {
  return text;
}


void Button::updateAndShow(sf::RenderWindow &window) {
  update(window);
  show(window);
}

void Button::update(sf::RenderWindow &window) {
  sf::Vector2f mouse_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

  bool mouse_on_X = abs(mouse_position.x - position.x) <= size.x;
  bool mouse_on_Y = abs(mouse_position.y - position.y) <= size.y;

  if(mouse_on_X && mouse_on_Y) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      pressed = true;
    } else if(pressed) {
      pressed = false;
      released = true;
    } else {
      pressed = false;
      released = false;
    }
  } else {
    pressed = false;
    released = false;
  }
}

void Button::show(sf::RenderWindow &window) {
  sf::RectangleShape button;
  button.setPosition(position);
  button.setSize(size);
  button.setFillColor(color);
  button.setOrigin({size.x / 2, size.y / 2});

  window.draw(button);

  sf::Text button_text(conf::arial);
  button_text.setPosition(position);
  button_text.setFillColor(text_color);
  button_text.setCharacterSize(35);
  button_text.setString(text);
  button_text.setOrigin({size.x / 2, size.y / 2});

  window.draw(button_text);
}

bool Button::isPressed() {
  return pressed;
}

bool Button::isRealesed() {
  return released;
}