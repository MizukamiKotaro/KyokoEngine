#pragma once

class Vector3;
class Matrix4x4;
/// <summary>
/// クォータニオン
/// </summary>
class Quaternion
{
public:
	/// <summary>
	/// 代入
	/// </summary>
	/// <param name="obj">クォータニオン</param>
	/// <returns>obj</returns>
	Quaternion& operator=(const Quaternion& obj) {
		x = obj.x;
		y = obj.y;
		z = obj.z;
		w = obj.w;
		return *this;
	}
	/// <summary>
	/// 加算
	/// </summary>
	/// <param name="obj">クォータニオン</param>
	void operator+=(const Quaternion& obj) {
		this->x = this->x + obj.x;
		this->y = this->y + obj.y;
		this->z = this->z + obj.z;
		this->w = this->w + obj.w;
	}
	/// <summary>
	/// 減算
	/// </summary>
	/// <param name="obj">クォータニオン</param>
	void  operator-=(const Quaternion& obj) {
		this->x -= obj.x;
		this->y -= obj.y;
		this->z -= obj.z;
		this->w -= obj.w;
	}
	/// <summary>
	/// 乗算
	/// </summary>
	/// <param name="a">スカラー</param>
	void operator*=(float a) {
		this->x *= a;
		this->y *= a;
		this->z *= a;
		this->w *= a;
	}
	/// <summary>
	/// 除算
	/// </summary>
	/// <param name="a">スカラー</param>
	void operator/=(float a) {
		this->x /= a;
		this->y /= a;
		this->z /= a;
		this->w /= a;
	}
	/// <summary>
	/// Slerp
	/// </summary>
	/// <param name="q0">クォータニオン0</param>
	/// <param name="q1">クォータニオン1</param>
	/// <param name="t">t</param>
	/// <returns>slerp結果</returns>
	static Quaternion Slerp(const Quaternion& q0, const Quaternion& q1, float t);
	/// <summary>
	/// 内積の取得
	/// </summary>
	/// <param name="q0">クォータニオン</param>
	/// <param name="q1">クォータニオン</param>
	/// <returns>内積</returns>
	static float Dot(const Quaternion& q0, const Quaternion& q1);
	/// <summary>
	/// 任意軸回転
	/// </summary>
	/// <param name="axis">任意軸</param>
	/// <param name="angle">回転</param>
	/// <returns>任意軸回転</returns>
	static Quaternion MakeRotateAxisAngle(const Vector3& axis, float angle);
	/// <summary>
	/// ある点からある点への回転
	/// </summary>
	/// <param name="from">from</param>
	/// <param name="to">to</param>
	/// <returns>回転</returns>
	static Quaternion DirectionToDirection(const Vector3& from, const Vector3& to);
	/// <summary>
	/// 乗算
	/// </summary>
	/// <param name="lhs">クォータニオン0</param>
	/// <param name="rhs">クォータニオン1</param>
	/// <returns>乗算結果</returns>
	static Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs);
	/// <summary>
	/// 単位クォータニオン
	/// </summary>
	/// <returns>単位クォータニオン</returns>
	static Quaternion Identity();
	/// <summary>
	/// 共役クォータニオン
	/// </summary>
	/// <returns>共役クォータニオン</returns>
	Quaternion Conjugate();
	/// <summary>
	/// ノルム
	/// </summary>
	/// <returns>ノルム</returns>
	float Norm();
	/// <summary>
	/// 正規化
	/// </summary>
	/// <returns>正規化</returns>
	Quaternion Normalize();
	/// <summary>
	/// 逆クォータニオン
	/// </summary>
	/// <returns>逆クォータニオン</returns>
	Quaternion Inverse();
	/// <summary>
	/// 回転行列
	/// </summary>
	/// <returns>回転行列</returns>
	Matrix4x4 MakeRotateMatrix();
	/// <summary>
	/// Vector3の回転
	/// </summary>
	/// <param name="vector">vector3</param>
	/// <returns>回転結果</returns>
	Vector3 RotateVector(const Vector3& vector);
	/// <summary>
	/// オイラーからクォータニオンへの変換
	/// </summary>
	/// <param name="eulerAngles">オイラー</param>
	/// <returns>クォータニオン</returns>
	static Quaternion EulerToQuaternion(const Vector3& eulerAngles);
	/// <summary>
	/// クォータニオンからオイラーに変換
	/// </summary>
	/// <param name="q">クォータニオン</param>
	/// <returns>オイラー</returns>
	static Vector3 QuaternionToEuler(const Quaternion& q);

public:
	float x; // x
	float y; // y
	float z; // z
	float w; // w
};
/// <summary>
/// 加算
/// </summary>
/// <param name="obj1">クォータニオン0</param>
/// <param name="obj2">クォータニオン1</param>
/// <returns>加算結果</returns>
Quaternion operator+(const Quaternion& obj1, const Quaternion& obj2);
/// <summary>
/// 減算
/// </summary>
/// <param name="obj1">クォータニオン0</param>
/// <param name="obj2">クォータニオン1</param>
/// <returns>減算結果</returns>
Quaternion operator-(const Quaternion& obj1, const Quaternion& obj2);
/// <summary>
/// 乗算
/// </summary>
/// <param name="obj1">クォータニオン0</param>
/// <param name="obj2">クォータニオン1</param>
/// <returns>乗算結果</returns>
Quaternion operator*(const Quaternion obj1, const Quaternion& obj2);
/// <summary>
/// 乗算
/// </summary>
/// <param name="obj">クォータニオン</param>
/// <param name="a">スカラー</param>
/// <returns>乗算結果</returns>
Quaternion operator*(const Quaternion& obj, float a);
/// <summary>
/// 乗算
/// </summary>
/// <param name="a">スカラー</param>
/// <param name="obj">クォータニオン</param>
/// <returns>乗算結果</returns>
Quaternion operator*(float a, const Quaternion& obj);
/// <summary>
/// 除算
/// </summary>
/// <param name="obj">クォータニオン</param>
/// <param name="a">スカラー</param>
/// <returns>除算結果</returns>
Quaternion operator/(const Quaternion& obj, float a);