#include "Lerp.h"

using namespace KamataEngine;

float Lerp(float a, float b, float t) { return t * a + (1.0f - t) * b; }
