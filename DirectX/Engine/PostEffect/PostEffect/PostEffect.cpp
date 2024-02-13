#include "PostEffect.h"

PostEffect::PostEffect()
{
	piplineType_ = PipelineType::SPRITE;

	CreatePostEffect();
}