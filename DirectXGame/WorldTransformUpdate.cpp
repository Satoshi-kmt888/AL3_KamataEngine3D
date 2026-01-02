#include "WorldTransformUpdate.h"
#include "MakeMatrix.h"

using namespace KamataEngine;

/// <summary>
/// ワールド行列更新
/// </summary>
/// <param name="worldTransform">ワールド変換データ</param>
void WorldTransformUpdate(WorldTransform& worldTransform) {

	// スケール、回転、平行移動を合成して行列を計算する
	worldTransform.matWorld_ = MakeAffineMatrix(worldTransform.scale_, worldTransform.rotation_, worldTransform.translation_);

	// 定数バッファへの書き込み
	worldTransform.TransferMatrix();
}
