#include "PostEffect.h"

PostEffect::PostEffect()
{
	piplineType_ = GraphicsPiplineManager::PiplineType::SPRITE;

	CreatePostEffect();
}