#pragma once

#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class SpriteGraphicsPipeline : public GraphicsPipeline
{
public:

	static SpriteGraphicsPipeline* GetInstance();

private:
	SpriteGraphicsPipeline() = default;
	~SpriteGraphicsPipeline() override = default;
	SpriteGraphicsPipeline(const SpriteGraphicsPipeline&) = delete;
	SpriteGraphicsPipeline& operator=(const SpriteGraphicsPipeline&) = delete;

	void InitializePSO() override;
};

