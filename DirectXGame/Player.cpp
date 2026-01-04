#include <algorithm>
#include <cassert>
#include <numbers>

#include "Lerp.h"
#include "Player.h"
#include "WorldTransformUpdate.h"

using namespace KamataEngine;

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize(Model* model, uint32_t textureHandle, Camera* camera, const KamataEngine::Vector3& position) {

	// NULLポインタチェック
	assert(model);

	// 引数のデータをメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;

	// ワールド変換の初期化
	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 1.0f;
	worldTransform_.translation_ = position;
	worldTransform_.Initialize();
}

/// <summary>
/// 更新
/// </summary>
void Player::Update() {

	// 旋回制御
	if (turnTimer_ > 0.0f) {

		turnTimer_ -= 1.0f / 60.0f;

		// 左右のプレイヤー角度テーブル
		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 1.0f, std::numbers::pi_v<float> * 2.0f / 1.0f};

		// 状態に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

		// プレイヤーの角度を設定する
		// worldTransform_.rotation_.y = Lerp();
	}

	// 左右移動入力
	if (Input::GetInstance()->PushKey(DIK_RIGHT) || Input::GetInstance()->PushKey(DIK_LEFT)) {

		// 左右加速
		Vector3 acceleration = {};

		if (Input::GetInstance()->PushKey(DIK_RIGHT)) {

			if (velocity_.x < 0.0f) {

				// 速度と逆方向に入力中は急ブレーキ
				velocity_.x *= (1.0f - kAttenuation);
			}

			acceleration.x += kAcceleration;

			if (lrDirection_ != LRDirection::kRight) {
				lrDirection_ = LRDirection::kRight;
				turnFirstRotationY_ = worldTransform_.rotation_.y;
				turnTimer_ = kTimeTurn;
			}

		} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {

			if (velocity_.x > 0.0f) {

				// 速度と逆方向に入力中は急ブレーキ
				velocity_.x *= (1.0f - kAttenuation);
			}

			acceleration.x -= kAcceleration;

			if (lrDirection_ != LRDirection::kLeft) {
				lrDirection_ = LRDirection::kLeft;
				turnFirstRotationY_ = worldTransform_.rotation_.y;
				turnTimer_ = kTimeTurn;
			}
		}

		// 加速/減速
		velocity_.x += acceleration.x;

		// 最大速度制限
		velocity_.x = std::clamp(velocity_.x, -kLimitRunSpeed, kLimitRunSpeed);

	} else {

		// 非入力時は移動減衰をかける
		velocity_.x *= (1.0f - kAttenuation);
	}

	// 移動処理
	worldTransform_.translation_.x += velocity_.x;

	// 行列を定数バッファに転送
	WorldTransformUpdate(worldTransform_);
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw() {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *camera_, textureHandle_);
}