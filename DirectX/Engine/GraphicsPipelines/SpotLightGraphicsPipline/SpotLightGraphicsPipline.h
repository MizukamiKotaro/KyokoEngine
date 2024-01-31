#pragma once

#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

// スプライト共通部分
class SpotLightGraphicsPipline : public GraphicsPipeline
{
public:

	static SpotLightGraphicsPipline* GetInstance();

private:
	SpotLightGraphicsPipline() = default;
	~SpotLightGraphicsPipline() = default;
	SpotLightGraphicsPipline(const SpotLightGraphicsPipline&) = delete;
	SpotLightGraphicsPipline& operator=(const SpotLightGraphicsPipline&) = delete;

	void InitializePSO() override;

};

