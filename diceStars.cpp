// diceStars.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <random>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include "diceStars.h"

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(1, 6);

enum class Colours {
    NONE, BLACK, PURPLE, BLUE, ORANGE
};

std::string GetColour(Colours colour) {
    std::string ret;
    switch (colour) {
    case Colours::BLACK:
        ret = "black ";
        break;
    case Colours::BLUE:
        ret = "blue ";
        break;

    case Colours::PURPLE:
        ret = "purple ";
        break;

    case Colours::ORANGE:
        ret = "orange ";
        break;
    }
    return ret;
}

int GetColourIndex(Colours colour) {
    int ret{};
    switch (colour) {
    case Colours::BLACK:
        ret = 0;
        break;
    case Colours::BLUE:
        ret = 2;
        break;

    case Colours::PURPLE:
        ret = 1;
        break;

    case Colours::ORANGE:
        ret = 3;
        break;
    default:
        throw std::invalid_argument("Not a valid color");
    }
    return ret;
}
static int idGenerator = 0;

struct Die {
    Colours colour;
    int number;
    int id{ idGenerator++ };
    bool IsStar() const {
        return number == 1;
    }
    bool IsNumber() const {
        return number >= 2 && number <= 6;
    }
    bool isValid() const {
        return IsNumber() || IsStar();
    }
    //TODO Check if 2 may be star in some colours
    void Draw() {
        number = dist(mt);
    }
    std::string Text() const {
        std::string ret{ "[" };
        ret += GetColour(colour);
        if (IsStar()) {
            ret += "star]";
        }
        else if (IsNumber()) {
            ret += std::to_string(number) + "]";
        }
        return ret;
    }
};

struct Bag {
    std::vector<Die> dice;
    int MaxToTake() {
        return std::min(3, (int)dice.size());
    }
    bool TakeFromBag(int n, std::vector<Die>& retDice) {
        if (n < 1 || n > 3) { return false; }
        if ((int)dice.size() < n) { return false; }
        //TODO: random bag sort
        for (int i = 0; i < n; ++i) {
            Die d = dice.back();
            d.Draw();
            retDice.push_back(d);
            dice.pop_back();
        }
        return true;
    }

    bool AddToBag(std::vector<Die>& newDice) {
        dice.insert(dice.end(), newDice.begin(), newDice.end());
        return true;
    }
};

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
        return actions[actions.size() -1];
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

struct Reserve {
    std::vector<Die> dice;
    Actions GetActions() {
        Actions actions;
        for (const auto& die : dice) {
            actions.Add(die);
        }
        return actions;
    };
    bool TakeFromReserve(std::vector<Die>& toRemove) {
        auto new_end = std::remove_if(dice.begin(), dice.end(),
            [&toRemove](const auto& it)
            { return std::any_of(toRemove.begin(), toRemove.end(), [&it](auto& r) {return r.id == it.id;});});

        dice.erase(new_end, dice.end());
        return true;
    }
};

struct ValuesRow {
    std::vector<std::reference_wrapper<int>> values;
    ValuesRow(std::vector<std::reference_wrapper<int>> _values) : values(_values) {}
    bool Add(int value) {
        bool ret = false;
        for (int& it : values) {
            if (it < 0) {
                it = value;
                ret = true;
                break;
            }
        }
        return ret;
    }
    int emptyValues() {
        int n = 0;
        std::for_each(values.begin(), values.end(), [&n](auto& it) {if (it == -1) { n++; }});
        return n;
    }

    bool Add(std::vector<Die>& dice) {
        bool ret = CanAdd(dice);
        if (!ret) { return false; }
        int diceSum = 0;
        std::for_each(dice.begin(), dice.end(), [&diceSum](auto& it) {
            if (it.IsNumber()) {
                diceSum += it.number;
            }
        });
        for (size_t zeros = 0; zeros < dice.size() - 1; zeros++) {
            Add(0);
        }
        Add(diceSum);
        return true;
    }

    bool CanAdd(std::vector<Die>& dice) {
        bool ret = emptyValues() >= (int)dice.size();
        ret = ret && dice.size() > 0;
        return ret;
    }
};

struct PlayerSheet {
    //black/purple/blue/orange
    std::array<std::array<int, 8>, 5> arr;
    std::array<int,5> missingStars{ 2,3,4,5,6 };
    std::array<int, 5> maxElements{ 8,7,6,5,4 };
    const int maxInColour = 5;

