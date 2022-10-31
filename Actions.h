#pragma once
#include <vector>
#include <stdexcept>
#include "Die.h"
#include "Action.h"

struct Actions {
    std::vector<Action> actions;
    void Print();

    Action& GetOrCreateColourAction(Die& die);

    Action& GetOrCreateNumberAction(Die& die);

    Action& GetOrCreateStarAction(Die& die);

    void Add(Die& die);
};