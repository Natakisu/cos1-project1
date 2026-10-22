#include "Game.h"

int main()
{
    Game game;

    game.DisplayWelcomeMenu(); // <-- This shows the welcome / instructions screen first!
    game.Initialize();         // <-- Then goes into New Game / Load Game
    game.RunCombatLoop();

    return 0;
}
