#pragma once
#include "BasePostEffect/BasePostEffect.h"
/// <summary>
/// ポストエフェクト
/// </summary>
class PostEffect : public BasePostEffect
{
public:
	PostEffect(const Vector2& size = windowSize_, bool isRender = true, bool isDepth = false);
};