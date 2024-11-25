#pragma once

class Vector3;
class Quaternion;
class EulerTransform;
class QuaternionTransform;
/// <summary>
/// 4x4行列
/// </summary>
class Matrix4x4 {
public:
	/// <summary>
	/// 回転のタイプ
	/// </summary>
	enum RotateType {
		kXYZ, // xyz
		kYXZ, // yxz
		kZXY, // zxy
		kXZY, // xzy
		kYZX, // yzx
		kZYX  // zyx
	};
public:
	/// <summary>
	/// 加算
	/// </summary>
	/// <param name="m1">マトリクス1</param>
	/// <param name="m2">マトリクス2</param>
	/// <returns>加算結果</returns>
	static Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2);
	/// <summary>
	/// 減算
	/// </summary>
	/// <param name="m1">マトリクス1</param>
	/// <param name="m2">マトリクス2</param>
	/// <returns>減算結果</returns>
	static Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2);
	/// <summary>
	/// 乗算
	/// </summary>
	/// <param name="m1">マトリクス1</param>
	/// <param name="m2">マトリクス2</param>
	/// <returns>乗算結果</returns>
	static Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2);
	/// <summary>
	/// 乗算
	/// </summary>
	/// <param name="num">数字</param>
	/// <param name="m">マトリクス</param>
	/// <returns>加乗算果</returns>
	static Matrix4x4 Multiply(float num, const Matrix4x4& m);
	/// <summary>
	/// 乗算
	/// </summary>
	/// <param name="vector">Vector3</param>
	/// <param name="m">マトリクス</param>
	/// <returns>乗算結果</returns>
	static Vector3 Multiply(const Vector3& vector, const Matrix4x4& m);
	/// <summary>
	/// 逆行列
	/// </summary>
	/// <param name="m">マトリクス</param>
	/// <returns>逆行列</returns>
	static Matrix4x4 Inverse(const Matrix4x4& m);
	/// <summary>
	/// 逆行列
	/// </summary>
	/// <returns>逆行列</returns>
	Matrix4x4 Inverse();

	/// <summary>
	/// 転置行列
	/// </summary>
	/// <param name="m">マトリクス</param>
	/// <returns>転置行列</returns>
	static Matrix4x4 Transpose(const Matrix4x4& m);

	/// <summary>
	/// 単位行列
	/// </summary>
	/// <returns>単位行列</returns>
	static Matrix4x4 MakeIdentity4x4();
	/// <summary>
	/// 位置行列の作成
	/// </summary>
	/// <param name="translate">座標</param>
	/// <returns>位置行列</returns>
	static Matrix4x4 MakeTranslateMatrix(const Vector3& translate);
	/// <summary>
	/// スケール行列の作成
	/// </summary>
	/// <param name="scale">スケール</param>
	/// <returns>スケール行列</returns>
	static Matrix4x4 MakeScaleMatrix(const Vector3& scale);
	/// <summary>
	/// x軸の回転行列の作成
	/// </summary>
	/// <param name="radian">回転</param>
	/// <returns>x軸の回転行列</returns>
	static Matrix4x4 MakeRotateXMatrix(float radian);
	/// <summary>
	/// y軸の回転行列の作成
	/// </summary>
	/// <param name="radian">回転</param>
	/// <returns>y軸の回転行列</returns>
	static Matrix4x4 MakeRotateYMatrix(float radian);
	/// <summary>
	/// z軸の回転行列の作成
	/// </summary>
	/// <param name="radian">回転</param>
	/// <returns>z軸の回転行列</returns>
	static Matrix4x4 MakeRotateZMatrix(float radian);
	/// <summary>
	/// xyzの回転行列の作成
	/// </summary>
	/// <param name="rotate">回転</param>
	/// <returns>xyzの回転行列</returns>
	static Matrix4x4 MakeRotateXYZMatrix(const Vector3& rotate);
	/// <summary>
	/// 回転行列の作成
	/// </summary>
	/// <param name="rotate">回転</param>
	/// <param name="rotateOrder">タイプ</param>
	/// <returns>回転行列</returns>
	static Matrix4x4 MakeRotateMatrix(const Vector3& rotate, RotateType rotateOrder);
	/// <summary>
	/// アフィン行列の作成
	/// </summary>
	/// <param name="scale">スケール</param>
	/// <param name="rotate">回転</param>
	/// <param name="translate">座標</param>
	/// <returns>アフィン行列</returns>
	static Matrix4x4 MakeAffinMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate);
	/// <summary>
	/// アフィン行列の作成
	/// </summary>
	/// <param name="scale">スケール</param>
	/// <param name="rotate">回転</param>
	/// <param name="translate">座標</param>
	/// <param name="rotateOrder">タイプ</param>
	/// <returns>アフィン行列</returns>
	static Matrix4x4 MakeAffinMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate, RotateType rotateOrder);
	/// <summary>
	/// アフィン行列の作成
	/// </summary>
	/// <param name="scale">スケール</param>
	/// <param name="rotate">回転</param>
	/// <param name="translate">座標</param>
	/// <returns>アフィン行列</returns>
	static Matrix4x4 MakeAffinMatrix(const Vector3& scale, const Quaternion& rotate, const Vector3& translate);
	/// <summary>
	/// アフィン行列の作成
	/// </summary>
	/// <param name="transform">トランスフォーム</param>
	/// <returns>アフィン行列</returns>
	static Matrix4x4 MakeAffinMatrix(const EulerTransform& transform);
	/// <summary>
	/// アフィン行列の作成
	/// </summary>
	/// <param name="transform">トランスフォーム</param>
	/// <returns>アフィン行列</returns>
	static Matrix4x4 MakeAffinMatrix(const QuaternionTransform& transform);
	/// <summary>
	/// 透視投影行列の作成
	/// </summary>
	/// <param name="fovY">高さ</param>
	/// <param name="aspectRatio">アスペクト比</param>
	/// <param name="nearClip">近く</param>
	/// <param name="farClip">遠く</param>
	/// <returns>透視投影行列</returns>
	static Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip);
	/// <summary>
	/// 正射影行列の作成
	/// </summary>
	/// <param name="left">左</param>
	/// <param name="top">上</param>
	/// <param name="right">右</param>
	/// <param name="bottom">下</param>
	/// <param name="nearClip">近く</param>
	/// <param name="farClip">遠く</param>
	/// <returns>正射影行列</returns>
	static Matrix4x4 MakeOrthographicMatrix(float left, float top, float right, float bottom, float nearClip, float farClip);
	/// <summary>
	/// ビューポート変換行列
	/// </summary>
	/// <param name="left">左</param>
	/// <param name="top">上</param>
	/// <param name="width">横幅</param>
	/// <param name="height">縦幅</param>
	/// <param name="minDepth">最小深度</param>
	/// <param name="maxDepth">最高深度</param>
	/// <returns>ビューポート変換行列</returns>
	static Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth);

	/// <summary>
	/// 任意軸回転行列の作成
	/// </summary>
	/// <param name="axis">任意軸</param>
	/// <param name="angle">回転</param>
	/// <returns>任意軸回転行列</returns>
	static Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle);
	/// <summary>
	/// ある方向からある方向への回転
	/// </summary>
	/// <param name="from">from</param>
	/// <param name="to">to</param>
	/// <returns>回転行列</returns>
	static Matrix4x4 DirectionToDirection(const Vector3& from, const Vector3& to);
	/// <summary>
	/// 回転行列
	/// </summary>
	/// <param name="quaternion">クォータニオン</param>
	/// <returns>回転行列</returns>
	static Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion);
	/// <summary>
	/// Vector3の回転
	/// </summary>
	/// <param name="vector">Vector3</param>
	/// <param name="quaternion">クォータニオン</param>
	/// <returns>回転後のVector3</returns>
	static Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion);

