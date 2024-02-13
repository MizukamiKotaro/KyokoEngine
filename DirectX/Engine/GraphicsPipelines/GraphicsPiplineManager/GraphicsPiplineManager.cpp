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

#include "GraphicsPipelines/PipelineTypeConfig.h"

GraphicsPipelineManager* GraphicsPipelineManager::GetInstance()
{
	static GraphicsPipelineManager instance;
	return &instance;
}

void GraphicsPipelineManager::Initialize()
{
	currentPiplineType_ = PipelineType::SPRITE;

	spritePSO_ = std::make_unique<SpriteGraphicsPipeline>();

	modelPSO_ = std::make_unique<ModelGraphicsPipline>();

	particlePSO_ = std::make_unique<ParticleGraphicsPipeline>();

	pointLightPSO_ = std::make_unique<PointLightGraphicsPipline>();

	spotLightPSO_ = std::make_unique<SpotLightGraphicsPipline>();

	contrastPSO_ = std::make_unique<ContrastGraphicsPipeline>();

	highLumiPSO_ = std::make_unique<HighLumiGraphicsPipeline>();

	blurPSO_ = std::make_unique<BlurGraphicsPipeline>();

	gaussianBlurPSO_ = std::make_unique<GaussianBlurGraphicsPipeline>();

	spritePSO_->PreDraw();
}

void GraphicsPipelineManager::PreDraw()
{
	currentPiplineType_ = PipelineType::SPRITE;

	spritePSO_->PreDraw();
}

void GraphicsPipelineManager::PreDraw(PipelineType type)
{
	if (currentPiplineType_ != type) {
		currentPiplineType_ = type;

		switch (type)
		{
		case PipelineType::SPRITE:
			spritePSO_->PreDraw();
			break;
		case PipelineType::MODEL:
			modelPSO_->PreDraw();
			break;
		case PipelineType::PARTICLE:
			particlePSO_->PreDraw();
			break;
		case PipelineType::POINT_LIGHT:
			pointLightPSO_->PreDraw();
			break;
		case PipelineType::SPOT_LIGHT:
			spotLightPSO_->PreDraw();
			break;
		case PipelineType::CONTRAST:
			contrastPSO_->PreDraw();
			break;
		case PipelineType::HIGH_LUMI:
			highLumiPSO_->PreDraw();
			break;
		case PipelineType::BLUR:
			blurPSO_->PreDraw();
			break;
		case PipelineType::GAUSSIAN_BLUR:
			gaussianBlurPSO_->PreDraw();
			break;
		case PipelineType::COUNT_PIPLINE_TYPE:
			break;
		default:
			break;
		}
	}
}

void GraphicsPipelineManager::SetBlendMode(PipelineType type, uint32_t blendMode)
{
	switch (type)
	{
	case PipelineType::SPRITE:
		spritePSO_->SetBlendMode(blendMode);
		break;
	case PipelineType::MODEL:
		modelPSO_->SetBlendMode(blendMode);
		break;
	case PipelineType::PARTICLE:
		particlePSO_->SetBlendMode(blendMode);
		break;
	case PipelineType::POINT_LIGHT:
		pointLightPSO_->SetBlendMode(blendMode);
		break;
	case PipelineType::SPOT_LIGHT:
		spotLightPSO_->SetBlendMode(blendMode);
		break;
	case PipelineType::CONTRAST:
		contrastPSO_->SetBlendMode(blendMode);
		break;
	case PipelineType::HIGH_LUMI:
		highLumiPSO_->SetBlendMode(blendMode);
		break;
	case PipelineType::BLUR:
		blurPSO_->SetBlendMode(blendMode);
		break;
	case PipelineType::GAUSSIAN_BLUR:
		gaussianBlurPSO_->SetBlendMode(blendMode);
		break;
	case PipelineType::COUNT_PIPLINE_TYPE:
		break;
	default:
		break;
	}
}

