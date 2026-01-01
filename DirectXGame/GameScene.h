#pragma once

#include <vector>

#include "KamataEngine.h"
#include "Player.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public:
	// コンストラクタ
	GameScene();

	// デストラクタ
	~GameScene();

private:
	/*
	カメラ
	--------------------*/
	// カメラ
	KamataEngine::Camera camera_;

	// デバッグカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	// デバッグカメラ有効フラグ
	bool isDebugCameraActive_ = false;

	/*
	ブロック
	--------------------*/

	// 3Dモデル
	KamataEngine::Model* modelBlock_ = nullptr;

	// ワールド変換データ
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	/*
	プレイヤー
	--------------------*/

	// 3Dモデル
	//KamataEngine::Model* modelPlayer_ = nullptr;

	// プレイヤー
	// Player* player_ = nullptr;

	/*
	リソース
	--------------------*/

	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

public:
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();
};