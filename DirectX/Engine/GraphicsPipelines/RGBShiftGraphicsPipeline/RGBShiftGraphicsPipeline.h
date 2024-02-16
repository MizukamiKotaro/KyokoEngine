#pragma once
#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class RGBShiftGraphicsPipeline : public GraphicsPipeline
{
public:
	RGBShiftGraphicsPipeline();
private:
	void InitializePSO() override;
};