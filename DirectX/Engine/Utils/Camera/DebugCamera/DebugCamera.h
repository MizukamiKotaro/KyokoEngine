#pragma once
#include "Vector3.h"
#include "Vector2.h"
#include "Transform/Transform.h"

class Input;
/// <summary>
/// デバッグカメラ
/// </summary>
class DebugCamera {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	DebugCamera();

	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="transform">トランスフォーム</param>
	void Update(EulerTransform& transform);
	/// <summary>
	/// デバッグの停止
	/// </summary>
	void StopDebug();
	/// <summary>
	/// デバッグしてるかの取得
	/// </summary>
	/// <returns>デバッグしてるか</returns>
	bool IsDebug() const { return isDebug_; }

private:
	/// <summary>
	/// デバッグ更新
	/// </summary>
	/// <param name="transform">トランスフォーム</param>
	void DebugUpdate(EulerTransform& transform);

private:
	Input* input_; // 入力
	EulerTransform beforeDebugTransform_; // デバッグ前のトランスフォーム
	bool isDebug_; // デバッグ中か
	bool isPreDebug_; // 以前がデバッグ中か
	bool is2D_; // 2Dか
	bool isMouseMove_; // マウスが動いているか

	Vector3 subRotate_; // 仮回転
	Vector3 subTranslate_; // 仮位置
	Vector2 mousePos_; // マウスの座標

	bool isTranslate_; // 位置か
	bool isRotate_; // 回転か
	bool isRotateTranslate_; // 位置と回転か
};