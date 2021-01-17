#include "Game.h"

int main()
{
    // Create an object of ApplicationManager
    Game game;
    while (!game.exited())
    {
        // Read new user (or whatever else)
        game.readInterfaceInput();
        game.moveFlippers(); // Move flippers
        // Simulate the game for one more frame
        game.simulate();
        game.GameOver();
        // Update the game graphical interface
        game.updateInterfaceOutput();
    }

    return 0;
}
