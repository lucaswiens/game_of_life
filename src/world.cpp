#include "world.h"

World::World(const size_t &rows, const size_t &columns, const char &life_cell, const char &dead_cell) : rows(rows + 2), columns(columns + 2), life_cell(life_cell), dead_cell(dead_cell) {
    for (size_t row = 0; row < this->rows; row++) {
        this->grid.push_back(std::vector<char>(this->columns, this->dead_cell));
        for (size_t column = 0; column < this->columns; column++) {
            if (this->BuildFloater(row, column, 3, 3)) {
                this->grid.at(row).at(column) = this->life_cell;
            }
        }
    }
}

bool World::BuildFloater(const size_t &row, const size_t &column, const size_t &row_position, const size_t &column_position) {
    if (row_position + 2 > this->rows || column_position + 2 > this->columns) { return false;}
    return ((row == row_position && column == column_position) ||
            (row == row_position + 1 && column == column_position + 1) ||
            (row == row_position + 1 && column == column_position + 2) ||
            (row == row_position + 2 && column == column_position) ||
            (row == row_position + 2 && column == column_position + 1));
}

void World::Print() {
    std::cout << "Generation: " << this->cycle << "\n";
    for (size_t row = 1; row < this->rows - 1; row++) {
        for (size_t column = 1; column < this->columns - 1; column++) {
            std::cout << this->grid.at(row).at(column);
        }
        std::cout << "\n";
    }
    std::cout << std::flush;
    std::cout << "\033[" << this->rows + 1 << "A\r"; // reset cursor position
}

void World::Update() {
    this->grid_last_cycle = this->grid;
    for (size_t row = 1; row < this->rows - 1; row++) {
        for (size_t column = 1; column < this->columns - 1; column++) {
            if (this->CheckLife(row, column)) {
                this->grid.at(row).at(column) = this->life_cell;
            } else {
                this->grid.at(row).at(column) = this->dead_cell;
            }
        }
    }
    this->cycle++;
}

// bug they all die no matter what
bool World::CheckLife(const size_t &row, const size_t &column) {
    const bool &alive = this->grid_last_cycle.at(row).at(column) != this->dead_cell;
    const size_t &number_of_life_neighbors = this->CountNeighbors(row, column);
    if (alive) {
        this->grid.at(row).at(column) = (char)number_of_life_neighbors;
        return 1 < number_of_life_neighbors && number_of_life_neighbors < 4;
    } else {
        this->grid.at(row).at(column) = (char)number_of_life_neighbors;
        return number_of_life_neighbors == 3;
    }
}

// todo maybe add option to see world as closed
size_t World::CountNeighbors(const size_t &row, const size_t &column) {
    size_t number_of_life_neighbors = 0;
    size_t row_neighbor = 0, column_neighbor = 0;

    for (int row_index = -1; row_index < 2; row_index++) {
        row_neighbor = row + row_index;
        for (int column_index = -1; column_index < 2; column_index++) {
            column_neighbor = column + column_index;
            if (this->grid_last_cycle.at(row_neighbor).at(column_neighbor) != this->dead_cell) {
                number_of_life_neighbors++;
            }
        }
    }
    if (this->grid_last_cycle.at(row).at(column) != this->dead_cell) {
        number_of_life_neighbors--;
    } // do not count the center cell
    return number_of_life_neighbors;
}

void World::ToggleCell(const size_t &row, const size_t &column) {
    if (IsAlive(row, column)) {
        this->grid.at(row).at(column) = this->dead_cell;
    } else {
        this->grid.at(row).at(column) = this->life_cell;
    }
}
bool World::IsAlive(const size_t &row, const size_t &column) {
    return this->grid.at(row).at(column) == this->life_cell;
}
