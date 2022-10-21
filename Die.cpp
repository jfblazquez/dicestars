#include "Die.h"

bool Die::IsStar() const {
    return number == 1;
}

bool Die::IsNumber() const {
    return number >= 2 && number <= 6;
}

bool Die::isValid() const {
    return IsNumber() || IsStar();
}

//TODO Check if 2 may be star in some colours

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
        ret += "]";
    }
    return ret;
}
