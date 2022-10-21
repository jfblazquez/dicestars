#pragma once
#include <vector>
#include <algorithm>
#include "Die.h"
#include "Actions.h"

struct Reserve {
    std::vector<Die> dice;
    Actions GetActions();
    bool TakeFromReserve(std::vector<Die>& toRemove);
};