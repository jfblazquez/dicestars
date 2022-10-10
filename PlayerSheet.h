#pragma once
#include <array>
#include <iostream>
#include <iomanip>
#include "Action.h"
#include "ValuesRow.h"

struct PlayerSheet {
    //black/purple/blue/orange
    std::array<std::array<int, 8>, 5> arr;
    std::array<int, 5> missingStars{ 2,3,4,5,6 };
    std::array<int, 5> maxElements{ 8,7,6,5,4 };
    const int maxInColour = 5;

    PlayerSheet();

    void Print();

    bool CanDoAction(Action& action);

    bool DoAction(Action& action);

    //TODO: Cache colourRow and dieRow
    ValuesRow GetColourRow(Colours colour);

    ValuesRow GetDieRow(int n);
};