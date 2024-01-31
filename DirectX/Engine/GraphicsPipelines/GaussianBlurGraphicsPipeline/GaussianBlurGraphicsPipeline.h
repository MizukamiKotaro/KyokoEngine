#pragma once

#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class GaussianBlurGraphicsPipeline : public GraphicsPipeline
{
public:

	static GaussianBlurGraphicsPipeline* GetInstance();

private:
	GaussianBlurGraphicsPipeline() = default;
	~GaussianBlurGraphicsPipeline() = default;
	GaussianBlurGraphicsPipeline(const GaussianBlurGraphicsPipeline&) = delete;
	GaussianBlurGraphicsPipeline& operator=(const GaussianBlurGraphicsPipeline&) = delete;

	void InitializePSO() override;

};

