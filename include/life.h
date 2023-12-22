#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SFML/Graphics.hpp>

#include <cmath>

#include "world.h"

class Life {
private:
    World world;
    sf::RenderWindow window;
    std::vector<std::vector<sf::RectangleShape>> cells;
    sf::Color background_color = sf::Color(0x1E, 0x1E, 0x2E);
    sf::Color life_color = sf::Color(0xE1, 0xE1, 0xE2);
    sf::Color dead_color = sf::Color(0x2E, 0x2E, 0x3E);

    size_t width, height, cell_width, cell_height, frames_per_second;
    double size, update_time_miliseconds, update_time;
    bool play_game, mouse_hold;

    //void init();
    void ProcessEvents();
    void Update();
    void Render();

public:
    Life(const size_t &, const size_t &, const size_t &, const size_t &, const double &, const char &, const char &, const double &, const size_t &);
    void Run();
};

#endif
