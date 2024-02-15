#pragma once
#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class ContrastGraphicsPipeline : public GraphicsPipeline
{
public:
	ContrastGraphicsPipeline();
private:
	void InitializePSO() override;
};