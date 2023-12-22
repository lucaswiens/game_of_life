#include <iostream>

#include "world.h"
#include "life.h"

int main (int argc, char *argv[]) {
    const size_t height      = (argc > 1) ? std::atoi(argv[1]) :  40;
    const size_t width       = (argc > 2) ? std::atoi(argv[2]) :  80;
    const size_t speed       = (argc > 3) ? std::atoi(argv[3]) :   1;
    const size_t cell_height = (argc > 4) ? std::atoi(argv[4]) :  20;
    const size_t cell_width  = (argc > 5) ? std::atoi(argv[5]) :  20;
    const double size        = (argc > 6) ? std::stod(argv[6]) : 0.9;

    std::cout << "Running with " << width << "x" << height << " with " << speed << " Hz" << std::endl;
    Life life(width, height, cell_width, cell_height, size, '#', '_', speed);
    life.Run();

    return 0;
}
