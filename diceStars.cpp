#include <iostream>
#include <vector>
#include <random>
#include "Game.h"
#include "diceStars.h"

int main()
{
    Game g;
    g.Init(1);
    g.currentPlayer().Print();
    for (int i = 1; i <= 10; i++) {
        std::cout << "Turn " << i << "\n";
        std::cout << "Take from bag max\n";
        g.TakeFromBag(g.bag.MaxToTake());
        g.PrintReserve();
        auto actions = g.ActionsForCurrentPlayer();
        actions.Print();
        if (actions.actions.empty()) return 0;
        Action& actionToDo = actions.actions.front();
        std::cout << "Doing action ";
        actionToDo.Print();
        bool ret = g.DoAction(actionToDo);
        std::cout << "After action: ("<< std::boolalpha << ret << ")\n";
        g.currentPlayer().Print();
        g.PrintBag();
        g.PrintReserve();
        g.PrintDiscard();    
    }
    //TODO: Change shift
    /*for (int i = 0; i < 4; ++i) {
        if (g.TakeFromBag(g.bag.MaxToTake())) {
            g.PrintReserve();
        }
        else {
            std::cout << "Cant take that much from bag. Max " << g.bag.MaxToTake() << "\n";
        }
    }*/

}