    PlayerSheet() {
        arr.fill({ {-1,-1,-1,-1,-1,-1,-1,-1} });
    }

    void Print() {
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
    bool CanDoAction(Action& action) {
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

    bool DoAction(Action& action) {
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
    ValuesRow GetColourRow(Colours colour) {
        std::vector<std::reference_wrapper<int>> ret;
        int pos = GetColourIndex(colour);
        for (int i = 0; i < maxInColour; i++) {
            ret.push_back(arr[i][pos]);
        }
        return ValuesRow(ret);
    }

    ValuesRow GetDieRow(int n) {
        int idx = n - 2;
        if (idx < 0) { throw std::invalid_argument("Not a valid die number"); }
        std::vector<std::reference_wrapper<int>> ret;
        for (int i = 0; i < maxElements[idx]; i++) {
            ret.push_back(arr[idx][i]);
        }
        return ValuesRow(ret);
    }
};



//2 black
// 3 purple
// 4 blue
//4 orange
/*
* 2: 4+4 +2
* 3: 4+3+3
* 4: 4+2+4
* 5:4+1+5
* 6:4+0+6
*/

//In die 1 equals to star
struct Game {
    Bag bag;
    Reserve reserve;
    std::vector<PlayerSheet> players;
    int playerShift{};

    void Init(int nplayers) {
        players = std::vector<PlayerSheet>(nplayers, PlayerSheet());
        Die black{ Colours::BLACK,0 };
        Die purple{ Colours::PURPLE,0 };
        Die blue{ Colours::BLUE,0 };
        Die orange{ Colours::ORANGE,0 };
        for (int i = 0; i < 2; ++i) {
            bag.dice.push_back(black);
        }
        for (int i = 0; i < 3; ++i) {
            bag.dice.push_back(purple);
        }
        for (int i = 0; i < 4; ++i) {
            bag.dice.push_back(blue);
        }
        for (int i = 0; i < 4; ++i) {
            bag.dice.push_back(orange);
        }
        reserve.dice.clear();
        playerShift = 0;
        PlayerSheet& currentPlayer2 = players[playerShift];
        //currentPlayer = 
    }
    bool TakeFromBag(int n) {
        std::vector<Die> newDice;
        bool ret = bag.TakeFromBag(n, newDice);
        if (ret) {
            reserve.dice.insert(reserve.dice.end(),newDice.begin(),newDice.end());
        }
        return ret;
    }
    bool PlayNumber(int n) {
        return false;
    }
    bool PlayColor(Colours color) {
        return false;
    }
    bool PlayStars(int n, bool restToBag) {
        return false;
    }
    void PrintReserve() {
        std::cout << "Reserve: ";
        for (const auto& it : reserve.dice) {
            std::cout << it.Text();
        }
        std::cout << '\n';
    }
    int nextPlayer() {
        playerShift = (playerShift + 1) % players.size();
        return playerShift;
    }
    PlayerSheet& currentPlayer() {
        return players[playerShift];
    }

    Actions ActionsForCurrentPlayer() {
        Actions actionsFromReserve = reserve.GetActions();
        Actions ret;
        for (auto& action : actionsFromReserve.actions) {
            if (currentPlayer().CanDoAction(action)) {
                ret.actions.push_back(action);
            }
        }
        return ret;
    };

};
int main()
{
    Game g;
    g.Init(2);
    //TODO: Change shift
    for (int i = 0; i < 2; ++i) {
        if (g.TakeFromBag(g.bag.MaxToTake())) {
            g.PrintReserve();
        }
        else {
            std::cout << "Cant take that much from bag. Max " << g.bag.MaxToTake() << "\n";
        }
    }
    g.currentPlayer().Print();
    for (int i = 0; i < 100; i++) {
        auto actions = g.ActionsForCurrentPlayer();
        actions.Print();
        if (actions.actions.empty()) return 0;
        Action& actionToDo = actions.actions.front();
        std::cout << "Doing action ";
        actionToDo.Print();
        bool ret = g.currentPlayer().DoAction(actionToDo);
        g.reserve.TakeFromReserve(actionToDo.dice);
        g.bag.AddToBag(actionToDo.dice);
        g.currentPlayer().Print();
        g.PrintReserve();
    }

}
