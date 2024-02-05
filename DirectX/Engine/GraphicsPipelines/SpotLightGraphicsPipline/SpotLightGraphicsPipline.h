#pragma once
#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class SpotLightGraphicsPipline : public GraphicsPipeline
{
public:
	SpotLightGraphicsPipline();
private:
	void InitializePSO() override;
};