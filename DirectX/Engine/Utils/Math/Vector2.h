#pragma once

/// <summary>
/// Vector2
/// </summary>
class Vector2
{
public:
	Vector2& operator=(const Vector2& other) noexcept;
	Vector2& operator+=(const Vector2& other) noexcept;
	Vector2& operator-=(const Vector2& other) noexcept;
	Vector2& operator*=(float scalar) noexcept;
	Vector2& operator/=(float scalar); // noexcept なし

	bool operator==(const Vector2& other) const noexcept;
	bool operator!=(const Vector2& other) const noexcept;

	// 長さの取得
	float Length() const;
	// 正規化の取得
	Vector2 Normalize() const;

public:
	float x = 0.0f;
	float y = 0.0f;
};

// 非メンバ演算子
[[nodiscard]] Vector2 operator+(const Vector2& v1, const Vector2& v2);
[[nodiscard]] Vector2 operator-(const Vector2& v1, const Vector2& v2);
[[nodiscard]] Vector2 operator*(const Vector2& v, float scalar);
[[nodiscard]] Vector2 operator*(float scalar, const Vector2& v);
[[nodiscard]] Vector2 operator/(const Vector2& v, float scalar);
