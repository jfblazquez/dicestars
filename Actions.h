#pragma once
#include <vector>
#include <stdexcept>
#include "Die.h"
#include "Action.h"

struct Actions {
    std::vector<Action> actions;
    void Print() {
        for (const auto& action : actions) {
            action.Print();
        }
    }

    Action& GetOrCreateColourAction(const Die& die) {
        for (auto& action : actions) {
            if (action.actionType == ActionType::COLOUR &&
                action.paramColour == die.colour) {
                action.dice.push_back(die);
                return action;
            }
        }

        Action newAction;
        newAction.actionType = ActionType::COLOUR;
        newAction.paramColour = die.colour;
        newAction.dice.push_back(die);
        actions.push_back(newAction);
        return actions[actions.size() - 1];
    }

    Action& GetOrCreateNumberAction(const Die& die) {
        if (!die.IsNumber()) { throw std::invalid_argument("Die is not number"); }
        for (auto& action : actions) {
            if (action.actionType == ActionType::NUMBER &&
                action.paramNumber == die.number) {
                action.dice.push_back(die);
                return action;
            }
        }

        Action newAction;
        newAction.actionType = ActionType::NUMBER;
        newAction.paramNumber = die.number;
        newAction.dice.push_back(die);
        actions.push_back(newAction);
        return actions[actions.size() - 1];
    }

    Action& GetOrCreateStarAction(const Die& die) {
        if (!die.IsStar()) { throw std::invalid_argument("Die is not star"); }
        for (auto& action : actions) {
            if (action.actionType == ActionType::STARS) {
                action.dice.push_back(die);
                return action;
            }
        }

        Action newAction;
        newAction.actionType = ActionType::STARS;
        newAction.dice.push_back(die);
        actions.push_back(newAction);
        return actions[actions.size() - 1];
    }

    void Add(const Die& die) {
        GetOrCreateColourAction(die);
        if (die.IsNumber()) {
            GetOrCreateNumberAction(die);
        }
        if (die.IsStar()) {
            GetOrCreateStarAction(die);
        }
    }
};