#include "Game.h"

// --- APPLICATION ENTRY POINT ---
int main()
{
    Game game;

    // --- GAMEPLAY LIFECYCLE ---
    game.DisplayWelcomeMenu();
    game.Initialize();
    game.RunCombatLoop();

    return 0;
}
//Organized and Refactored