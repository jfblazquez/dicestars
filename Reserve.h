#pragma once
#include <vector>
#include <algorithm>
#include "Die.h"
#include "Actions.h"

struct Reserve {
    vectorDie dice;
    Actions GetActions();
    bool TakeFromReserve(vectorDie& toRemove);
};