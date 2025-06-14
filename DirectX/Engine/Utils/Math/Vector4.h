#pragma once

/// <summary>
/// Vector4
/// </summary>
class Vector4
{
public:
	/// <summary>
	/// 比較演算子、等しいか
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool operator==(const Vector4& other) const noexcept {
		return x == other.x && y == other.y;
	}
	/// <summary>
	/// 比較演算子
	/// </summary>
	/// <param name="other">等しくないか</param>
	/// <returns></returns>
	bool operator!=(const Vector4& other) const noexcept {
		return !(*this == other);
	}

	float x; // x
	float y; // y
	float z; // z
	float w; // w
};