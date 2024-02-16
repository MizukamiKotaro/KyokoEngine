#pragma once
#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class MosaicGraphicsPipeline : public GraphicsPipeline
{
public:
	MosaicGraphicsPipeline();
private:
	void InitializePSO() override;
};