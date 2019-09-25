#include <iostream>

#include "Game.hpp"

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    try
    {
        color_shootout::Game game;
        game.run();
    }
    catch (std::exception &e)
    {
        std::cerr << "An exception has occured! The application will be terminated.\n"
            << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
