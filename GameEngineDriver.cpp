#include "GameEngine.h"

int gmain()
{
    GameEngine *game = new GameEngine();
    game->startGame();
    return 0;
}