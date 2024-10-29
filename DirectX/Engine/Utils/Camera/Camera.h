#pragma once
#include "Utils/Math/Vector3.h"
#include "Utils/Math/Matrix4x4.h"
#include "Utils/Transform/Transform.h"
#include <wrl.h>
#include <d3d12.h>
#include <memory>

class DebugCamera;

class Camera {

public:

	struct CameraForGPU
	{
		Vector3 worldPosition;
	};

	Camera();
	~Camera();

	void Initialize();

	void DebugUpdate();
	void Update();

	const bool& GetIsDebug() const;

	const Matrix4x4& GetViewProjection() const { return viewProjectionMatrix_; }

	const Matrix4x4& GetInverseProjection() const { return inverseProjectionMatrix_; }

	static const Matrix4x4& GetOrthographicMat() { return orthographicMat_; }

	const D3D12_GPU_VIRTUAL_ADDRESS GetGPUVirtualAddress() const { return cameraForGPUResource_->GetGPUVirtualAddress(); }

	const bool InScreenCheck2D(const Vector3& position, const float& radius) const;

	void StopDebug();

private:
	Microsoft::WRL::ComPtr<ID3D12Resource> cameraForGPUResource_;
	CameraForGPU* cameraForGPUData_;

private:

	void CreateResource();

public:

	EulerTransform transform_;

private:

	std::unique_ptr<DebugCamera> debugCamera_;

	Matrix4x4 projectionMatrix_;
	Matrix4x4 inverseProjectionMatrix_;
	Matrix4x4 viewProjectionMatrix_;

	static Matrix4x4 orthographicMat_;

};