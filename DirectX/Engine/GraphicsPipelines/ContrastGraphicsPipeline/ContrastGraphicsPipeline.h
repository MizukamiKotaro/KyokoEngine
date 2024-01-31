#pragma once

#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class ContrastGraphicsPipeline : public GraphicsPipeline
{
public:

	static ContrastGraphicsPipeline* GetInstance();

private:
	ContrastGraphicsPipeline() = default;
	~ContrastGraphicsPipeline() = default;
	ContrastGraphicsPipeline(const ContrastGraphicsPipeline&) = delete;
	ContrastGraphicsPipeline& operator=(const ContrastGraphicsPipeline&) = delete;

	void InitializePSO() override;

};

