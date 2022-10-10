#include "Colours.h"

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
