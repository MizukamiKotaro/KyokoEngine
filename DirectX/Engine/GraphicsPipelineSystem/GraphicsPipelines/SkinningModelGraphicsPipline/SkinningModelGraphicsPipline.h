#pragma once
#include "GraphicsPipelineSystem/GraphicsPipeline/GraphicsPipeline.h"

class SkinningModelGraphicsPipline : public GraphicsPipeline
{
public:
	SkinningModelGraphicsPipline();
private:
	void InitializePSO() override;
};