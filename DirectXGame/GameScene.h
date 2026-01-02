#pragma once

#include <vector>

#include "KamataEngine.h"
#include "Skydome.h"
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

	//==================================================
	//　　　　　　　　　　　　　カメラ
	//==================================================
	
	// カメラ
	KamataEngine::Camera camera_;

	// デバッグカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	// デバッグカメラ有効フラグ
	bool isDebugCameraActive_ = false;

	//==================================================
	// 　　　　　　　　　　　　天球
	//==================================================

	//天球
	Skydome* skydome_ = nullptr;

	//3Dモデル
	KamataEngine::Model* modelSkydome_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandleSkydome_ = 0;

	//==================================================
	// 　　　　　　　　　　　　ブロック
	//==================================================

	// 3Dモデル
	KamataEngine::Model* modelBlock_ = nullptr;

	// ワールド変換データ
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	//テクスチャハンドル
	uint32_t textureHandleWoodBox_ = 0;

	//==================================================
	// 　　　　　　　　　　　　プレイヤー
	//==================================================

	// プレイヤー
	Player* player_ = nullptr;

	// 3Dモデル
	KamataEngine::Model* modelPlayer_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandlePlayer_ = 0;

public:
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();
};