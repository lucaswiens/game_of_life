#include "life.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Window/Event.hpp>

Life::Life(const size_t &width, const size_t &height, const size_t &cell_width, const size_t &cell_height, const double &size, const char &life_cell, const char &dead_cell, const int &speed) :
    width(width),
    height(height),
    cell_width(cell_width),
    cell_height(cell_height),
    size(size),
    world(World(height, width, life_cell, dead_cell)),
    window(sf::VideoMode(cell_height * height, cell_width * width), "Game of Life") {
    for (size_t row = 0; row < height; row++) {
        this->cells.push_back({});
        for (size_t column = 0; column < width; column++) {
            this->cells.back().push_back(sf::RectangleShape(sf::Vector2f(this->cell_height * this->size, this->cell_width * this->size)));
            this->cells.back().at(column).setPosition(this->cell_height * (row), this->cell_width * (column));
            this->cells.back().at(column).setFillColor(this->dead_color);
        }
    }
    this->window.setFramerateLimit(speed);

    this->play_game = true;
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
    while (this->window.pollEvent(event)) {
        if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q)) {
            this->window.close();
        }

        if (play_game && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            this->play_game = false;
        } else if (!play_game && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
            this->play_game = true;
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            const size_t &x = round(event.mouseButton.x / cell_width);
            const size_t &y = round(event.mouseButton.y / cell_height);
            this->world.ToggleCell(x, y);
        }
    }
};

void Life::Update() {
    if (play_game) { world.Update();}
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
    for (size_t row = 0; row < this->height; row++) {
        for (size_t column = 0; column < width; column++) {
            this->window.draw(cells.at(row).at(column));
        }
    }
    this->window.display();
};




