#pragma once

#include "KamataEngine.h"
#include "Player.h"

// ゲームシーン
class GameScene {

public:
	// コンストラクタ
	GameScene();

	// デストラクタ
	~GameScene();

private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;

	// 3Dモデル
	KamataEngine::Model* model_ = nullptr;

	// カメラ
	KamataEngine::Camera camera_;

	// プレイヤー
	Player* player_ = nullptr;

public:
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();
};