#include "Discard.h"

bool Discard::TakeFromDiscard(std::vector<Die>& toRemove) {
    auto new_end = std::remove_if(dice.begin(), dice.end(),
        [&toRemove](const auto& it)
        { return std::any_of(toRemove.begin(), toRemove.end(), [&it](auto& r) {return r.id == it.id; }); });

    dice.erase(new_end, dice.end());
    return true;
}

bool Discard::Add(std::vector<Die>& newDice) {
    dice.insert(dice.end(), newDice.begin(), newDice.end());
    return true;
}
