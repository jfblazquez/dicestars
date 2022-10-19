#include "PlayerSheet.h"

PlayerSheet::PlayerSheet() {
    arr.fill({ { -1,-1,-1,-1,-1,-1,-1,-1 } });
}

void PlayerSheet::Print() {
    int dieNumber = minDie;
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
    std::cout << "Points: " << GetPoints() << "\n";
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

ValuesRow PlayerSheet::GetDieRow(int die) {
    size_t idx = die - minDie;
    if (idx >= maxElements.size() ) { throw std::invalid_argument("Not a valid die number"); }
    std::vector<std::reference_wrapper<int>> ret;
    for (int i = 0; i < maxElements[idx]; i++) {
        ret.push_back(arr[idx][i]);
    }
    return ValuesRow(ret);
}


int PlayerSheet::GetPoints()
{
    //TODO ValuesRow with ValuesWithStarsRows
    int points = 0;
    for (auto die = minDie; die < maxDie; die++) {
        ValuesRow row = GetDieRow(die);
        points += row.Sum() * StarMultiplier(die);
    }
    return points;
}


bool PlayerSheet::AnyStarFill(int die)
{
    size_t idx = die - minDie;
    if (idx >= maxElements.size()) { throw std::invalid_argument("Not a valid die number"); }
    return missingStars[idx] != initialMissingStars[idx];
}

bool PlayerSheet::AllStarCompleted(int die)
{
    size_t idx = die - minDie;
    if (idx >= maxElements.size()) { throw std::invalid_argument("Not a valid die number"); }
    return missingStars[idx] == 0;
}

int PlayerSheet::StarMultiplier(int die)
{
    if (AllStarCompleted(die)) {
        return 2;
    }
    else if (AnyStarFill(die)) {
        return 0;
    }
    return 1;

}
