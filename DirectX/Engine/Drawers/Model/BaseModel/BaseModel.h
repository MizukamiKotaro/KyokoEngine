#pragma once
#include <stdint.h>
#include <string>
#include "Utils/Math/Vector2.h"
#include "Utils/Math/Vector4.h"
#include "Utils/Math/Matrix4x4.h"
#include "Utils/Transform/Transform.h"
#include "Light/Light.h"
#include "ModelData/ModelData.h"
#include "ModelDataManager.h"
#include "GraphicsPipelineSystem/BlendModeConfig.h"
#include "Resource/Resource.h"
#include "Drawers/DrawerBase/DrawerBase.h"

class Camera;
/// <summary>
/// モデルの基盤
/// </summary>
class BaseModel : public DrawerBase
{
public:
	virtual ~BaseModel();
	virtual void Update(float time = 0) = 0;
	virtual void Draw(const Camera& camera, BlendMode blendMode = BlendMode::kBlendModeNormal) const = 0;

public:
	void SetTexture(const Texture* texture);
	void SetSRVGPUDescriptorHandle_(D3D12_GPU_DESCRIPTOR_HANDLE srvGPUDescriptorHandle) { srvGPUDescriptorHandle_ = srvGPUDescriptorHandle; }
	void SetModelData(const ModelData* modelData);
	void SetLight(const BaseLight* light);
	void UnUsedLight() { materialData_->enableLighting = 0; }
	void SetColor(const Vector4& color);
	virtual const Matrix4x4 GetRotateMatrix();

	const Light& GetLight() const { return light_; }
	const ModelData& GetModelData() const { return *modelData_; }
	D3D12_GPU_DESCRIPTOR_HANDLE GetTextureData() const { return srvGPUDescriptorHandle_; }
	ID3D12Resource& GetMaterialData() const;
	struct Material
	{
		Vector4 color;
		int32_t enableLighting;
		float padding[3];
		Matrix4x4 uvTransform;
		float shininess; // 光沢度
		Vector3 supeqularColor; // 鏡面反射の色
		float skyboxAlpha; // スカイボックスの反射用の透明度
	};
	Material* GetMaterialData() { return materialData_; }

protected:

	struct TransformationMatrix {
		Matrix4x4 WVP;
		Matrix4x4 World;
		Matrix4x4 WorldInverse;
	};

	
	Kyoko::ResourceManualRelease materialResource_;
	Material* materialData_;
	Kyoko::ResourceManualRelease transformationResource_;
	TransformationMatrix* transformationData_;

protected:
	void CreateModel(const std::string& fileName);
	void CreateModel(const ModelData* modelData);

	void CreateResources();
	void CreateMaterialResource();
	void CreateTransformationResource();
	void InitVariables();

	void TransformUpdate();

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