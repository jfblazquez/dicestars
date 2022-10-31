#pragma once

#include <vector>
#include <algorithm>
#include "Die.h"

struct Discard
{
    vectorDie dice;    
    
    bool TakeFromDiscard(vectorDie& toRemove);

    bool Add(vectorDie& newDice);
};

