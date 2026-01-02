#include <cassert>

#include "Skydome.h"
#include "WorldTransformUpdate.h"

using namespace KamataEngine;

/// <summary>
///
/// </summary>
/// <param name="model">モデル</param>
/// <param name="textureHandle">テクスチャハンドル</param>
/// <param name="camera">カメラ</param>
void Skydome::Initialize(Model* model, uint32_t textureHandle, Camera* camera) {

	// NULLポインタチェック
	assert(model);

	// 引数のデータをメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;
	camera_ = camera;

	// ワールド変換の初期化
	worldTransform_.Initialize();
}

/// <summary>
/// 更新
/// </summary>
void Skydome::Update() {

	// 行列を定数バッファに転送
	WorldTransformUpdate(worldTransform_);
}

/// <summary>
/// 描画
/// </summary>
void Skydome::Draw() {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, *camera_);
}