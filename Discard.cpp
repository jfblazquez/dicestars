#include "Discard.h"

bool Discard::TakeFromDiscard(vectorDie& toRemove) {
    auto new_end = std::remove_if(dice.begin(), dice.end(),
        [&toRemove](const Die& it)
        { return std::any_of(toRemove.begin(), toRemove.end(), [&it](Die& r) {return r.id == it.id; }); });

    dice.erase(new_end, dice.end());
    return true;
}

bool Discard::Add(vectorDie& newDice) {
    dice.insert(dice.end(), newDice.begin(), newDice.end());
    return true;
}
