#pragma once
#include <array>
#include <memory>
#include "GameElement/BaseStageObject/BaseStageObject.h"

class SpotLightBoxAnimationEditor;

class TwinSpotLightBoxAnimationEditor : public BaseStageObject
{
public:
	TwinSpotLightBoxAnimationEditor(const std::string& mainName, const std::string& name, uint32_t no);
	void SetTime(float time) override;
	void Update(float time) override;
	void Draw(const Camera& camera) override;
	void DrawLight(const Camera& camera) override;

private:
	void SetGlobalVariable() override;
	void ApplyGlobalVariable() override;

public:
	std::array<std::unique_ptr<SpotLightBoxAnimationEditor>, 2> lights_;
};