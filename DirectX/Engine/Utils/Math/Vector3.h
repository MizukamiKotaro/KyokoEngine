#pragma once
/// <summary>
/// Vector3
/// </summary>
class Vector3
{
public:
	/// <summary>
	/// イコール
	/// </summary>
	/// <param name="obj">vector3</param>
	/// <returns>数値が同じか</returns>
	bool operator==(const Vector3& obj) const {
		if (x == obj.x && y == obj.y && z == obj.z) {
			return true;
		}
		return false;
	}
	/// <summary>
	/// ノットイコール
	/// </summary>
	/// <param name="obj">vector3</param>
	/// <returns>数値が違うか</returns>
	bool operator!=(const Vector3& obj) {
		if (x != obj.x || y != obj.y || z != obj.z) {
			return true;
		}
		return false;
	}

	/// <summary>
	/// 代入
	/// </summary>
	/// <param name="obj">vector3</param>
	/// <returns>obj</returns>
	Vector3& operator=(const Vector3& obj) {
		x = obj.x;
		y = obj.y;
		z = obj.z;
		return *this;
	}

	/// <summary>
	/// 加算
	/// </summary>
	/// <param name="obj">vector3</param>
	void operator+=(Vector3 obj) {
		this->x = this->x + obj.x;
		this->y = this->y + obj.y;
		this->z = this->z + obj.z;
	}

	/// <summary>
	/// 減算
	/// </summary>
	/// <param name="obj">vector3</param>
	void  operator-=(Vector3 obj) {
		this->x -= obj.x;
		this->y -= obj.y;
		this->z -= obj.z;
	}

	/// <summary>
	/// 乗算
	/// </summary>
	/// <param name="a">スカラー</param>
	void operator*=(float a) {
		this->x *= a;
		this->y *= a;
		this->z *= a;
	}

	/// <summary>
	/// 除算
	/// </summary>
	/// <param name="a">スカラー</param>
	void operator/=(float a) {
		this->x /= a;
		this->y /= a;
		this->z /= a;
	}
	/// <summary>
	/// 長さの取得
	/// </summary>
	/// <returns>長さ</returns>
	float Length();
	/// <summary>
	/// 2つのベクトルの長さの取得
	/// </summary>
	/// <param name="pos">ポジション</param>
	/// <returns>長さ</returns>
	float Length(const Vector3& pos);
	/// <summary>
	/// 正規化の取得
	/// </summary>
	/// <returns>正規化</returns>
	Vector3 Normalize();
	/// <summary>
	/// クランプ
	/// </summary>
	/// <param name="min">最小値</param>
	/// <param name="max">最大値</param>
	/// <returns>クランプ結果</returns>
	Vector3 Clamp(float min, float max);

public:
	float x; // x
	float y; // y
	float z; // z
};
/// <summary>
/// 加算
/// </summary>
/// <param name="obj1">v1</param>
/// <param name="obj2">v2</param>
/// <returns>加算結果</returns>
Vector3 operator+(const Vector3& obj1, const Vector3& obj2);

/// <summary>
/// 減算
/// </summary>
/// <param name="obj1">v1</param>
/// <param name="obj2">v2</param>
/// <returns>減算結果</returns>
Vector3 operator-(const Vector3& obj1, const Vector3& obj2);

/// <summary>
/// 乗算
/// </summary>
/// <param name="a">スカラー</param>
/// <param name="obj">vector3</param>
/// <returns>乗算結果</returns>
Vector3 operator*(float a, const Vector3& obj);
/// <summary>
/// 乗算
/// </summary>
/// <param name="obj">vector3</param>
/// <param name="a">スカラー</param>
/// <returns>乗算結果</returns>
Vector3 operator*(const Vector3& obj, float a);

/// <summary>
/// 除算
/// </summary>
/// <param name="obj">vector3</param>
/// <param name="a">スカラー</param>
/// <returns>除算結果</returns>
Vector3 operator/(const Vector3& obj, float a);
/// <summary>
/// 加算
/// </summary>
/// <param name="obj">vector3</param>
/// <returns>加算結果</returns>
Vector3 operator+(const Vector3& obj);
/// <summary>
/// 減算
/// </summary>
/// <param name="obj">vector3</param>
/// <returns>減算結果</returns>
Vector3 operator-(const Vector3& obj);