#define NOMINMAX

#include <algorithm>
#include <numbers>

#include "CameraController.h"
#include "Lerp.h"
#include "Player.h"

using namespace KamataEngine;

/// <summary>
/// 初期化
/// </summary>
void CameraController::Initialize(Camera* camera) {

	// 引数のデータを記録
	camera_ = camera;

	// カメラの初期化
	camera_->Initialize();

	movableArea_.left = 0.0f;
	movableArea_.right = 100.0f;
	movableArea_.top = 0.0f;
	movableArea_.bottom = 100.0f;
}

/// <summary>
/// 更新
/// </summary>
void CameraController::Update() {

	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	// 追従対象の速度を取得
	targetVelocity_ = target_->GetVelocity();

	// 追従対象とオフセットと追従対象の速度からカメラの目標座標を計算
	targetCoord_.x = targetWorldTransform.translation_.x + targetOffset_.x + targetVelocity_.x * kVelocityBias;
	targetCoord_.y = targetWorldTransform.translation_.y + targetOffset_.y + targetVelocity_.y * kVelocityBias;
	targetCoord_.z = targetWorldTransform.translation_.z + targetOffset_.z + targetVelocity_.z * kVelocityBias;

	// 座標補間によりゆったり追従
	camera_->translation_.x = Lerp(targetCoord_.x, camera_->translation_.x, kInterpolationRate);
	camera_->translation_.y = Lerp(targetCoord_.y, camera_->translation_.y, kInterpolationRate);
	camera_->translation_.z = Lerp(targetCoord_.z, camera_->translation_.z, kInterpolationRate);

	// 追従対象の座標を取得
	targetTranslation_ = target_->GetTranslation();

	// 追従対象が画面外に出ないよう補正
	camera_->translation_.x = std::max(camera_->translation_.x, targetTranslation_.x + margin_.left);
	camera_->translation_.x = std::min(camera_->translation_.x, targetTranslation_.x + margin_.right);
	camera_->translation_.y = std::max(camera_->translation_.y, targetTranslation_.y + margin_.bottom);
	camera_->translation_.y = std::min(camera_->translation_.y, targetTranslation_.y + margin_.top);

	// 移動範囲制限
	camera_->translation_.x = std::clamp(camera_->translation_.x, movableArea_.left, movableArea_.right);
	camera_->translation_.y = std::clamp(camera_->translation_.y, movableArea_.bottom, movableArea_.top);

	// 行列を更新する
	camera_->UpdateMatrix();
}

/// <summary>
/// リセット
/// </summary>
void CameraController::Reset() {

	// 追従対象のワールドトランスフォームを参照
	const WorldTransform& targetWorldTransform = target_->GetWorldTransform();

	// 追従対象とオフセットからカメラ座標を取得
	camera_->translation_.x = targetWorldTransform.translation_.x + targetOffset_.x;
	camera_->translation_.y = targetWorldTransform.translation_.y + targetOffset_.y;
	camera_->translation_.z = targetWorldTransform.translation_.z + targetOffset_.z;
}