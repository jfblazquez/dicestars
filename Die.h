#pragma once
#include <vector>
#include "Colours.h"
#include "RandomEngine.h"

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
        number = RandomEngine::Instance().GetDieNumber();
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

