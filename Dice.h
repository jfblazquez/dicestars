#pragma once
#include "Die.h"

class Dice
{
public:

	Dice();

	void Init();

	~Dice();

	vectorDie GetDice();
private:

	vectorDie mDice;

};

