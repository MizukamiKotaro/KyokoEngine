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

GraphicsPiplineManager* GraphicsPiplineManager::GetInstance()
{
	static GraphicsPiplineManager instance;
	return &instance;
}

void GraphicsPiplineManager::Initialize()
{
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

void GraphicsPiplineManager::PreDraw()
{
	currentPiplineType_ = PiplineType::SPRITE;

	spritePSO_->PreDraw();
}

void GraphicsPiplineManager::PreDraw(PiplineType type)
{
	if (currentPiplineType_ != type) {
		currentPiplineType_ = type;

		switch (type)
		{
		case GraphicsPiplineManager::PiplineType::SPRITE:
			spritePSO_->PreDraw();
			break;
		case GraphicsPiplineManager::PiplineType::MODEL:
			modelPSO_->PreDraw();
			break;
		case GraphicsPiplineManager::PiplineType::PARTICLE:
			particlePSO_->PreDraw();
			break;
		case GraphicsPiplineManager::PiplineType::POINT_LIGHT:
			pointLightPSO_->PreDraw();
			break;
		case GraphicsPiplineManager::PiplineType::SPOT_LIGHT:
			spotLightPSO_->PreDraw();
			break;
		case GraphicsPiplineManager::PiplineType::CONTRAST:
			contrastPSO_->PreDraw();
			break;
		case GraphicsPiplineManager::PiplineType::HIGH_LUMI:
			highLumiPSO_->PreDraw();
			break;
		case GraphicsPiplineManager::PiplineType::BLUR:
			blurPSO_->PreDraw();
			break;
		case GraphicsPiplineManager::PiplineType::GAUSSIAN_BLUR:
			gaussianBlurPSO_->PreDraw();
			break;
		case GraphicsPiplineManager::PiplineType::COUNT_PIPLINE_TYPE:
			break;
		default:
			break;
		}
	}
}

void GraphicsPiplineManager::SetBlendMode(PiplineType type, uint32_t blendMode)
{
	switch (type)
	{
	case GraphicsPiplineManager::PiplineType::SPRITE:
		spritePSO_->SetBlendMode(blendMode);
		break;
	case GraphicsPiplineManager::PiplineType::MODEL:
		modelPSO_->SetBlendMode(blendMode);
		break;
	case GraphicsPiplineManager::PiplineType::PARTICLE:
		particlePSO_->SetBlendMode(blendMode);
		break;
	case GraphicsPiplineManager::PiplineType::POINT_LIGHT:
		pointLightPSO_->SetBlendMode(blendMode);
		break;
	case GraphicsPiplineManager::PiplineType::SPOT_LIGHT:
		spotLightPSO_->SetBlendMode(blendMode);
		break;
	case GraphicsPiplineManager::PiplineType::CONTRAST:
		contrastPSO_->SetBlendMode(blendMode);
		break;
	case GraphicsPiplineManager::PiplineType::HIGH_LUMI:
		highLumiPSO_->SetBlendMode(blendMode);
		break;
	case GraphicsPiplineManager::PiplineType::BLUR:
		blurPSO_->SetBlendMode(blendMode);
		break;
	case GraphicsPiplineManager::PiplineType::GAUSSIAN_BLUR:
		gaussianBlurPSO_->SetBlendMode(blendMode);
		break;
	case GraphicsPiplineManager::PiplineType::COUNT_PIPLINE_TYPE:
		break;
	default:
		break;
	}
}

