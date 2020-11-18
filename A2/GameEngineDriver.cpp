#include "GameEngine.h"

int main()
{
    GameEngine *game = new GameEngine();
    game->startGame();

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

    return 0;
}