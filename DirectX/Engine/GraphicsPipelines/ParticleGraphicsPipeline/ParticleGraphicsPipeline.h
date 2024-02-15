#pragma once
#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class ParticleGraphicsPipeline : public GraphicsPipeline
{
public:
	ParticleGraphicsPipeline();
private:
	void InitializePSO() override;
};