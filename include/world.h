#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>
#include <array>

class World {
    private:
        size_t rows, columns, cycle = 0;
        char life_cell, dead_cell;
        std::vector<std::vector<char>> grid;
        std::vector<std::vector<char>> grid_last_cycle;
        bool CheckLife(const size_t &row, const size_t &column);
        size_t CountNeighbors(const size_t &row, const size_t &column);
        bool BuildFloater(const size_t &row, const size_t &column, const size_t &row_position, const size_t &column_position);
    public:
        World(const size_t &rows, const size_t &columns, const char &life_cell, const char &dead_cell);
        void Print();
        void Update();
        bool IsAlive(const size_t &row, const size_t&colum);
};

#endif
