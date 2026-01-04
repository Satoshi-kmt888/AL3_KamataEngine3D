#include "Lerp.h"

using namespace KamataEngine;

float Lerp(float a, float b, float t) {

	float result{};

	result = t * a + (1.0f - t) * b;

	return;
}
