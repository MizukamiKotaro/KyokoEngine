#include "PostEffect.h"
#include "GraphicsPipelineSystem/PipelineTypeConfig.h"

PostEffect::PostEffect(const Vector2& size, bool isRender, bool isDepth)
{
	piplineType_ = PipelineType::COPY;
	CreatePostEffect(isRender, isDepth, size);
}
