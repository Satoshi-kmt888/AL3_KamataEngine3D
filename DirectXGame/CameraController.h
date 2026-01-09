#pragma once

#include "KamataEngine.h"

/// <summary>
/// 矩形の頂点
/// </summary>
struct Rect {
	float left = 0.0f;
	float right = 1.0f;
	float bottom = 0.0f;
	float top = 1.0f;
};

// 前方宣言
class Player;
/// <summary>
/// カメラコントローラ
/// </summary>
class CameraController {

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Initialize(KamataEngine::Camera* camera);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// リセット
	/// </summary>
	void Reset();

public:

	//追従対象
	void SetTarget(Player* target) { target_ = target; }

	//カメラの範囲
	void SetMovableArea(Rect area) { movableArea_ = area; }

private:
	// 座標補間割合
	static inline const float kInterpolationRate = 0.3f;

	// 速度掛け率
	static inline const float kVelocityBias = 5.0f;

	// 追従対象の各方向へのカメラ移動範囲
	static inline const Rect margin_ = {-2.0f, 2.0f, -2.0f, 2.0f};

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

	// 追従対象
	Player* target_ = nullptr;

	// 追従対象とカメラの座標の差
	KamataEngine::Vector3 targetOffset_ = {0.0f, 0.0f, -25.0f};

	// カメラ移動範囲
	Rect movableArea_ = {0.0f, 100.0f, 0.0f, 100.0f};

	// カメラの目標座標
	KamataEngine::Vector3 targetCoord_;

	// 追従対象の速度
	KamataEngine::Vector3 targetVelocity_;

	// 追従対象の座標
	KamataEngine::Vector3 targetTranslation_;
};
