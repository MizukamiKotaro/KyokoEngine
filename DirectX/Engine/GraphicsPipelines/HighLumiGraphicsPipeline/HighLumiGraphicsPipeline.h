#pragma once

#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class HighLumiGraphicsPipeline : public GraphicsPipeline
{
public:

	static HighLumiGraphicsPipeline* GetInstance();

private:
	HighLumiGraphicsPipeline() = default;
	~HighLumiGraphicsPipeline() = default;
	HighLumiGraphicsPipeline(const HighLumiGraphicsPipeline&) = delete;
	HighLumiGraphicsPipeline& operator=(const HighLumiGraphicsPipeline&) = delete;

	void InitializePSO() override;

};

