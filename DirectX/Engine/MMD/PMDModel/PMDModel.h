#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <stdint.h>
#include <string>
#include "Utils/Math/Vector2.h"
#include "Utils/Math/Vector4.h"
#include "Utils/Math/Matrix4x4.h"
#include "Utils/Transform/Transform.h"
#include "Light/Light.h"
#include "MMD/MMDModelData/ModelDataPMD.h"
#include "ModelDataManager.h"
#include "GraphicsPipelineSystem/BlendModeConfig.h"
#include "ModelData/SkinClustr.h"

#include "Drawers/IDrawer/IDrawer.h"

class DescriptorHeap;
class Camera;

class PMDModel : public IDrawer
{
public:
	PMDModel(const std::string& fileName);
	~PMDModel();
	void SetTime(const float& time);
	void Update(const float& time = 0.0f);
	void Draw(const Camera& camera, const BlendMode& blendMode = BlendMode::kBlendModeNormal) const;

public:
	static void StaticInitialize();
	void LoadGLTF(const std::string& fileName);
	const ModelDataPMD& GetModelData() const { return *modelData_; }
	void SetModelData(const ModelDataPMD* modelData);

	const SkinCluster& GetSkinCluter() const { return *skinCluter_.get(); }

private:

	struct TransformationMatrix {
		Matrix4x4 WVP;
		Matrix4x4 World;
		Matrix4x4 WorldInverse;
	};

	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	ComPtr<ID3D12Resource> transformationResource_;
	TransformationMatrix* transformationData_;

	void CreateModel(const std::string& fileName);

	void CreateResources();
	void CreateTransformationResource();
	void InitVariables();

	void TransformUpdate();

private:
	void AnimationUpdate(float time);
	void LoadAnimation(const std::string& fileName);

	Vector3 CalculateValue(AnimationCurve<Vector3>& keyframes, const float& time);
	Quaternion CalculateValue(AnimationCurve<Quaternion>& keyframes, const float& time);

	void CreateSkeleton();
	void CreateSkinCluster();
	int32_t Createjoint(const NodeData& node, const std::optional<int32_t>& parent, std::vector<Joint>& joints);

	void ApplyAnimation();
	void UpdateSkeleton();
	void UpdateSkinAnimation();
	void UpdateCompute();

public:
	EulerTransform transform_;

private:

	const ModelDataPMD* modelData_;


	static DescriptorHeap* srvHeap_;

	std::unique_ptr<Animation> animation_;
	std::unique_ptr<Skeleton> skeleton_;
	std::unique_ptr<SkinCluster> skinCluter_;
	float animationTime_;

	bool isSetTime_;
};