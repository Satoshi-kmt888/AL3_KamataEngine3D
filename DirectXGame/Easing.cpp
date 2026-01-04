#include "Easing.h"
#include "Lerp.h"
#include <math.h>

/// <summary>
/// イージング
/// </summary>
/// <param name="t">0.0f~1.0fで変化するΔt</param>
/// <param name="easingType">イージングの種類</param>
/// <returns>イージングされたΔtの値</returns>
float Easing(float t, EasingType easingType) {

	switch (easingType) {

	case EasingType::kEASE_IN:

		/*
		イーズイン
		--------------------*/

		// イージングタイムを計算
		return t * t;

	case EasingType::kEASE_OUT:

		/*
		イーズアウト
		--------------------*/

		// イージングタイムを計算
		return 1.0f - (1.0f - t) * (1.0f - t);

	case EasingType::kEASE_IN_OUT:

		/*
		イーズインアウト
		--------------------*/

		if (t < 0.5f) {

			// イージングタイムを計算
			return 2.0f * t * t;

		} else {

			// イージングタイムを計算
			return 1.0f - powf(-2.0f * t + 2.0f, 2.0f) / 2.0f;
		}

	case EasingType::kEASE_IN_BACK: {

		/*
		イーズインバック
		--------------------*/

		// 定数を宣言
		const float c1 = 1.70158f;
		const float c3 = c1 + 1.0f;

		// イージングタイムを計算
		return c3 * powf(t, 3.0f) - c1 * powf(t, 2.0f);
	}

	case EasingType::kEASE_OUT_BACK: {

		/*
		イーズアウトバック
		--------------------*/

		// 定数を宣言
		const float c1 = 1.70158f;
		const float c3 = c1 + 1.0f;

		// イージングタイムを計算
		return 1.0f + c3 * powf(t - 1.0f, 3.0f) + c1 * powf(t - 1.0f, 2.0f);
	}
	}

	return t;
}
