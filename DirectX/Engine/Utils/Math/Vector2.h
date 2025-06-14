#pragma once
/// <summary>
/// Vector2
/// </summary>
class Vector2
{
public:
	/// <summary>
	/// 代入
	/// </summary>
	/// <param name="obj">vector2</param>
	/// <returns>obj</returns>
	Vector2& operator=(const Vector2& obj) {
		x = obj.x;
		y = obj.y;
		return *this;
	}
	/// <summary>
	/// 加算
	/// </summary>
	/// <param name="obj">vector2</param>
	void operator+=(const Vector2& obj) {
		this->x = this->x + obj.x;
		this->y = this->y + obj.y;
	}
	/// <summary>
	/// 減算
	/// </summary>
	/// <param name="obj">vector2</param>
	void  operator-=(const Vector2& obj) {
		this->x -= obj.x;
		this->y -= obj.y;
	}
	/// <summary>
	/// 乗算
	/// </summary>
	/// <param name="a">スカラー</param>
	void operator*=(float a) {
		this->x *= a;
		this->y *= a;
	}
	/// <summary>
	/// 除算
	/// </summary>
	/// <param name="a">スカラー</param>
	void operator/=(float a) {
		this->x /= a;
		this->y /= a;
	}
	/// <summary>
	/// 比較演算子、等しいか
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	bool operator==(const Vector2& other) const noexcept {
		return x == other.x && y == other.y;
	}
	/// <summary>
	/// 比較演算子
	/// </summary>
	/// <param name="other">等しくないか</param>
	/// <returns></returns>
	bool operator!=(const Vector2& other) const noexcept {
		return !(*this == other);
	}
	/// <summary>
	/// 長さの取得
	/// </summary>
	/// <returns>長さ</returns>
	float Length(); 
	/// <summary>
	/// 正規化の取得
	/// </summary>
	/// <returns>正規化</returns>
	Vector2 Normalize();

public:
	float x; // x
	float y; // y
};
/// <summary>
/// 加算
/// </summary>
/// <param name="obj1">v1</param>
/// <param name="obj2">v2</param>
/// <returns>加算結果</returns>
Vector2 operator+(const Vector2& obj1, const Vector2& obj2);
/// <summary>
/// 減算
/// </summary>
/// <param name="obj1">v1</param>
/// <param name="obj2">v2</param>
/// <returns>減算結果</returns>
Vector2 operator-(const Vector2& obj1, const Vector2& obj2);
/// <summary>
/// 乗算
/// </summary>
/// <param name="obj">vector2</param>
/// <param name="a">スカラー</param>
/// <returns>乗算結果</returns>
Vector2 operator*(const Vector2& obj, float a);
/// <summary>
/// 乗算
/// </summary>
/// <param name="a">スカラー</param>
/// <param name="obj">vector2</param>
/// <returns>乗算結果</returns>
Vector2 operator*(float a, const Vector2& obj);
/// <summary>
/// 除算
/// </summary>
/// <param name="obj">vector2</param>
/// <param name="a">スカラー</param>
/// <returns>除算結果</returns>
Vector2 operator/(const Vector2& obj, float a);