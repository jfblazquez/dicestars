#pragma once
#include <vector>
#include "Die.h"

struct Bag {
    std::vector<Die> dice;

    int MaxToTake();

    bool TakeFromBag(int n, std::vector<Die>& retDice);

    bool AddToBag(std::vector<Die>& newDice);
};