#pragma once
#include <vector>
#include "Die.h"

struct Bag {
    std::vector<Die> dice;
    int MaxToTake() {
        return std::min(3, (int)dice.size());
    }
    bool TakeFromBag(int n, std::vector<Die>& retDice) {
        if (n < 1 || n > 3) { return false; }
        if ((int)dice.size() < n) { return false; }
        //TODO: random bag sort
        for (int i = 0; i < n; ++i) {
            Die d = dice.back();
            d.Draw();
            retDice.push_back(d);
            dice.pop_back();
        }
        return true;
    }

    bool AddToBag(std::vector<Die>& newDice) {
        dice.insert(dice.end(), newDice.begin(), newDice.end());
        return true;
    }
};