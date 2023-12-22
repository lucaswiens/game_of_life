#include "world.h"

World::World(const size_t &rows, const size_t &columns, const char &life_cell, const char &dead_cell) : rows(rows+2), columns(columns+2), life_cell(life_cell), dead_cell(dead_cell) {
    for (size_t row = 0; row < this->rows; row++) {
        this->grid.push_back(std::vector<bool>(this->columns, false));
        for (size_t column = 0; column < this->columns; column++) {
            if (this->BuildFloater(row, column, 3, 3)) {
                this->grid.at(row).at(column) = true;
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
    for (size_t row = 0; row < this->rows; row++) {
        for (size_t column = 0; column < this->columns; column++) {
            if (this->grid.at(row).at(column)) {
                std::cout << this->life_cell;
            } else {
                std::cout << this->dead_cell;
            }
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
                this->grid.at(row).at(column) = true;
            } else {
                this->grid.at(row).at(column) = false;
            }
        }
    }
    this->cycle++;
}

bool World::CheckLife(const size_t &row, const size_t &column) {
    const size_t &number_of_life_neighbors = this->CountNeighbors(row, column);
    if (this->grid_last_cycle.at(row).at(column)) {
        return number_of_life_neighbors == 3 || number_of_life_neighbors == 2;
    } else {
        return number_of_life_neighbors == 3;
    }
}

size_t World::CountNeighbors(const size_t &row, const size_t &column) {
    size_t number_of_life_neighbors = 0;

    size_t row_neighbor, column_neighbor;
    for (int row_index = -1; row_index < 2; row_index++) {
        row_neighbor = row + row_index;
        for (int column_index = -1; column_index < 2; column_index++) {
            column_neighbor = column + column_index;
            if (this->grid_last_cycle.at(row_neighbor).at(column_neighbor)) {
                number_of_life_neighbors++;
            }
        }
    }

    // do not count the center cell
    if (this->grid_last_cycle.at(row).at(column)) {
        number_of_life_neighbors--;
    }

    return number_of_life_neighbors;
}

void World::ToggleCell(const size_t &row_, const size_t &column_) {
    const size_t row = row_ + 1;
    const size_t column = column_ + 1;
    this->grid.at(row).at(column) = !this->grid.at(row).at(column);
}
bool World::IsAlive(const size_t &row, const size_t &column) {
    return this->grid.at(row + 1).at(column + 1);
}
