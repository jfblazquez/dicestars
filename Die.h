#pragma once
#include <vector>
#include "Colours.h"
#include "RandomEngine.h"

static int idGenerator = 0;

struct Die {
    Colours colour;
    int number;
    int id{ idGenerator++ };

    bool IsStar() const;
    
    bool IsNumber() const;
    
    bool isValid() const;
    //TODO Check if 2 may be star in some colours
    
    void Draw();
    
    std::string Text() const;
};

