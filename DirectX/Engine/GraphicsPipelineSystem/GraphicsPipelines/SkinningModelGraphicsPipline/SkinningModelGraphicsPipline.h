#pragma once
#include "GraphicsPipelineSystem/GraphicsPipeline/GraphicsPipeline.h"

class SkinningModelGraphicsPipeline : public GraphicsPipeline
{
public:
	SkinningModelGraphicsPipeline();
private:
	void InitializePSO() override;
};