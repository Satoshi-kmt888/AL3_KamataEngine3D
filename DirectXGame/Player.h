#pragma once

#include "KamataEngine.h"

/// <summary>
/// 左右
/// </summary>
enum class LRDirection {
	kRight,
	kLeft,
};

/// <summary>
/// プレイヤー
/// </summary>
class Player {

private:
	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// 速度
	KamataEngine::Vector3 velocity_ = {};

	// 加速度
	static inline const float kAcceleration = 0.01f;

	// 速度減衰率
	static inline const float kAttenuation = 0.05f;

	// 速度の助言
	static inline const float kLimitRunSpeed = 5.0f;

	// 左右の向き
	LRDirection lrDirection_ = LRDirection::kRight;

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;

	// 旋回タイマー
	float turnTimer_ = 0.0f;

	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.3f;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;

public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="model">モデル</param>
	/// <param name="textureHandle">テクスチャハンドル</param>
	/// <param name="camera">カメラ</param>
	void Initialize(KamataEngine::Model* model, uint32_t textureHandle, KamataEngine::Camera* camera, const KamataEngine::Vector3& position);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
};
