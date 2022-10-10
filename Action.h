#pragma once
#include <vector>
#include <iostream>
#include <sstream>
#include "Die.h"
#include "Colours.h"

enum class ActionType { NONE, COLOUR, NUMBER, STARS };

struct Action {
    ActionType actionType{ ActionType::NONE };
    Colours paramColour{ Colours::NONE };
    int paramNumber{ 0 };
    int paramStars{ 0 }; //TODO: Decide how to star haha
    std::vector<Die> dice;
    void Print() const {
        std::stringstream ss;
        if (actionType == ActionType::COLOUR) {
            ss << "Action type colour. " << GetColour(paramColour) << "\n";
            ss << "Dice: ";
            for (const auto& die : dice) {
                ss << die.Text();
            }
            ss << '\n';
            std::cout << ss.str();
        }
        else if (actionType == ActionType::NUMBER) {
            ss << "Action type number. " << paramNumber << "\n";
            ss << "Dice: ";
            for (const auto& die : dice) {
                ss << die.Text();
            }
            ss << '\n';
            std::cout << ss.str();
        }
        else if (actionType == ActionType::STARS) {
            ss << "Action type stars. \n";
            ss << "Dice: ";
            for (const auto& die : dice) {
                ss << die.Text();
            }
            ss << '\n';
            std::cout << ss.str();
        }
        std::cout << "\n";
    }
};