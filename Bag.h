#pragma once
#include <vector>
#include "Die.h"

struct Bag {
    vectorDie dice;

    int MaxToTake();

    bool TakeFromBag(int n, vectorDie& retDice);

    bool AddToBag(vectorDie& newDice);
};