#pragma once
#include <string>
#include <stdexcept>

enum class Colours {
    NONE, BLACK, PURPLE, BLUE, ORANGE
};

const int colourNum = 4;

std::string GetColour(Colours colour);

int GetColourIndex(Colours colour);

