#include "GameEngine.h"

int main()
{
    GameEngine *game = new GameEngine();
    game->startGame();
    //cout << ((game->getPlayers()[0])->getTerritoryList())->size() << endl;

    std::cout << "\n" << endl;

    game->mainGameLoop();

    //cout << ((game->getPlayers()[0])->getTerritoryList())->size() << endl;

    return 0;
}