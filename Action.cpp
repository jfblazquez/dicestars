#include "Action.h"

void Action::Print() const {
    std::stringstream ss;
    if (actionType == ActionType::COLOUR) {
        ss << "Action type colour. " << GetColour(paramColour) << "\n";
        ss << "Dice: ";
        for (const Die& die : dice) {
            ss << die.Text();
        }
        ss << '\n';
        std::cout << ss.str();
    }
    else if (actionType == ActionType::NUMBER) {
        ss << "Action type number. " << paramNumber << "\n";
        ss << "Dice: ";
        for (const Die& die : dice) {            
            ss << die.Text();
        }
        ss << '\n';
        std::cout << ss.str();
    }
    else if (actionType == ActionType::STARS) {
        ss << "Action type stars. \n";
        ss << "Dice: ";
        for (const Die& die : dice) {
            ss << die.Text();
        }
        ss << '\n';
        std::cout << ss.str();
    }
    std::cout << "\n";
}
