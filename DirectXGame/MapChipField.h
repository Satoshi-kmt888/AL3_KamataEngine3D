#pragma once

#include <vector>

#include "KamataEngine.h"

/// <summary>
/// マップチップの種類
/// </summary>
enum class MapChipType { kBlank, kBlock };

/// <summary>
/// マップチップデータ
/// </summary>
struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

/// <summary>
/// マップチップフィールド
/// </summary>
class MapChipField {

private:
	// 1ブロックのサイズ
	static inline const float kBlockWidth = 2.0f;
	static inline const float kBlockHeight = 2.0f;

	// ブロックの個数
	static inline const uint32_t kNumBlockHorizontal = 100;
	static inline const uint32_t kNumBlockVirtical = 20;

	// マップチップデータ
	MapChipData mapChipData_;

public:
	// 要素数の取得
	uint32_t GetNumBlockHorizontal() { return kNumBlockHorizontal; }
	uint32_t GetNumBlockVirtical() { return kNumBlockVirtical; }

public:
	/// <summary>
	/// マップチップデータのリセット
	/// </summary>
	void ResetMapChipData();

	/// <summary>
	/// マップの読み込み
	/// </summary>
	/// <param name="filePath">ファイルの場所</param>
	void LoadMapChipCsv(const std::string& filePath);

	/// <summary>
	/// マップチップの種別を取得
	/// </summary>
	/// <param name="xIndex">横のインデックス</param>
	/// <param name="yIndex">縦のインデックス</param>
	/// <returns></returns>
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex, uint32_t yIndex);

	/// <summary>
	/// マップチップの座標を取得
	/// </summary>
	/// <param name="xIndex">横のインデックス</param>
	/// <param name="yIndex">縦のインデックス</param>
	/// <returns></returns>
	KamataEngine::Vector3 GetMapChipPositionByIndex(uint32_t xIndex, uint32_t yIndex);
};
