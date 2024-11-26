#pragma once
#include <memory>
#include "GameElement/BaseStageObject/BaseStageObject.h"
#include "ModelData/ModelData.h"

class ObjectEditor : public BaseStageObject
{
public: 
	ObjectEditor(const std::string& mainName, const std::string& name, uint32_t no);

	void Initialize() override;
	void Update(float time) override;
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
