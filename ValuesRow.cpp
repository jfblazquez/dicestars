#include "ValuesRow.h"

bool ValuesRow::Add(int value) {
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

int ValuesRow::emptyValues() {
    int n = 0;
    std::for_each(values.begin(), values.end(), [&n](auto& it) {if (it == -1) { n++; }});
    return n;
}

bool ValuesRow::Add(std::vector<Die>& dice) {
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

bool ValuesRow::CanAdd(std::vector<Die>& dice) {
    bool ret = emptyValues() >= (int)dice.size();
    ret = ret && dice.size() > 0;
    return ret;
}

int ValuesRow::Sum()
{
    int n = 0;
    std::for_each(values.begin(), values.end(), [&n](auto& it) {if (it > 0) { n+= it; }});
    return n;
}
