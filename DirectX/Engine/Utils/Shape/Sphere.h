#pragma once
#include "Utils/Math/Vector3.h"
#include "Utils/Math/Matrix4x4.h"
#include <cstdint>
/// <summary>
/// 球
/// </summary>
class Sphere
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="center">センター</param>
	/// <param name="radius">半径</param>
	void Initialize(const Vector3& center, float radius);
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="center">センター</param>
	/// <param name="rotate">回転</param>
	/// <param name="radius">半径</param>
	void Initialize(const Vector3& center, const Vector3& rotate, float radius);
	/// <summary>
	/// 初期化
	/// </summary>
	/// <param name="center">センター</param>
	/// <param name="scale">スケール</param>
	/// <param name="rotate">回転</param>
	/// <param name="radius">半径</param>
	void Initialize(const Vector3& center, const Vector3& scale, const Vector3& rotate, float radius);

public:
	Vector3 center_; // センター
	Vector3 scale_; // スケール
	Vector3 rotate_; // 回転
	float radius_; // 半径
};

