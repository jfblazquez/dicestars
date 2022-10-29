#pragma once
#include <vector>
#include "Colours.h"
#include "RandomEngine.h"

static int idGenerator = 0;

enum class DieLocation {
    BAG, RESERVE, DISCARD
};

class Die {
    friend class Dice;
public:

    Colours colour;
    int number{0};
    int id{ idGenerator++ };
    DieLocation dieLocation{ DieLocation::BAG };

    bool IsStar() const;
    
    bool IsNumber() const;
    
    bool isValid() const;
    
    void Draw();
    
    std::string Text() const;

    ~Die() = default;

private:
    Die(Colours _colour) {
        colour = _colour;
        number = 0;
    }

    Die(const Die&) = default;
    Die(Die&&) = default;
    Die& operator=(const Die&) = default;
    Die& operator=(Die&&) = default;


};

using refDie = std::reference_wrapper<Die>;
using vectorDie = std::vector<refDie>;
