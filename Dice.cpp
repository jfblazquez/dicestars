#include "Dice.h"

Dice::Dice() {
	for (int i = 0; i < 2; i++) {
		Die* p = new Die(Colours::PURPLE);
		mDice.push_back(*p);
	}
	for (int i = 0; i < 3; i++) {
		Die* p = new Die(Colours::PURPLE);
		mDice.push_back(*p);
	}
	for (int i = 0; i < 4; i++) {
		Die* p = new Die(Colours::BLUE);
		mDice.push_back(*p);
	}
	for (int i = 0; i < 5; i++) {
		Die* p = new Die(Colours::ORANGE);
		mDice.push_back(*p);
	}
}

void Dice::Init() {
	for (Die& die : mDice) {
		die.dieLocation = DieLocation::BAG;
	}
}

Dice::~Dice() {
	for (Die& die : mDice) {
		delete &die;
	}
	mDice.clear();
}

vectorDie Dice::GetDice()
{
	return mDice;
}
