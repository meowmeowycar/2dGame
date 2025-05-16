#include "Button.h"
#include "configuration.h"
#include "char_lengths.h"

Button::Button(float x, float y, float width, float height, std::string text) : position({x, y}), size(width, height), text(text), text_size(35), color(sf::Color::Black), text_color(sf::Color::White), pressed(false), released(false) {}

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
  this->currentColor = color;

  this->activeColor = sf::Color(
   std::min(color.r + 100, 255),
   std::min(color.g + 100, 255),
   std::min(color.b + 100, 255),
   color.a
 );
}

void Button::setTextColor(sf::Color text_color) {
  this->text_color = text_color;
  this->text_currentColor = text_color;
}

void Button::setTextSize(float size) {
  text_size = size;
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

float Button::getTextSize() {
  return text_size;
}


void Button::updateAndShow(sf::RenderWindow &window) {
  update(window);
  show(window);
}

void Button::update(sf::RenderWindow &window) {
  sf::Vector2f mouse_position = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

  bool mouse_on_X = abs(mouse_position.x - position.x) <= size.x / 2;
  bool mouse_on_Y = abs(mouse_position.y - position.y) <= size.y / 2;


  if(mouse_on_X && mouse_on_Y) {
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      pressed = true;
      currentColor = activeColor;
    } else if(pressed) {
      pressed = false;
      released = true;
    } else {
      pressed = false;
      released = false;
      currentColor = color;
    }
  } else {
    pressed = false;
    released = false;
    currentColor = color;
  }
}

void Button::show(sf::RenderWindow &window) {
  sf::RectangleShape button;
  button.setPosition(position);
  button.setSize(size);
  button.setFillColor(currentColor);
  button.setOrigin({size.x / 2, size.y / 2});

  window.draw(button);

  sf::Text button_text(conf::arial);
  button_text.setPosition(position);
  button_text.setFillColor(text_currentColor);
  button_text.setCharacterSize(text_size);
  button_text.setString(text);
  sf::Vector2f text_rect = {calculate_string_length("arial", text, text_size), text_size * 1.5f};
  button_text.setOrigin({text_rect.x / 2, text_rect.y / 2});

  window.draw(button_text);


  // TESTS

  /*
  sf::RectangleShape line1;
  line1.setPosition(position);
  line1.setSize({1, size.y});
  line1.setFillColor(sf::Color::White);
  line1.setOrigin({1, size.y / 2});

  sf::RectangleShape line2;
  line2.setPosition(position);
  line2.setSize({size.x, 1});
  line2.setFillColor(sf::Color::White);
  line2.setOrigin({size.x / 2, 1});

  sf::RectangleShape outline;
  outline.setPosition(position);
  outline.setSize(text_rect);
  outline.setFillColor(sf::Color::Transparent);
  outline.setOutlineColor(sf::Color::White);
  outline.setOutlineThickness(2);
  outline.setOrigin({text_rect.x / 2, text_rect.y / 2});

  window.draw(line2);
  window.draw(line1);
  window.draw(outline);
  */
}

bool Button::isPressed() {
  return pressed;
}

bool Button::isReleased() {
  bool temp = released;
  released = false;
  return temp;
}