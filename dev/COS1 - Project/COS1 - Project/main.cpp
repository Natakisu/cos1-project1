#include "Game.h"

int main() {
    Game game;

    // Run the game session loop continuously 
    while (true) {
        game.Initialize();      // Displays welcome menu, sets up game
        game.RunCombatLoop();   // Plays combat until win/loss

    }

    return 0;
}
