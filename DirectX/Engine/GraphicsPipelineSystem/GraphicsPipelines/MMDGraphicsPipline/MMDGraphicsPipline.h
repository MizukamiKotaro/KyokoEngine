#pragma once
#include "GraphicsPipelineSystem/GraphicsPipeline/GraphicsPipeline.h"

class MMDGraphicsPipline : public GraphicsPipeline
{
public:
	MMDGraphicsPipline();
private:
	void InitializePSO() override;
};