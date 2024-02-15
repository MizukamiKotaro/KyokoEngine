#pragma once
#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class ModelGraphicsPipline : public GraphicsPipeline
{
public:
	ModelGraphicsPipline();
private:
	void InitializePSO() override;
};