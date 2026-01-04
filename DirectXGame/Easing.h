#pragma once

/// <summary>
/// イージングの種類
/// </summary>
enum class EasingType {
	kEASE_IN,
	kEASE_OUT,
	kEASE_IN_OUT,
	kEASE_IN_BACK,
	kEASE_OUT_BACK,
};

// イージング関数
float Easing(float t, enum EasingType);