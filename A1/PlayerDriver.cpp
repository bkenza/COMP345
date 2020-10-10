#include "Player.h"
using namespace std;

int main()
{
    cout << "\n***********************************************************\n" << endl;
    Player p1;
    cout << "PLAYER 1" << endl;
    p1.issueOrder("bomb");
    p1.issueOrder("ALLAHUAKBARRR");
    p1.issueOrder("deploy");
    p1.issueOrder("negotiate");
    p1.issueOrder("SPANKMEDADDY");
    //p1.toAttack();
    //p1.toDefend();

    /*cout << "\n***********************************************************\n" << endl;
    cout << "PLAYER 2" << endl;
    Player p2;*/

    return 0;
}