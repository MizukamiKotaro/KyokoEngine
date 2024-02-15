#pragma once
#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class PointLightGraphicsPipline : public GraphicsPipeline
{
public:
	PointLightGraphicsPipline();
private:
	void InitializePSO() override;
};