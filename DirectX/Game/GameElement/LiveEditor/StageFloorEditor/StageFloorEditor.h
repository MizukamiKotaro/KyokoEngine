#pragma once
#include "Model.h"
#include <memory>
#include "GameElement/BaseStageObject/BaseStageObject.h"
#include "Noise/Noise.h"
#include "PostEffect/PostEffect.h"

class StageFloorEditor : public BaseStageObject
{
public:
	StageFloorEditor(const std::string& mainName, const std::string& name, uint32_t no);

	void Initialize() override;
	void Update(float time) override;
	void Draw(const Camera& camera) override;

private:
	void SetGlobalVariable() override;
	void ApplyGlobalVariable() override;

	void WaterInitialize();
	void WaterUpdate(float time);

	std::unique_ptr<Model> model_;
	std::unique_ptr<PostEffect> post_;
	std::unique_ptr<Noise> noise_;
	uint32_t uneune_;
	bool isWater_;
	bool isStage_;
};
