#pragma once
#include "BaseModel/BaseModel.h"

/// <summary>
/// RigidAnimationモデル
/// </summary>
class RigidAnimationModel : public BaseModel
{
public:
	RigidAnimationModel(const std::string& fileName);
	RigidAnimationModel(const ModelData* modelData, const std::string& fileName);

	void SetTime(float time);
	void Update(float time = 0.0f) override;
	void Draw(const Camera& camera, BlendMode blendMode = BlendMode::kBlendModeNormal) const override;

public:
	void LoadGLTF(const std::string& fileName);
	void LoadAnimation(const std::string& fileName);

	const Matrix4x4 GetRotateMatrix() override;
	const QuaternionTransform& GetAnimTransform() const { return animTransform_; }
private:
	void AnimationUpdate(float time);
	Vector3 CalculateValue(const AnimationCurve<Vector3>& keyframes, float time);
	Quaternion CalculateValue(const AnimationCurve<Quaternion>& keyframes, float time);

	int32_t Createjoint(const NodeData& node, const std::optional<int32_t>& parent, std::vector<Joint>& joints);

private:
	std::unique_ptr<Animation> animation_;
	float animationTime_;
	QuaternionTransform animTransform_;
};