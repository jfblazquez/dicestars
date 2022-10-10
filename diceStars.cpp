// diceStars.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <random>
#include "Game.h"
#include "diceStars.h"

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(1, 6);

//2 black
// 3 purple
// 4 blue
//4 orange
/*
* 2: 4+4 +2
* 3: 4+3+3
* 4: 4+2+4
* 5:4+1+5
* 6:4+0+6
*/

//In die 1 equals to star


int main()
{
    Game g;
    g.Init(2);
    //TODO: Change shift
    for (int i = 0; i < 2; ++i) {
        if (g.TakeFromBag(g.bag.MaxToTake())) {
            g.PrintReserve();
        }
        else {
            std::cout << "Cant take that much from bag. Max " << g.bag.MaxToTake() << "\n";
        }
    }
    g.currentPlayer().Print();
    for (int i = 0; i < 100; i++) {
        auto actions = g.ActionsForCurrentPlayer();
        actions.Print();
        if (actions.actions.empty()) return 0;
        Action& actionToDo = actions.actions.front();
        std::cout << "Doing action ";
        actionToDo.Print();
        bool ret = g.currentPlayer().DoAction(actionToDo);
        g.reserve.TakeFromReserve(actionToDo.dice);
        g.bag.AddToBag(actionToDo.dice);
        g.currentPlayer().Print();
        g.PrintReserve();
    }

}
