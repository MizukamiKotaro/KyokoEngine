#include "GraphicsPiplineManager.h"

#include "GraphicsPipelines/ModelGraphicsPipline/ModelGraphicsPipline.h"
#include "GraphicsPipelines/ParticleGraphicsPipeline/ParticleGraphicsPipeline.h"
#include "GraphicsPipelines/SpriteGraphicsPipeline/SpriteGraphicsPipeline.h"
#include "GraphicsPipelines/PointLightGraphicsPipline/PointLightGraphicsPipline.h"
#include "GraphicsPipelines/SpotLightGraphicsPipline/SpotLightGraphicsPipline.h"
#include "GraphicsPipelines/ContrastGraphicsPipeline/ContrastGraphicsPipeline.h"
#include "GraphicsPipelines/HighLumiGraphicsPipeline/HighLumiGraphicsPipeline.h"
#include "GraphicsPipelines/BlurGraphicsPipeline/BlurGraphicsPipeline.h"
#include "GraphicsPipelines/GaussianBlurGraphicsPipeline/GaussianBlurGraphicsPipeline.h"
#include "GraphicsPipelines/ScanNoiseGraphicsPipeline/ScanNoiseGraphicsPipeline.h"
#include "GraphicsPipelines/PipelineTypeConfig.h"

GraphicsPipelineManager* GraphicsPipelineManager::GetInstance()
{
	static GraphicsPipelineManager instance;
	return &instance;
}

void GraphicsPipelineManager::Initialize()
{
	currentPiplineType_ = PipelineType::SPRITE;

	pipelineMap_[PipelineType::SPRITE] = std::make_unique<SpriteGraphicsPipeline>();
	pipelineMap_[PipelineType::MODEL] = std::make_unique<ModelGraphicsPipline>();
	pipelineMap_[PipelineType::PARTICLE] = std::make_unique<ParticleGraphicsPipeline>();
	pipelineMap_[PipelineType::POINT_LIGHT] = std::make_unique<PointLightGraphicsPipline>();
	pipelineMap_[PipelineType::SPOT_LIGHT] = std::make_unique<SpotLightGraphicsPipline>();
	pipelineMap_[PipelineType::CONTRAST] = std::make_unique<ContrastGraphicsPipeline>();
	pipelineMap_[PipelineType::HIGH_LUMI] = std::make_unique<HighLumiGraphicsPipeline>();
	pipelineMap_[PipelineType::BLUR] = std::make_unique<BlurGraphicsPipeline>();
	pipelineMap_[PipelineType::GAUSSIAN_BLUR] = std::make_unique<GaussianBlurGraphicsPipeline>();
	pipelineMap_[PipelineType::SCAN_NOISE] = std::make_unique<ScanNoiseGraphicsPipeline>();

	pipelineMap_[PipelineType::SPRITE]->PreDraw();
}

void GraphicsPipelineManager::PreDraw()
{
	currentPiplineType_ = PipelineType::SPRITE;

	pipelineMap_[currentPiplineType_]->PreDraw();
}

void GraphicsPipelineManager::PreDraw(PipelineType type)
{
	if (currentPiplineType_ != type) {
		currentPiplineType_ = type;

		pipelineMap_[type]->PreDraw();
	}
}

void GraphicsPipelineManager::SetBlendMode(PipelineType type, uint32_t blendMode)
{
	pipelineMap_[type]->SetBlendMode(blendMode);
}