public:
	float m[4][4]; // 行列
};
/// <summary>
/// 加算
/// </summary>
/// <param name="m1">マトリクス1</param>
/// <param name="m2">マトリクス2</param>
/// <returns>加算結果</returns>
Matrix4x4 operator+(const Matrix4x4 m1, const Matrix4x4& m2);
/// <summary>
/// 減算
/// </summary>
/// <param name="m1">マトリクス1</param>
/// <param name="m2">マトリクス2</param>
/// <returns>減算結果</returns>
Matrix4x4 operator-(const Matrix4x4 m1, const Matrix4x4& m2);
/// <summary>
/// 乗算
/// </summary>
/// <param name="m1">マトリクス1</param>
/// <param name="m2">マトリクス2</param>
/// <returns></returns>
Matrix4x4 operator*(const Matrix4x4 m1, const Matrix4x4& m2);
/// <summary>
/// 乗算
/// </summary>
/// <param name="s">数字</param>
/// <param name="m">マトリクス</param>
/// <returns>乗算結果</returns>
Matrix4x4 operator*(float s, const Matrix4x4& m);
/// <summary>
/// 乗算
/// </summary>
/// <param name="m">マトリクス</param>
/// <param name="s">数字</param>
/// <returns>乗算結果</returns>
Matrix4x4 operator*(const Matrix4x4& m, float s);
/// <summary>
/// 乗算
/// </summary>
/// <param name="v">Vector3</param>
/// <param name="m">マトリクス</param>
/// <returns>乗算結果</returns>
Vector3 operator*(const Vector3& v, const Matrix4x4& m);
/// <summary>
/// 乗算
/// </summary>
/// <param name="m">マトリクス</param>
/// <param name="v">Vector3</param>
/// <returns>乗算結果</returns>
Vector3 operator*(const Matrix4x4& m, const Vector3& v);