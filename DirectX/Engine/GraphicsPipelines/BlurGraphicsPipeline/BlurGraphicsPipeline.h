#pragma once

#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class BlurGraphicsPipeline : public GraphicsPipeline
{
public:

	static BlurGraphicsPipeline* GetInstance();

private:
	BlurGraphicsPipeline() = default;
	~BlurGraphicsPipeline() = default;
	BlurGraphicsPipeline(const BlurGraphicsPipeline&) = delete;
	BlurGraphicsPipeline& operator=(const BlurGraphicsPipeline&) = delete;

	void InitializePSO() override;

};

