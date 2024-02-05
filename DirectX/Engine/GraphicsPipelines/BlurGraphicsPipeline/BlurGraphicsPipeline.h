#pragma once
#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class BlurGraphicsPipeline : public GraphicsPipeline
{
public:
	BlurGraphicsPipeline();
private:
	void InitializePSO() override;
};