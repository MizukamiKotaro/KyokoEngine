#pragma once
#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class NegaPosiInverseGraphicsPipeline : public GraphicsPipeline
{
public:
	NegaPosiInverseGraphicsPipeline();
private:
	void InitializePSO() override;
};