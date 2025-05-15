#include "Button.h"
#include "configuration.h"
#include "../cmake-build-release/_deps/sfml-src/extlibs/headers/miniaudio/miniaudio.h"

Button::Button(float x, float y, float width, float height, std::string text) : position({x, y}), size(width, height), text(text), text_size(35), color(sf::Color::Black), text_color(sf::Color::White), pressed(false), released(false) {
  char_lengths[48] = 0.56;  // 0
  char_lengths[49] = 0.49;  // 1
  char_lengths[50] = 0.56;  // 2
  char_lengths[51] = 0.56;  // 3
  char_lengths[52] = 0.56;  // 4
  char_lengths[53] = 0.56;  // 5
  char_lengths[54] = 0.56;  // 6
  char_lengths[55] = 0.56;  // 7
  char_lengths[56] = 0.56;  // 8
  char_lengths[57] = 0.56;  // 9

  char_lengths[65] = 0.67;  // A
  char_lengths[66] = 0.67;  // B
  char_lengths[67] = 0.72;  // C
  char_lengths[68] = 0.73;  // D
  char_lengths[69] = 0.67;  // E
  char_lengths[70] = 0.61;  // F
  char_lengths[71] = 0.78;  // G
  char_lengths[72] = 0.72;  // H
  char_lengths[73] = 0.27;  // I
  char_lengths[74] = 0.50;  // J
  char_lengths[75] = 0.66;  // K
  char_lengths[76] = 0.55;  // L
  char_lengths[77] = 0.83;  // M
  char_lengths[78] = 0.72;  // N
  char_lengths[79] = 0.78;  // O
  char_lengths[80] = 0.67;  // P
  char_lengths[81] = 0.78;  // Q
  char_lengths[82] = 0.72;  // R
  char_lengths[83] = 0.66;  // S
  char_lengths[84] = 0.61;  // T
  char_lengths[85] = 0.72;  // U
  char_lengths[86] = 0.67;  // V
  char_lengths[87] = 0.94;  // W
  char_lengths[88] = 0.67;  // X
  char_lengths[89] = 0.66;  // Y
  char_lengths[90] = 0.61;  // Z

  char_lengths[97] = 0.56;   // a
  char_lengths[98] = 0.56;   // b
  char_lengths[99] = 0.50;   // c
  char_lengths[100] = 0.56;  // d
  char_lengths[101] = 0.56;  // e
  char_lengths[102] = 0.263; // f
  char_lengths[103] = 0.56;  // g
  char_lengths[104] = 0.55;  // h
  char_lengths[105] = 0.22;  // i
  char_lengths[106] = 0.215; // j
  char_lengths[107] = 0.50;  // k
  char_lengths[108] = 0.22;  // l
  char_lengths[109] = 0.83;  // m
  char_lengths[110] = 0.56;  // n
  char_lengths[111] = 0.56;  // o
  char_lengths[112] = 0.56;  // p
  char_lengths[113] = 0.56;  // q
  char_lengths[114] = 0.34;  // r
  char_lengths[115] = 0.50;  // s
  char_lengths[116] = 0.28;  // t
  char_lengths[117] = 0.56;  // u
  char_lengths[118] = 0.50;  // v
  char_lengths[119] = 0.72;  // w
  char_lengths[120] = 0.50;  // x
  char_lengths[121] = 0.50;  // y
  char_lengths[122] = 0.50;  // z
}

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
  sf::Vector2f text_rect = {0, text_size * 1.5f};

  for (char character : text) {
    text_rect.x += char_lengths[character] * text_size;
  }

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