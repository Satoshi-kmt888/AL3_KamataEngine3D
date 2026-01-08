#include "GameScene.h"
#include "MakeMatrix.h"
#include "WorldTransformUpdate.h"

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

	// デバッグカメラ
	delete debugCamera_;

	/*
	天球
	--------------------*/

	// 天球
	delete skydome_;

	// モデルデータの開放
	delete modelSkydome_;

	/*
	マップチップ
	--------------------*/

	// マップチップフィールドの開放
	delete mapChipField_;

	/*
	ブロック
	--------------------*/

	// ワールド変換データの開放
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {
			delete worldTransformBlock;
		}
	}

	worldTransformBlocks_.clear();

	// モデルデータの開放
	delete modelBlock_;

	/*
	プレイヤー
	--------------------*/

	// プレイヤーの開放
	delete player_;

	// モデルデータの開放
	delete modelPlayer_;
}

/// <summary>
/// 初期化
/// </summary>
void GameScene::Initialize() {

	//==================================================
	// 　　　　　　　　　　　　天球
	//==================================================

	// インスタンスの生成
	skydome_ = new Skydome();

	// テクスチャハンドル
	textureHandleSkydome_ = TextureManager::Load("./Resources/skydome/skydome.jpg");

	// モデルの生成
	modelSkydome_ = Model::CreateFromOBJ("skydome", true);

	// 天球の初期化
	skydome_->Initialize(modelSkydome_, textureHandleSkydome_, &camera_);

	//==================================================
	// 　　　　　　　　　　　マップチップ
	//==================================================

	// インスタンスの生成
	mapChipField_ = new MapChipField();

	// ファイル読み込み
	mapChipField_->LoadMapChipCsv("Resources/map.csv");

	// 表示ブロックの生成
	GenerateBlocks();

	//==================================================
	// 　　　　　　　　　　　ブロック
	//==================================================

	// テクスチャハンドル
	textureHandleWoodBox_ = TextureManager::Load("./Resources/woodBox/woodBox.png");

	// 3Dモデルデータの生成
	modelBlock_ = Model::CreateFromOBJ("woodBox", true);

	//==================================================
	// 　　　　　　　　　　　プレイヤー
	//==================================================

	// プレイヤーの生成
	player_ = new Player();

	// 座標をマップチップ番号で指定
	Vector3 playerPosition = mapChipField_->GetMapChipPositionByIndex(1, 18);

	// ファイル名を指定してテクスチャを読み込む
	textureHandlePlayer_ = TextureManager::Load("./Resources/player/player.png");

	// 3Dモデルデータの生成
	modelPlayer_ = Model::CreateFromOBJ("player", true);

	// プレイヤーの初期化
	player_->Initialize(modelPlayer_, textureHandlePlayer_, &camera_, playerPosition);

	//==================================================
	// 　　　　　　　　　　カメラコントローラ
	//==================================================

	// カメラコントローラのインスタンス生成
	cameraController_ = new CameraController();

	// 初期化
	cameraController_->Initialize(&camera_);

	// カメラの移動範囲をセット
	cameraController_->SetMovableArea({18.0f, 180.0f, 9.0f, 40.0f});

	// 追従対象をセット
	cameraController_->SetTarget(player_);

	// リセット
	cameraController_->Reset();

	//==================================================
	// 　　　　　　　　　　　　カメラ
	//==================================================

	// カメラの初期化
	camera_.farZ = 1600.0f;
	camera_.Initialize();

	// デバッグカメラのインスタンス生成
	debugCamera_ = new DebugCamera(1280, 720);
}

/// <summary>
/// 更新
/// </summary>
void GameScene::Update() {

	//==================================================
	// 　　　　　　　　　　　　天球
	//==================================================

	// 天球の更新
	skydome_->Update();

	//==================================================
	// 　　　　　　　　　　　ブロック
	//==================================================

	// ブロックの更新
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			// worldTransformBlockがnullptrだったらスキップ
			if (!worldTransformBlock) {
				continue;
			}

			// ワールド行列の更新
			WorldTransformUpdate(*worldTransformBlock);
		}
	}

	//==================================================
	// 　　　　　　　　　　　プレイヤー
	//==================================================

	// プレイヤーの更新
	player_->Update();

	//==================================================
	// 　　　　　　　　　　カメラコントローラ
	//==================================================

	// カメラコントローラの更新
	cameraController_->Update();

	//==================================================
	// 　　　　　　　　　　　　カメラ
	//==================================================

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
}

/// <summary>
/// 描画
/// </summary>
void GameScene::Draw() {

	// 3Dモデル描画前処理
	Model::PreDraw();

	//==================================================
	// 　　　　　　　　　　　　天球
	//==================================================

	// 天球の描画
	skydome_->Draw();

	//==================================================
	// 　　　　　　　　　　　　ブロック
	//==================================================

	// ブロックの描画
	for (std::vector<WorldTransform*>& worldTransformBlockLine : worldTransformBlocks_) {
		for (WorldTransform* worldTransformBlock : worldTransformBlockLine) {

			// worldTransformBlockがnullptrだったらスキップ
			if (!worldTransformBlock) {
				continue;
			}

			// 3Dモデルを描画
			modelBlock_->Draw(*worldTransformBlock, camera_, textureHandleWoodBox_);
		}
	}

	//==================================================
	// 　　　　　　　　　　　プレイヤー
	//==================================================

	// プレイヤーの描画
	player_->Draw();

	// 3Dモデル描画後処理
	Model::PostDraw();
}

/// <summary>
/// 　表示ブロックの生成
/// </summary>
void GameScene::GenerateBlocks() {

	// 要素数
	uint32_t numBlockHorizontal = mapChipField_->GetNumBlockHorizontal();
	uint32_t numBlockVirtical = mapChipField_->GetNumBlockVirtical();

	// 要素数を変更する
	worldTransformBlocks_.resize(numBlockVirtical);

	// 列数を設定
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {

		// 1列の要素数を設定(横方向のブロック数)
		worldTransformBlocks_[i].resize(numBlockHorizontal);
	}

	// ブロックの生成
	for (uint32_t i = 0; i < numBlockVirtical; ++i) {
		for (uint32_t j = 0; j < numBlockHorizontal; ++j) {
			if (mapChipField_->GetMapChipTypeByIndex(j, i) == MapChipType::kBlock) {
				WorldTransform* worldTransform = new WorldTransform();

				// ブロックの初期化
				worldTransform->Initialize();

				// ブロックの配置座標
				worldTransformBlocks_[i][j] = worldTransform;
				worldTransformBlocks_[i][j]->translation_ = mapChipField_->GetMapChipPositionByIndex(j, i);
			}
		}
	}
}