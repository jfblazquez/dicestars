#pragma once

#include <vector>
#include <algorithm>
#include "Die.h"

struct Discard
{
    std::vector<Die> dice;    
    
    bool TakeFromDiscard(std::vector<Die>& toRemove);

    bool Add(std::vector<Die>& newDice);
};

