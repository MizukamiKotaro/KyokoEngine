#pragma once
#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class SpriteGraphicsPipeline : public GraphicsPipeline
{
public:
	SpriteGraphicsPipeline();
private:
	void InitializePSO() override;
};