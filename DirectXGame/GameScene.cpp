#include "GameScene.h"
#include "MakeMatrix.h"

using namespace KamataEngine;

/// <summary>
/// コンストラクタ
/// </summary>
GameScene::GameScene() {}

/// <summary>
/// デストラクタ
/// </summary>
GameScene::~GameScene() {

	/*
	カメラ
	--------------------*/

	delete debugCamera_;

	/*
	ブロック
	--------------------*/

	// モデルデータの開放
	delete modelBlock_;

	// ワールド変換データの開放
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}

	worldTransformBlocks_.clear();

	/*
	プレイヤー
	--------------------*/

	// プレイヤーの開放
	// delete player_;

	// モデルデータの開放
	// delete modelPlayer_;
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize() {

	/*
	カメラ
	--------------------*/

	// カメラの初期化
	camera_.Initialize();

	// デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 720);

	/*
	ブロック
	--------------------*/

	// 3Dモデルデータの生成
	modelBlock_ = Model::Create();

	// 要素数
	const uint32_t kNumBlockHorizontal = 10;
	const uint32_t kNumBlockVirtical = 20;

	// ブロック1個分の横幅
	const float kBlockWidth = 2.0f;
	const float kBlockHeight = 2.0f;

	// 要素数を変更する
	worldTransformBlocks_.resize(kNumBlockVirtical);

	// 列数を設定
	for (int i = 0; i < kNumBlockVirtical; i++) {

		// 1列の要素数を設定(横方向のブロック数)
		worldTransformBlocks_[i].resize(kNumBlockHorizontal);
	}

	// キューブの生成
	for (uint32_t i = 0; i < kNumBlockVirtical; ++i) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; ++j) {
			worldTransformBlocks_[i][j] = new WorldTransform();
			worldTransformBlocks_[i][j]->Initialize();
			worldTransformBlocks_[i][j]->translation_.x = kBlockWidth * i;
			worldTransformBlocks_[i][j]->translation_.y = kBlockHeight * j;
		}
	}

	for (uint32_t i = 0; i < kNumBlockVirtical; i++) {
		for (uint32_t j = 0; j < kNumBlockHorizontal; j++) {
			worldTransformBlocks_[i][j] = nullptr;
			j++;
		}
		i++;
	}

	/*
	プレイヤー
	--------------------*/

	// 3Dモデルデータの生成
	// modelPlayer_ = Model::Create();

	// プレイヤーの生成
	// player_ = new Player();

	// プレイヤーの初期化
	// player_->Initialize(modelPlayer_, textureHandle_, &camera_);

	/*
	リソース
	--------------------*/

	// ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("./Resources/cube/cube.jpg");
}

/// <summary>
/// 更新
/// </summary>
void GameScene::Update() {

	/*
	カメラ
	--------------------*/

#ifdef _DEBUG

	if (Input::GetInstance()->TriggerKey(DIK_SPACE)) {

		if (isDebugCameraActive_) {

			// デバッグカメラを無効にする
			isDebugCameraActive_ = false;

		} else {

			// デバッグカメラを有効にする
			isDebugCameraActive_ = true;
		}
	}

#endif

	if (isDebugCameraActive_) {

		// デバッグカメラの更新
		debugCamera_->Update();

		// カメラのビュー/プロジェクション行列にデバッグカメラのビュー/プロジェクション行列を代入
		camera_.matView = debugCamera_->GetCamera().matView;
		camera_.matProjection = debugCamera_->GetCamera().matProjection;

		// ビュープロジェクション行列の転送
		camera_.TransferMatrix();

	} else {

		// ビュープロジェクション行列の更新と転送
		camera_.UpdateMatrix();
	}

	/*
	ブロック
	--------------------*/

	// ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			// worldTransformBlockがnullptrだったらスキップ
			if (!worldTransformBlock) {
				continue;
			}

			// アフィン変換行列の作成
			Matrix4x4 worldMatrix = MakeAffineMatrix(worldTransformBlock->scale_, worldTransformBlock->rotation_, worldTransformBlock->translation_);

			// ワールド行列
			worldTransformBlock->matWorld_ = worldMatrix;

			// 定数バッファに転送する
			worldTransformBlock->TransferMatrix();
		}
	}

	/*
	プレイヤー
	--------------------*/

	// プレイヤーの更新
	// player_->Update();
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {

	// 3Dモデル描画前処理
	Model::PreDraw();

	/*
	ブロック
	--------------------*/

	// ブロックの描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			// worldTransformBlockがnullptrだったらスキップ
			if (!worldTransformBlock) {
				continue;
			}

			// 3Dモデルを描画
			modelBlock_->Draw(*worldTransformBlock, camera_);
		}
	}

	/*
	プレイヤー
	--------------------*/

	// プレイヤーの描画
	// player_->Draw();

	// 3Dモデル描画後処理
	Model::PostDraw();
}