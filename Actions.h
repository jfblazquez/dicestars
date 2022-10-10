#pragma once
#include <vector>
#include <stdexcept>
#include "Die.h"
#include "Action.h"

struct Actions {
    std::vector<Action> actions;
    void Print();

    Action& GetOrCreateColourAction(const Die& die);

    Action& GetOrCreateNumberAction(const Die& die);

    Action& GetOrCreateStarAction(const Die& die);

    void Add(const Die& die);
};