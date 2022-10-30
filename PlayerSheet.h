#pragma once
#include <array>
#include <iostream>
#include <iomanip>
#include "Action.h"
#include "ValuesRow.h"

class PlayerSheet {
public:

    //black/purple/blue/orange
    std::array<std::array<int, 8>, 5> arr;
    const std::array<int, 5> initialMissingStars{ 2,3,4,5,6 };
    std::array<int, 5> missingStars{ initialMissingStars };
    std::array<int, 5> maxElements{ 8,7,6,5,4 };
    const int maxInColour = 5;
    const int minDie = 2;
    const int maxDie = 6;

    PlayerSheet();

    ~PlayerSheet() = default;

    void Print();

    bool CanDoAction(Action& action);

    bool DoAction(Action& action);

    ValuesRow& GetColourRow(Colours colour);

    ValuesRow& GetDieRow(int n);

    int GetPoints();

    bool AnyStarFill(int die);

    bool AllStarCompleted(int die);

    int StarMultiplier(int die);

    void DebugAddress();

    PlayerSheet(const PlayerSheet&) = delete;

private:

    void CreateValuesRow();

    void CreateColourRows();

    void CreateDieRows();

    vectorPValuesRow colourRows;

    vectorPValuesRow dieRows;

};

using ptrPlayerSheet = std::shared_ptr<PlayerSheet>;
using vectorPPlayerSheet = std::vector<ptrPlayerSheet>;