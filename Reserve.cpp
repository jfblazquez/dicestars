#include "Reserve.h"

Actions Reserve::GetActions() {
    Actions actions;
    for (const auto& die : dice) {
        actions.Add(die);
    }
    return actions;
}

bool Reserve::TakeFromReserve(std::vector<Die>& toRemove) {
    auto new_end = std::remove_if(dice.begin(), dice.end(),
        [&toRemove](const auto& it)
        { return std::any_of(toRemove.begin(), toRemove.end(), [&it](auto& r) {return r.id == it.id;});});

    dice.erase(new_end, dice.end());
    return true;
}
