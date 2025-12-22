#include "GameScene.h"

using namespace KamataEngine;

/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene() {}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {

	// モデルデータの開放
	delete model_;

	// プレイヤーの開放
	delete player_;
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize() {

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("./Resources/cube/cube.jpg");

	// 3Dモデルデータの生成
	model_ = Model::Create();

	// カメラの初期化
	camera_.Initialize();

	// プレイヤーの生成
	player_ = new Player();

	// プレイヤーの初期化
	player_->Initialize(model_, textureHandle_, &camera_);
}

/// <summary>
/// 更新
/// </summary>
void GameScene::Update() {

	// プレイヤーの更新
	player_->Update();
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {

	Model::PreDraw();

	// プレイヤーの描画
	player_->Draw();

	Model::PostDraw();
}