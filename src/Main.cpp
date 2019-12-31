/*
** EPITECH PROJECT, 2019
** QuadtreeDemo
** File description:
** Main.cpp
*/

#include <iostream>

#include "App.hpp"

static void printHelp()
{
    std::cout << "Click anywhere inside the window to generate particles.\n"
                 "Press S to slow down time by 50%.\n"
                 "Press F to freeze time.\n"
                 "Press G to toggle gravity on/off.\n"
                 "Press H to hide/show the quadtree.\n"
                 "Press T to hide/show data or status text.\n"
                 "Press V to toggle VSync on/off. (Default: ON)\n"
                 "Press Space to remove every particles.\n"
                 "Press ESC, DEL or Q to exit the program.\n"
              << std::flush;
}

int main(const int, const char *const *)
{
    printHelp();

    try {
        App app;

        app.run();
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Uncaught exception: " << e.what() << '\n';
        return 1;
    }
}
