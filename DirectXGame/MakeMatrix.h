#pragma once

#include "KamataEngine.h"

//==================================================
// 　　　　　　　　　　　行列の計算
//==================================================

// 行列の積
KamataEngine::Matrix4x4 MatrixMultiply(const KamataEngine::Matrix4x4& matrix1, const KamataEngine::Matrix4x4& matrix2);

//==================================================
// 　　　　　　　　　　　SRT行列
//==================================================

// 拡縮行列
KamataEngine::Matrix4x4 MakeScaleMatrix(const KamataEngine::Vector3& scale);

// 回転行列
KamataEngine::Matrix4x4 MakeRotateXMatrix(float radian);
KamataEngine::Matrix4x4 MakeRotateYMatrix(float radian);
KamataEngine::Matrix4x4 MakeRotateZMatrix(float radian);

// 平行移動行列
KamataEngine::Matrix4x4 MakeTranslateMatrix(const KamataEngine::Vector3& translate);

// アフィン変換行列
KamataEngine::Matrix4x4 MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rotate, const KamataEngine::Vector3& translate);

//==================================================
// 　　　　　　　　　　カメラの行列
//==================================================

// ビュー行列
KamataEngine::Matrix4x4 MakeInverseMatrix(const KamataEngine::Matrix4x4& m);

// プロジェクション行列
KamataEngine::Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);