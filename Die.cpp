#include "Die.h"

bool Die::IsStar() const {
    if (colour == Colours::ORANGE) {
        return number <= 2;
    }
    return number == 1;        
}

bool Die::IsNumber() const {
    if (colour == Colours::ORANGE) {
        return number >= 2 && number <= 6;
    }
    return number >= 2 && number <= 6;
}

bool Die::isValid() const {
    return IsNumber() || IsStar();
}

 void Die::Draw() {
    number = RandomEngine::Instance().GetDieNumber();
}

std::string Die::Text() const {
    std::string ret{ "[" };
    ret += GetColour(colour);
    if (IsStar()) {
        ret += "star]";
    }
    else if (IsNumber()) {
        ret += std::to_string(number) + "]";
    }
    else {
        //not a valid state. Number not known yet
        ret += "]";
    }
    return ret;
}
