#include <algorithm>

#include "CameraController.h"
#include "Lerp.h"
#include "Player.h"

using namespace KamataEngine;

/// <summary>
/// 初期化
/// </summary>
void CameraController::Initialize(Camera* camera) {

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

	// 追従対象とオフセットからカメラの目標座標を計算
	targetCoord_.x = targetWorldTransform.translation_.x + targetOffset_.x;
	targetCoord_.y = targetWorldTransform.translation_.y + targetOffset_.y;
	targetCoord_.z = targetWorldTransform.translation_.z + targetOffset_.z;

	// 座標補間によりゆったり追従
	camera_->translation_.x = Lerp(targetCoord_.x, camera_->translation_.x, kInterpolationRate);
	camera_->translation_.y = Lerp(targetCoord_.y, camera_->translation_.y, kInterpolationRate);
	camera_->translation_.z = Lerp(targetCoord_.z, camera_->translation_.z, kInterpolationRate);

	// 移動範囲制限
	camera_->translation_.x = std::clamp(camera_->translation_.x, movableArea_.left, movableArea_.right);
	camera_->translation_.y = std::clamp(camera_->translation_.y, movableArea_.top, movableArea_.bottom);

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