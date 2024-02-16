#pragma once
#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class ScanNoiseGraphicsPipeline : public GraphicsPipeline
{
public:
	ScanNoiseGraphicsPipeline();
private:
	void InitializePSO() override;
};