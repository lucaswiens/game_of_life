#include "life.h"
#include <SFML/Graphics/RectangleShape.hpp>

Life::Life(const size_t &width, const size_t &height, const char &life_cell, const char &dead_cell, const int &speed) :
    width(width),
    height(height),
    world(World(height, width, life_cell, dead_cell)),
    //window(sf::VideoMode(this->width * 50, this->height * 50), "Game of Life") {
    window(sf::VideoMode(600, 800), "Game of Life") {
    for (size_t row = 0; row < height; row++) {
        cells.push_back({});
        for (size_t column = 0; column < width; column++) {
            cells.back().push_back(sf::RectangleShape(sf::Vector2f(44, 44)));
            cells.back().at(column).setPosition(50 * (row), 50 * (column));
            cells.back().at(column).setFillColor(dead_color);
        }
    }
    window.setFramerateLimit(speed);
}

void Life::Run() {
    while (this->window.isOpen()) {
        this->ProcessEvents();
        this->Update();
        this->Render();
    }
}

void Life::ProcessEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            this->window.close();
        }
    }
};

void Life::Update() {
    world.Update();
    // this is inefficient because the char grid is updated independently
    for (size_t row = 0; row < this->height; row++) {
        for (size_t column = 0; column < width; column++) {
            if (world.IsAlive(row, column)) {
                cells.at(row).at(column).setFillColor(life_color);
            } else {
                cells.at(row).at(column).setFillColor(dead_color);
            }
        }
    }
};

void Life::Render() {
    this->window.clear(background_color);

    //std::cout << width << " " << this->height << std::endl;
    for (size_t row = 0; row < this->height; row++) {
        for (size_t column = 0; column < width; column++) {
            this->window.draw(cells.at(row).at(column));
        }
    }
    this->window.display();
};




