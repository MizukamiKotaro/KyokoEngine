#pragma once
#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class HighLumiGraphicsPipeline : public GraphicsPipeline
{
public:
	HighLumiGraphicsPipeline();
private:
	void InitializePSO() override;
};