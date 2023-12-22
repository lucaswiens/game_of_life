#ifndef WORLD_H
#define WORLD_H

#include <array>
#include <iostream>
#include <vector>

class World {
private:
  size_t rows, columns, cycle = 0;
  char life_cell, dead_cell;
  std::vector<std::vector<bool>> grid;
  std::vector<std::vector<bool>> grid_last_cycle;
  bool CheckLife(const size_t &, const size_t &);
  size_t CountNeighbors(const size_t &, const size_t &);
  bool BuildFloater(const size_t &, const size_t &, const size_t &, const size_t &);

public:
  World(const size_t &, const size_t &, const char &, const char &);
  void ToggleCell(const size_t &, const size_t &);
  void Print();
  void Update();
  bool IsAlive(const size_t &, const size_t &);
};

#endif
