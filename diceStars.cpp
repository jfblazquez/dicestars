// diceStars.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <random>
#include "Game.h"
#include "diceStars.h"

//2 black
// 3 purple
// 4 blue
//4 orange
/*
* 2: 4+4 +2
* 3: 4+3+3
* 4: 4+2+4
// * 5:4+1+5
* 6:4+0+6
*/

//In die 1 equals to star


int main()
{
    Game g;
    g.Init(2);
    //TODO: Change shift
    /*for (int i = 0; i < 4; ++i) {
        if (g.TakeFromBag(g.bag.MaxToTake())) {
            g.PrintReserve();
        }
        else {
            std::cout << "Cant take that much from bag. Max " << g.bag.MaxToTake() << "\n";
        }
    }*/
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
        std::cout << "After action:\n";
        g.currentPlayer().Print();
        g.PrintBag();
        g.PrintReserve();
        g.PrintDiscard();        
    }

}
