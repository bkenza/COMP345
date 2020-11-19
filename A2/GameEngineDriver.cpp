#include "GameEngine.h"

int gedmain()
{
    GameEngine *game = new GameEngine();
    game->startGame();
    cout << ((game->getPlayers()[0])->getTerritoryList())->size() << endl;

    /*cout << "THESE ARE YOUR PLAYERS" << endl;
    for(int i = 0; i < game->getPlayers().size(); i++)
    {
        std::cout << "Player: " << game->getPlayers()[i]->getPlayerID() << endl;
        std::cout << "Player: " << game->getPlayers()[i]->getReinforcementPool() << endl;
        std::cout << "Player: " << game->getPlayers()[i]->getHand() << endl;
        //std::cout << "Player: " << game->getPlayers()[i]-> << endl;
    }*/
    std::cout << "\n" << endl;
    game->mainGameLoop();

    cout << ((game->getPlayers()[0])->getTerritoryList())->size() << endl;

    return 0;
}