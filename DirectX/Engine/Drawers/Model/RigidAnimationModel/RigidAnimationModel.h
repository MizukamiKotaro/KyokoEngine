#pragma once
#include "BaseModel/BaseModel.h"

class Camera;

class RigidAnimationModel : public BaseModel
{
public:
	RigidAnimationModel(const std::string& fileName);
	RigidAnimationModel(const ModelData* modelData, const std::string& fileName);

	void Update(const float& time = 0.0f);

	void Draw(const Camera& camera, BlendMode blendMode = BlendMode::kBlendModeNormal);

public:
	void LoadGLTF(const std::string& fileName);
	void LoadAnimation(const std::string& fileName);

	const Matrix4x4 GetRotateMatrix() override;

private:
	void AnimationUpdate(const float& time);
	Vector3 CalculateValue(const AnimationCurve<Vector3>& keyframes, const float& time);
	Quaternion CalculateValue(const AnimationCurve<Quaternion>& keyframes, const float& time);

private:
	int32_t Createjoint(const NodeData& node, const std::optional<int32_t>& parent, std::vector<Joint>& joints);

private:
	std::unique_ptr<Animation> animation_;
	float animationTime_;
};