#include "Bag.h"

int Bag::MaxToTake() {
    return std::min(3, (int)dice.size());
}

bool Bag::TakeFromBag(int n, vectorDie& retDice) {
    if (n < 1 || n > 3) { return false; }
    if ((int)dice.size() < n) { return false; }
    //TODO: random bag sort
    for (int i = 0; i < n; ++i) {
        Die& d = dice.back();
        d.Draw();
        retDice.push_back(d);
        dice.pop_back();
    }
    return true;
}

bool Bag::AddToBag(vectorDie& newDice) {
    dice.insert(dice.end(), newDice.begin(), newDice.end());
    return true;
}
