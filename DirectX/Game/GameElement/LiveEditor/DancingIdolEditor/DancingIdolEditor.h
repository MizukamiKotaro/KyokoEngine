#pragma once
#include "MMD/PMDModel/PMDModel.h"
#include "GameElement/BaseStageObject/BaseStageObject.h"
#include <memory>

class DancingIdolEditor : public BaseStageObject
{
public: 

	DancingIdolEditor(const std::string& mainName, const std::string& name, uint32_t no);
	void SetTime(float time) override;
	void Update(float time) override;
	void Draw(const Camera& camera) override;

private:
	void SetGlobalVariable() override;
	void ApplyGlobalVariable() override;
	
	std::unique_ptr<PMDModel> idol_;
	Vector3 firstPosition_;
};
