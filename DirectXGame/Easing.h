#pragma once

/// <summary>
/// イージングの種類
/// </summary>
enum class EaseType {
	EASE_IN,
	EASE_OUT,
	EASE_IN_OUT,
	EASE_IN_BACK,
	EASE_OUT_BACK,
};

/// <summary>
/// イージング補間値
/// </summary>
/// <param name="t">0~1で変化するΔt</param>
/// <param name="easeType">イージングの種類</param>
/// <returns></returns>
float Easing(float t, EaseType easeType);