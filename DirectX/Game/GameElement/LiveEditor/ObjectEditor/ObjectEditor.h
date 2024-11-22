#pragma once
#include <memory>
#include "GameElement/IStageObject/IStageObject.h"
#include "ModelData/ModelData.h"

class ObjectEditor : public IStageObject
{
public: 
	ObjectEditor(const std::string& mainName, const std::string& name, const uint32_t& no);

	void Initialize() override;
	void Update(const float& time) override;
	void Draw(const Camera& camera) override;
private:
	void SetGlobalVariable() override;
	void ApplyGlobalVariable() override;
	void AddInstancing();
	void AddInstancing(const Matrix4x4& matrix);
	const InstancingGroupData* GetInstancingData(const std::string& tag);
private:
	const ModelData* modelData_;
	std::string modelName_;
	Vector3 position_;
	Vector3 rotate_;
	Vector3 scale_;
	Vector4 color_;
	float allScale_;
	bool isTwin_;
	bool isOutLine_;
	bool isBloom_;
};
