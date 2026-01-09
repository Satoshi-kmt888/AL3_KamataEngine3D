#define NOMINMAX

#include <algorithm>
#include <cassert>
#include <numbers>

#include "Easing.h"
#include "Lerp.h"
#include "Player.h"
#include "WorldTransformUpdate.h"
#include "MapChipField.h"

using namespace KamataEngine;
//using namespace MathUtility;

void Player::Initialize(Model* model, uint32_t textureHandle, Camera* camera, const Vector3& position) {

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

void Player::Update() {

	// 旋回
	Turn();

	// 移動
	Move();

	// ワールド行列を定数バッファに転送
	WorldTransformUpdate(worldTransform_);
}

void Player::Draw() {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *camera_, textureHandle_);
}

void Player::Turn() {

	// 旋回制御
	if (turnTimer_ > 0.0f) {

		turnTimer_ -= 1.0f / 60.0f;

		// 左右のプレイヤー角度テーブル
		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 1.0f, std::numbers::pi_v<float> * 2.0f / 1.0f};

		// 状態に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];

		// プレイヤーの角度を設定する
		worldTransform_.rotation_.y = Lerp(turnFirstRotationY_, destinationRotationY, Easing(turnTimer_, EaseType::EASE_IN_OUT));
	}
}

void Player::Move() {

	// 接地状態
	if (onGround_) {

		//==================================================
		//
		//==================================================

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

					// プレイヤーの向きを右向きに設定
					lrDirection_ = LRDirection::kRight;

					// 旋回開始時の角度を記録
					turnFirstRotationY_ = worldTransform_.rotation_.y;

					// 旋回タイマーを設定
					turnTimer_ = kTimeTurn;
				}

			} else if (Input::GetInstance()->PushKey(DIK_LEFT)) {

				if (velocity_.x > 0.0f) {

					// 速度と逆方向に入力中は急ブレーキ
					velocity_.x *= (1.0f - kAttenuation);
				}

				acceleration.x -= kAcceleration;

				if (lrDirection_ != LRDirection::kLeft) {

					// プレイヤーの向きを左向きに設定
					lrDirection_ = LRDirection::kLeft;

					// 旋回開始時の角度を記録
					turnFirstRotationY_ = worldTransform_.rotation_.y;

					// 旋回タイマーを設定
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

		// 衝突情報を初期化
		CollisionMapInfo collisionMapInfo;

		// 移動量に速度の値をコピー
		collisionMapInfo.moveAmount = velocity_;

		// マップ衝突チェック
		CollisionMap(collisionMapInfo);

		if (Input::GetInstance()->PushKey(DIK_UP)) {

			// ジャンプ初速
			velocity_.y += kJumpAcceleration;
		}

	} else {

		// 落下速度
		velocity_.x += 0.0f;
		velocity_.y += -kGravityAcceleration;
		velocity_.z += 0.0f;

		// 落下速度制限
		velocity_.y = std::max(velocity_.y, -kLimitFallSpeed);
	}

	// 移動処理
	worldTransform_.translation_.x += velocity_.x;
	worldTransform_.translation_.y += velocity_.y;

	// 接地フラグ
	bool landing = false;

	if (velocity_.y <= 0.0f) {

		if (worldTransform_.translation_.y <= 1.0f) {
			landing = true;
		}
	}

	if (onGround_) {

		if (velocity_.y > 0.0f) {
			onGround_ = false;
		}

	} else {

		if (landing) {

			// めり込み排斥
			worldTransform_.translation_.y = 2.0f;

			// 摩擦による横方向減衰
			velocity_.x *= (1.0f - kAttenuation);

			// 加法速度をリセット
			velocity_.y = 0.0f;

			// 接地状態に移行
			onGround_ = true;
		}
	}
}

void Player::CollisionMap(CollisionMapInfo& info) {}

void Player::CollisionMapTop(CollisionMapInfo& info) {

	//上昇しているか？
	if (info.moveAmount.y <= 0.0f) {
		return;
	}

	//移動後の4つの角の座標
	std::array<Vector3, kNumCorner> positionsNew;

	for (uint32_t i = 0; i < positionsNew.size(); ++i) {

		positionsNew[i].x = worldTransform_.translation_.x + info.moveAmount.x;
		positionsNew[i].y = worldTransform_.translation_.y + info.moveAmount.y;
		positionsNew[i].z = worldTransform_.translation_.z + info.moveAmount.z;

		positionsNew[i] = CornerPosition(positionsNew[i], static_cast<Corner>(i));

		MapChipType mapChipType;

		//真上の当たり判定を行う
		bool hit = false;

		//左上点の判定
		IndexSet indexSet;
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[LEFT_TOP]);
		mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

		if (mapChipType == MapChipType::kBlock) {
			hit = true;
		}

		//右上点の判定
		IndexSet indexSet;
		indexSet = mapChipField_->GetMapChipIndexSetByPosition(positionsNew[RIGHT_TOP]);
		mapChipType = mapChipField_->GetMapChipTypeByIndex(indexSet.xIndex, indexSet.yIndex);

		if (mapChipType == MapChipType::kBlock) {
			hit = true;
		}
	}
}

KamataEngine::Vector3 Player::CornerPosition(const Vector3& center, Corner corner) {

	Vector3 result{};

	Vector3 offsetTable[kNumCorner] = {
	    {-kWidth / 2.0f, kHeight / 2.0f,  0.0f}, // LEFT_TOP
	    {kWidth / 2.0f,  kHeight / 2.0f,  0.0f}, // RIGHT_TOP
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0.0f}, // LEFT_BOTTOM
	    {kWidth / 2.0f,  -kHeight / 2.0f, 0.0f}  // RIGHT_BOTTOM
	};

	result.x = center.x + offsetTable[static_cast<uint32_t>(corner)].x;
	result.y = center.y + offsetTable[static_cast<uint32_t>(corner)].y;
	result.z = center.z + offsetTable[static_cast<uint32_t>(corner)].z;

	return result;
}
