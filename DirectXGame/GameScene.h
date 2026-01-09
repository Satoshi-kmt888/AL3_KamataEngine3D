#pragma once

#include <vector>

#include "CameraController.h"
#include "KamataEngine.h"
#include "MapChipField.h"
#include "Player.h"
#include "Skydome.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	//==================================================
	// 　　　　　　　　　　　　天球
	//==================================================

	// 天球
	Skydome* skydome_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandleSkydome_ = 0;

	// 3Dモデル
	KamataEngine::Model* modelSkydome_ = nullptr;

	//==================================================
	// 　　　　　　　　　　　マップチップ
	//==================================================

	// マップチップフィールド
	MapChipField* mapChipField_;

	// 表示ブロックの生成
	void GenerateBlocks();

	//==================================================
	// 　　　　　　　　　　　　ブロック
	//==================================================

	// ワールド変換データ
	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_;

	// テクスチャハンドル
	uint32_t textureHandleWoodBox_ = 0;

	// 3Dモデル
	KamataEngine::Model* modelBlock_ = nullptr;

	//==================================================
	// 　　　　　　　　　　　　プレイヤー
	//==================================================

	// プレイヤー
	Player* player_ = nullptr;

	// テクスチャハンドル
	uint32_t textureHandlePlayer_ = 0;

	// 3Dモデル
	KamataEngine::Model* modelPlayer_ = nullptr;

	//==================================================
	// 　　　　　　　　　　　　　カメラ
	//==================================================

	// カメラ
	KamataEngine::Camera camera_;

	// デバッグカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	// デバッグカメラ有効フラグ
	bool isDebugCameraActive_ = false;

	// カメラコントローラ
	CameraController* cameraController_ = nullptr;
};