#pragma once
#include <vector>
#include <functional>
#include <algorithm>
#include <numeric>
#include <memory>
#include <iostream>
#include "Die.h"

using refInt = std::reference_wrapper<int>;
using vectorRInt = std::vector<refInt>;

struct ValuesRow {
    vectorRInt values;
    
    ValuesRow(vectorRInt _values) : values(_values) {}
    
    bool Add(int value);

    int emptyValues();

    bool Add(vectorDie& dice);

    bool CanAdd(vectorDie& dice);

    int Sum();

    ValuesRow(const ValuesRow&) = delete;
};

using ptrValuesRow = std::shared_ptr<ValuesRow>;
using vectorPValuesRow = std::vector<ptrValuesRow>;