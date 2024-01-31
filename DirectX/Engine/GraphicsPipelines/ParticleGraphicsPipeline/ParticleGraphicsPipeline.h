#pragma once

#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

class ParticleGraphicsPipeline : public GraphicsPipeline
{
public:

	static ParticleGraphicsPipeline* GetInstance();

private:
	ParticleGraphicsPipeline() = default;
	~ParticleGraphicsPipeline() = default;
	ParticleGraphicsPipeline(const ParticleGraphicsPipeline&) = delete;
	ParticleGraphicsPipeline& operator=(const ParticleGraphicsPipeline&) = delete;

	void InitializePSO() override;

};

