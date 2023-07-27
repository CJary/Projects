#include <iostream>
#include "Game.h"

int main() {
    // Initialize the game engine
    Game game;

    // Game Loop
    while (game.running() && !game.getEndGame()) {
        // Update the game logic
        game.update();

        // Render the game objects
        game.render();
    }

    // End of Application
    return 0;
}
