#include "FPS.h"
#include <SFML/Graphics.hpp>
#include <cmath>
#include "configuration.h"

float FPS::fps_sum = 0;
int FPS::fps_count = 0;
float FPS::fps_array[conf::fps_accuracy];
sf::Text FPS::fps_text(conf::arial);

void FPS::show_fps(sf::RenderWindow& window, float dt) {
    fps_text.setCharacterSize(30);
    fps_text.setFillColor(sf::Color::Red);
    fps_text.setPosition({conf::window_size_f.x - 170, 0});

    std::stringstream ss;

    fps_sum += 1 / dt;

    if (fps_count < conf::fps_accuracy) {
        ss<<"FPS: "<<std::round(fps_sum / fps_count);
    } else {
        fps_sum -= fps_array[fps_count % conf::fps_accuracy];
        ss<<"FPS: "<<std::round(fps_sum / conf::fps_accuracy);
    }

    fps_array[fps_count % conf::fps_accuracy] = 1 / dt;

    fps_text.setString(ss.str().c_str());
    window.draw(fps_text);

    fps_count++;
}