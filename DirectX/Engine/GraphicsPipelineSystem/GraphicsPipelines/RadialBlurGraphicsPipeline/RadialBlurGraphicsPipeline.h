#pragma once
#include "GraphicsPipelineSystem/GraphicsPipeline/GraphicsPipeline.h"

class RadialBlurGraphicsPipeline : public GraphicsPipeline
{
public:
	RadialBlurGraphicsPipeline();
private:
	void InitializePSO() override;
};