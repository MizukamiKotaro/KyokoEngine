#pragma once
#include "BaseModel/BaseModel.h"
#include "ModelData/SkinClustr.h"

class DescriptorHeap;

class SkinningModel : public BaseModel
{
public:

	// Model(const std::string& fileName);
	// 例)
	// Cubeフォルダ
	//   Cube.obj
	//   Cube.mtl
	// の状態

	/// <summary>
	/// モデルの生成
	/// </summary>
	/// <param name="fileName">.objが入っているフォルダの名前( "Cube" 等)</param>
	SkinningModel(const std::string& fileName, const bool& ispmx = false);
	~SkinningModel();

	void SetTime(float time);
	void Update(float time = 0) override;
	void Draw(const Camera& camera, BlendMode blendMode = BlendMode::kBlendModeNormal) const override;

public:
	static void StaticInitialize();
	void LoadGLTF(const std::string& fileName, bool ispmx = false);

	const Matrix4x4 GetRotateMatrix() override;

	const SkinCluster& GetSkinCluter() const { return *skinCluter_.get(); }

private:
	void AnimationUpdate(float time);
	void LoadAnimation(const std::string& fileName);
	
	Vector3 CalculateValue(AnimationCurve<Vector3>& keyframes, float time);
	Quaternion CalculateValue(AnimationCurve<Quaternion>& keyframes, float time);

	void CreateSkeleton();
	void CreateSkinCluster();
	int32_t Createjoint(const NodeData& node, const std::optional<int32_t>& parent, std::vector<Joint>& joints);

	void ApplyAnimation();
	void UpdateSkeleton();
	void UpdateSkinAnimation();
	void UpdateCompute();

private:
	static DescriptorHeap* srvHeap_;

	std::unique_ptr<Animation> animation_;
	std::unique_ptr<Skeleton> skeleton_;
	std::unique_ptr<SkinCluster> skinCluter_;
	float animationTime_;

	bool isSetTime_;
};