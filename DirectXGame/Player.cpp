#include <cassert>

#include "Player.h"
#include "WorldTransformUpdate.h"

using namespace KamataEngine;

/// <summary>
/// 初期化
/// </summary>
void Player::Initialize(Model* model, uint32_t textureHandle, Camera* camera) {

	// NULLポインタチェック
	assert(model);

	// 引数のデータをメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;

	// ワールド変換の初期化
	worldTransform_.translation_.x = 2.0f;
	worldTransform_.translation_.y = 2.0f;
	worldTransform_.Initialize();
}

/// <summary>
/// 更新
/// </summary>
void Player::Update() {

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