#include "Game.h"

int main()
{
    Game game;

    game.DisplayWelcomeMenu();
    game.Initialize();
    game.RunCombatLoop();

    return 0;
}
