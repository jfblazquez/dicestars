#pragma once
#include <vector>
#include <functional>
#include <algorithm>
#include "Die.h"

struct ValuesRow {
    std::vector<std::reference_wrapper<int>> values;
    
    ValuesRow(std::vector<std::reference_wrapper<int>> _values) : values(_values) {}
    
    bool Add(int value);

    int emptyValues();

    bool Add(std::vector<Die>& dice);

    bool CanAdd(std::vector<Die>& dice);
};