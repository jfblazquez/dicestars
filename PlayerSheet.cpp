#include "PlayerSheet.h"

PlayerSheet::PlayerSheet() {
    arr.fill({ { -1,-1,-1,-1,-1,-1,-1,-1 } });
}

void PlayerSheet::Print() {
    int dieNumber = 2;
    std::cout << "  blk  pur  blu  ora\n";
    for (auto dieIndex = 0; dieIndex < maxInColour; dieIndex++) {
        std::cout << dieNumber++ << " ";
        for (auto elem = 0; elem < maxElements[dieIndex]; elem++) {
            int v = arr[dieIndex][elem];
            std::string vs;
            if (v == -1) {
                std::cout << "[  ] ";
            }
            else if (v == 0) {
                std::cout << "[ X] ";
            }
            else {
                std::cout << "[" << std::setw(2) << v << "] ";
            }

        }
        std::cout << '\n';
    }
}

bool PlayerSheet::CanDoAction(Action& action) {
    bool ret = false;
    if (action.actionType == ActionType::COLOUR) {
        ValuesRow row = GetColourRow(action.paramColour);
        ret = row.CanAdd(action.dice);
    }
    else if (action.actionType == ActionType::NUMBER) {
        ValuesRow row = GetDieRow(action.paramNumber);
        ret = row.CanAdd(action.dice);
    }
    else if (action.actionType == ActionType::STARS) {
        //TODO
        return false;
    }
    return ret;
}

bool PlayerSheet::DoAction(Action& action) {
    bool ret = false;
    if (action.actionType == ActionType::COLOUR) {
        ValuesRow row = GetColourRow(action.paramColour);
        ret = row.Add(action.dice);
    }
    else if (action.actionType == ActionType::NUMBER) {
        ValuesRow row = GetDieRow(action.paramNumber);
        ret = row.Add(action.dice);
    }
    else if (action.actionType == ActionType::STARS) {
        //TODO
        return false;
    }
    return ret;
}

//TODO: Cache colourRow and dieRow

ValuesRow PlayerSheet::GetColourRow(Colours colour) {
    std::vector<std::reference_wrapper<int>> ret;
    int pos = GetColourIndex(colour);
    for (int i = 0; i < maxInColour; i++) {
        ret.push_back(arr[i][pos]);
    }
    return ValuesRow(ret);
}

ValuesRow PlayerSheet::GetDieRow(int n) {
    int idx = n - 2;
    if (idx < 0) { throw std::invalid_argument("Not a valid die number"); }
    std::vector<std::reference_wrapper<int>> ret;
    for (int i = 0; i < maxElements[idx]; i++) {
        ret.push_back(arr[idx][i]);
    }
    return ValuesRow(ret);
}
