#pragma once

#include "KamataEngine.h"

//==================================================
// 　　　　　　　　　　　行列の計算
//==================================================

/// <summary>
/// 行列の積
/// </summary>
/// <param name="matrix1">行列1</param>
/// <param name="matrix2">行列2</param>
/// <returns></returns>
KamataEngine::Matrix4x4 MatrixMultiply(const KamataEngine::Matrix4x4& matrix1, const KamataEngine::Matrix4x4& matrix2);

//==================================================
// 　　　　　　　　　　　SRT行列
//==================================================

/// <summary>
/// 拡縮行列
/// </summary>
/// <param name="scale">拡縮係数</param>
/// <returns></returns>
KamataEngine::Matrix4x4 MakeScaleMatrix(const KamataEngine::Vector3& scale);

/// <summary>
/// X軸回りの回転行列
/// </summary>
/// <param name="radian">回転角</param>
/// <returns></returns>
KamataEngine::Matrix4x4 MakeRotateXMatrix(float radian);

/// <summary>
/// Y軸回りの回転行列
/// </summary>
/// <param name="radian">回転角</param>
/// <returns></returns>
KamataEngine::Matrix4x4 MakeRotateYMatrix(float radian);

/// <summary>
/// Z軸回りの回転行列
/// </summary>
/// <param name="radian">回転角</param>
/// <returns></returns>
KamataEngine::Matrix4x4 MakeRotateZMatrix(float radian);

/// <summary>
/// 平行移動行列
/// </summary>
/// <param name="translate">平行移動座標</param>
/// <returns></returns>
KamataEngine::Matrix4x4 MakeTranslateMatrix(const KamataEngine::Vector3& translate);

/// <summary>
/// アフィン変換行列
/// </summary>
/// <param name="scale">拡縮係数</param>
/// <param name="rotate">回転角</param>
/// <param name="translate">平行移動座標</param>
/// <returns></returns>
KamataEngine::Matrix4x4 MakeAffineMatrix(const KamataEngine::Vector3& scale, const KamataEngine::Vector3& rotate, const KamataEngine::Vector3& translate);

//==================================================
// 　　　　　　　　　　カメラの行列
//==================================================

/// <summary>
/// 逆行列
/// </summary>
/// <param name="m">行列</param>
/// <returns></returns>
KamataEngine::Matrix4x4 MakeInverseMatrix(const KamataEngine::Matrix4x4& m);

/// <summary>
/// プロジェクション行列
/// </summary>
/// <param name="fovY"></param>
/// <param name="aspectRatio"></param>
/// <param name="nearClip"></param>
/// <param name="farClip"></param>
/// <returns></returns>
KamataEngine::Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);