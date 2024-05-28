#pragma once
#include "BaseModel/BaseModel.h"
#include "ModelData/SkinClustr.h"

class Camera;

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
	SkinningModel(const std::string& fileName);
	~SkinningModel();

	void Update(const float& time);

	void Draw(const Camera& camera, BlendMode blendMode = BlendMode::kBlendModeNormal) const;

public:
	void LoadGLTF(const std::string& fileName);

	const Matrix4x4 GetRotateMatrix() override;

	const SkinCluter& GetSkinCluter() const { return *skinCluter_.get(); }

private:
	void AnimationUpdate(float time);
	void LoadAnimation(const std::string& fileName);
	
	Vector3 CalculateValue(const AnimationCurve<Vector3>& keyframes, const float& time);
	Quaternion CalculateValue(const AnimationCurve<Quaternion>& keyframes, const float& time);

private:
	void CreateSkeleton();

	void CreateSkinCluster();

	int32_t Createjoint(const NodeData& node, const std::optional<int32_t>& parent, std::vector<Joint>& joints);

	void ApplyAnimation();

	void UpdateSkeleton();

	void UpdateSkinAnimation();

private:
	std::unique_ptr<Animation> animation_;
	std::unique_ptr<Skeleton> skeleton_;
	std::unique_ptr<SkinCluter> skinCluter_;
	float animationTime_;
};