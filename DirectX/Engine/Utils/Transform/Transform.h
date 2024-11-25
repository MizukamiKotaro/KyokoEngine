#pragma once
#include "Utils/Math/Vector3.h"
#include "Utils/Math/Matrix4x4.h"
#include "Quaternion.h"
/// <summary>
/// オイラートランスフォーム
/// </summary>
class EulerTransform {

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	EulerTransform();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 行列の更新
	/// </summary>
	void UpdateMatrix();
	/// <summary>
	/// ワールド座標の取得
	/// </summary>
	/// <returns>ワールド座標</returns>
	const Vector3& GetWorldPosition() const;
	/// <summary>
	/// xz平面で当たっているか
	/// </summary>
	/// <param name="transform">トランスフォーム</param>
	/// <returns>xz平面で当たっているか</returns>
	bool IsCollisionXZ(const EulerTransform& transform);

	/// <summary>
	/// 平行移動のみの親のセット
	/// </summary>
	/// <param name="transform">親にするTransformのポインタ</param>
	void SetWorldTranslateParent(const EulerTransform* transform);

	/// <summary>
	/// 平行移動の親子関係の解除
	/// </summary>
	void ClearWorldTranslateParent();
	/// <summary>
	/// クォータニオンのセット
	/// </summary>
	/// <param name="qua">クォータニオン</param>
	void SetQuaRot(const Quaternion& qua);

public:
	Vector3 scale_; // スケール
	Vector3 rotate_; // 回転
	Vector3 translate_; // 座標

	Matrix4x4 worldMat_; // ワールド行列
	Vector3 worldPos_; // ワールド座標

	Quaternion rot_; // クォータニオン
	bool isQua_; // クォータニオンを使用するか

	const EulerTransform* parent_ = nullptr; // 親ポインタ
	const EulerTransform* worldTranslateParent_ = nullptr; // 平行移動用の親ポインタ
};