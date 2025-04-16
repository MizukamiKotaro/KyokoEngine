#pragma once
#include "Utils/Math/Vector3.h"
#include "Utils/Math/Matrix4x4.h"
#include "Utils/Transform/Transform.h"
#include <memory>
#include "Resource/Resource.h"

class DebugCamera;

/// <summary>
/// カメラ
/// </summary>
class Camera {
public:
	/// <summary>
	/// GPUに送るカメラデータ
	/// </summary>
	struct CameraForGPU
	{
		Vector3 worldPosition; // ワールド座標
	};

	Camera();
	~Camera();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// デバッグカメラの更新
	/// </summary>
	void DebugUpdate();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// デバッグカメラ中かの取得
	/// </summary>
	/// <returns>デバッグカメラ中か</returns>
	bool GetIsDebug() const;
	/// <summary>
	/// ViewProjection行列の取得
	/// </summary>
	/// <returns>ViewProjection行列</returns>
	const Matrix4x4& GetViewProjection() const { return viewProjectionMatrix_; }
	/// <summary>
	/// Projectionの逆行列の取得
	/// </summary>
	/// <returns>Projectionの逆行列</returns>
	const Matrix4x4& GetInverseProjection() const { return inverseProjectionMatrix_; }
	/// <summary>
	/// Orthographic行列の取得
	/// </summary>
	/// <returns>Orthographic行列</returns>
	static const Matrix4x4& GetOrthographicMat() { return orthographicMat_; }
	/// <summary>
	/// GPUアドレスの取得
	/// </summary>
	/// <returns>GPUアドレス</returns>
	D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const { return cameraForGPUResource_.GetGPUVirtualAddress(); }
	/// <summary>
	/// 画面内にあるかの判定
	/// </summary>
	/// <param name="position">座標</param>
	/// <param name="radius">半径</param>
	/// <returns>画面内にあるか</returns>
	bool InScreenCheck2D(const Vector3& position, float radius) const;
	/// <summary>
	/// デバッグの停止
	/// </summary>
	void StopDebug();

private:
	/// <summary>
	/// リソースの作成
	/// </summary>
	void CreateResource();

public:
	EulerTransform transform_; // トランスフォーム

private:
	Kyoko::ResourceManualRelease cameraForGPUResource_; // GPUリソース
	CameraForGPU* cameraForGPUData_; // GPUデータ

	std::unique_ptr<DebugCamera> debugCamera_; // デバッグカメラ

	Matrix4x4 projectionMatrix_; // projection行列
	Matrix4x4 inverseProjectionMatrix_; // projection逆行列
	Matrix4x4 viewProjectionMatrix_; // viewProjection行列

	static Matrix4x4 orthographicMat_; // orthographic行列

};