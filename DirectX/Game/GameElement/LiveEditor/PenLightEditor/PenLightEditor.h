#pragma once
#include "RigidAnimationModel/RigidAnimationModel.h"
#include "GameElement/IStageObject/IStageObject.h"

class Camera;

class PenLightEditor : public IStageObject
{
public:
	PenLightEditor(const std::string& mainName, const std::string& name, const uint32_t& no);
	void SetTime(const float& time) override;
	void Update(const float& time) override;
	void Draw(const Camera& camera) override;

private:
	void SetGlobalVariable() override;
	void ApplyGlobalVariable() override;

	void MakeInstancingData();
	void AddInstancing();
private:
	std::unique_ptr<RigidAnimationModel> box_;
	bool isTwin_;
	float distance_;
	int32_t num_;
	int32_t n_;
	Vector4 color_;
	Vector3 angle_;
	Vector3 scale_;
	float length_;
	float y_;

};