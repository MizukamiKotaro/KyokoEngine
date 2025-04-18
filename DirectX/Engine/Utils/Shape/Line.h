#pragma once
#include "Utils/Math/Vector3.h"

/// <summary>
/// 直線
/// </summary>
struct Line
{
	Vector3 origin; // 始点
	Vector3 diff; // 終点への差分ベクトル
};
/// <summary>
/// 半直線
/// </summary>
struct Ray
{
	Vector3 origin; // 始点
	Vector3 diff; // 終点への差分ベクトル
};
/// <summary>
/// 線分
/// </summary>
struct Segment
{
	Vector3 origin; // 始点
	Vector3 diff; // 終点への差分ベクトル
};