#include <iostream>

#include "world.h"
#include "life.h"

int main (int argc, char *argv[]) {
    const int height = (argc > 1) ? std::atoi(argv[1]) :  80;
    const int width  = (argc > 2) ? std::atoi(argv[2]) :  40;
    const int speed  = (argc > 3) ? std::atoi(argv[3]) : 100;
    std::cout << "Running with " << width << "x" << height << " with " << speed << " Hz" << std::endl;
    Life life(width, height, '#', '_', speed);
    life.Run();

    return 0;
}
