#pragma once
#include <string>
#include <stdexcept>

enum class Colours {
    NONE, BLACK, PURPLE, BLUE, ORANGE
};

std::string GetColour(Colours colour);

int GetColourIndex(Colours colour);

