#pragma once
#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class GaussianBlurGraphicsPipeline : public GraphicsPipeline
{
public:
	GaussianBlurGraphicsPipeline();
private:
	void InitializePSO() override;
};