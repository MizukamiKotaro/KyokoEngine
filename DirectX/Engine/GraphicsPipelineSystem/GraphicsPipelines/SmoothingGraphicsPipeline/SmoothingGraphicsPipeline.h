#pragma once
#include "GraphicsPipelineSystem/GraphicsPipeline/GraphicsPipeline.h"

class SmoothingGraphicsPipeline : public GraphicsPipeline
{
public:
	SmoothingGraphicsPipeline();
private:
	void InitializePSO() override;
};