#pragma once
#include <random>

class RandomEngine
{
public:
	static RandomEngine& Instance() {
		static RandomEngine _instance;
		return _instance;
	}

	int GetDieNumber();
private:
	RandomEngine() = default;
	std::random_device rd;
	std::mt19937 mt{ rd() };
	std::uniform_int_distribution<int> dist{ 1, 6 };
};

