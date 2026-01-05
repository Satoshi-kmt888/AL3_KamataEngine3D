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

private:

	/// <summary>
	/// 旋回
	/// </summary>
	void Turn();

	/// <summary>
	/// 移動
	/// </summary>
	void Move();

private:
	//==================================================
	//                 拡縮・回転・移動
	//==================================================

	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	/*
	定数
	--------------------*/

	// 旋回時間<秒>
	static inline const float kTimeTurn = 0.8f;

	// 加速度
	static inline const float kAcceleration = 0.01f;

	// 速度減衰率
	static inline const float kAttenuation = 0.05f;

	// 速度の助言
	static inline const float kLimitRunSpeed = 5.0f;

	// 重力加速度
	static inline const float kGravityAcceleration = 0.1f;

	// 最大落下速度
	static inline const float kLimitFallSpeed = 3.0f;

	// ジャンプ初速
	static inline const float kJumpAcceleration = 1.0f;

	/*
	拡縮
	--------------------*/

	/*
	回転
	--------------------*/

	// 旋回開始時の角度
	float turnFirstRotationY_ = 0.0f;

	// 旋回タイマー
	float turnTimer_ = 0.0f;

	/*
	移動
	--------------------*/

	// 速度
	KamataEngine::Vector3 velocity_ = {};

	//==================================================
	//                      状態
	//==================================================

	// 左右の向き
	LRDirection lrDirection_ = LRDirection::kRight;

	// 接地状態フラグ
	bool onGround_ = true;

	//==================================================
	//                      描画
	//==================================================

	// テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// モデル
	KamataEngine::Model* model_ = nullptr;

	// カメラ
	KamataEngine::Camera* camera_ = nullptr;
};
