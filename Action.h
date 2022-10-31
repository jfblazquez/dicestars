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
    bool onEndReserveToBag{};
    vectorDie dice;
    void Print() const;
};