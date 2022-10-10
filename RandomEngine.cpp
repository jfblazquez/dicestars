#include "RandomEngine.h"

int RandomEngine::GetDieNumber() {
	return dist(mt);
}

RandomEngine::RandomEngine() {
	mt = { rd() };
}
