#include "RandomEngine.h"

int RandomEngine::GetDieNumber() {
	return dist(mt);
}
