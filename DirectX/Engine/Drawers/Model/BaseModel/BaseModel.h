#pragma once

#include <wrl.h>
#include <d3d12.h>
#include <stdint.h>
#include <string>
#include "Utils/Math/Vector2.h"
#include "Utils/Math/Vector4.h"
#include "Utils/Math/Matrix4x4.h"
#include "Utils/Transform/Transform.h"
#include "GraphicsPipelineSystem/GraphicsPiplineManager/GraphicsPiplineManager.h"
#include "Light/Light.h"
#include "ModelData/ModelData.h"
#include "ModelDataManager.h"
#include "GraphicsPipelineSystem/BlendModeConfig.h"
#include "GraphicsPipelineSystem/PipelineTypeConfig.h"

#include "Drawers/IDrawer/IDrawer.h"

class Camera;

class BaseModel : public IDrawer
{
public:
	virtual ~BaseModel();
	void Update();

public:
	void SetTexture(const Texture* texture);
	void SetSRVGPUDescriptorHandle_(const D3D12_GPU_DESCRIPTOR_HANDLE& srvGPUDescriptorHandle) { srvGPUDescriptorHandle_ = srvGPUDescriptorHandle; }
	void SetModelData(const ModelData* modelData);
	void SetLight(const ILight* light);
	void UnUsedLight() { materialData_->enableLighting = 0; }
	void SetColor(const Vector4& color) { color_ = color; }
	virtual const Matrix4x4 GetRotateMatrix();

protected:
	struct Material
	{
		Vector4 color;
		int32_t enableLighting;
		float padding[3];
		Matrix4x4 uvTransform;
		float shininess; // 光沢度
		Vector3 supeqularColor; // 鏡面反射の色
	};

	struct TransformationMatrix {
		Matrix4x4 WVP;
		Matrix4x4 World;
		Matrix4x4 WorldInverse;
	};

	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	ComPtr<ID3D12Resource> materialResource_;
	Material* materialData_;
	ComPtr<ID3D12Resource> transformationResource_;
	TransformationMatrix* transformationData_;

protected:
	void CreateModel(const std::string& fileName);
	void CreateModel(const ModelData* modelData);

	void CreateResources();
	void CreateMaterialResource();
	void CreateTransformationResource();
	void InitVariables();

public:
	EulerTransform transform_;
	Vector4 color_;

protected:
	Light light_;

	Matrix4x4 uvMatrix_;
	Vector3 uvScale_;
	Vector3 uvRotate_;
	Vector3 uvPos_;

	const ModelData* modelData_;
	// texture変えたい時用
	const Texture* texture_;
	// ポストエフェクト用
	D3D12_GPU_DESCRIPTOR_HANDLE srvGPUDescriptorHandle_;
};