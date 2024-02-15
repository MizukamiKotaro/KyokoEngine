#include "PostEffect.h"
#include "GraphicsPipelines/PipelineTypeConfig.h"

PostEffect::PostEffect()
{
	piplineType_ = PipelineType::SPRITE;

	CreatePostEffect();
}