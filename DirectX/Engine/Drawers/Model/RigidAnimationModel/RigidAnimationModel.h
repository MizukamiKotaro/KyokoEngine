#pragma once
#include "BaseModel/BaseModel.h"

class RigidAnimationModel : public BaseModel
{
public:
	RigidAnimationModel(const std::string& fileName);
	RigidAnimationModel(const ModelData* modelData, const std::string& fileName);

	void Update(const float& time = 0.0f) override;
	void Draw(const Camera& camera, const BlendMode& blendMode = BlendMode::kBlendModeNormal) const override;

public:
	void LoadGLTF(const std::string& fileName);
	void LoadAnimation(const std::string& fileName);

	const Matrix4x4 GetRotateMatrix() override;

	static Vector3 CalculateValue(const AnimationCurve<Vector3>& keyframes, const float& time);
	static Quaternion CalculateValue(const AnimationCurve<Quaternion>& keyframes, const float& time);

	Animation& GetAnimation() const { return *animation_.get(); }
	const float& GetAnimationTime() const { return animationTime_; }
private:
	void AnimationUpdate(const float& time);

private:
	int32_t Createjoint(const NodeData& node, const std::optional<int32_t>& parent, std::vector<Joint>& joints);

private:
	std::unique_ptr<Animation> animation_;
	float animationTime_;
};