#include "Lerp.h"

using namespace KamataEngine;

/// <summary>
/// 線形補間
/// </summary>
/// <param name="a">開始値</param>
/// <param name="b">終了値</param>
/// <param name="t">時間</param>
/// <returns></returns>
float Lerp(float a, float b, float t) {

	return t * a + (1.0f - t) * b;
}
