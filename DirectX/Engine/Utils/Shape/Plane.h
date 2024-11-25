#pragma once
#include "Utils/Math/Vector3.h"
#include "Utils/Math/Matrix4x4.h"
#include <cstdint>
/// <summary>
/// 平面
/// </summary>
class Plane {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
public:
	Vector3 normal; // 法線
	float distance; // 距離
	bool isLimit = false; // 上限ありか
};
