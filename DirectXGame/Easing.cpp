#include "Easing.h"
#include "Lerp.h"
#include <math.h>

float Easing(float t, EaseType easeType) {

	switch (easeType) {

	case EaseType::EASE_IN:

		// イージングタイムを計算
		return t * t;

	case EaseType::EASE_OUT:

		// イージングタイムを計算
		return 1.0f - (1.0f - t) * (1.0f - t);

	case EaseType::EASE_IN_OUT:

		if (t < 0.5f) {

			// イージングタイムを計算
			return 2.0f * t * t;

		} else {

			// イージングタイムを計算
			return 1.0f - powf(-2.0f * t + 2.0f, 2.0f) / 2.0f;
		}

	case EaseType::EASE_IN_BACK: {

		// 定数を宣言
		const float c1 = 1.70158f;
		const float c3 = c1 + 1.0f;

		// イージングタイムを計算
		return c3 * powf(t, 3.0f) - c1 * powf(t, 2.0f);
	}

	case EaseType::EASE_OUT_BACK: {

		// 定数を宣言
		const float c1 = 1.70158f;
		const float c3 = c1 + 1.0f;

		// イージングタイムを計算
		return 1.0f + c3 * powf(t - 1.0f, 3.0f) + c1 * powf(t - 1.0f, 2.0f);
	}
	}

	return t;
}
