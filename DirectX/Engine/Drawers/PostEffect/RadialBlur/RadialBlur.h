#pragma once
#include "BasePostEffect/BasePostEffect.h"

/// <summary>
/// ラディアルブラー
/// </summary>
class RadialBlur : public BasePostEffect
{
public:
	RadialBlur();
	~RadialBlur() override;
	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(BlendMode blendMode = BlendMode::kBlendModeNormal) override;
	struct RadialBlurData {
		Vector2 center;
		float width;
		int32_t numSamples;
	};
private:
	void CreateRadialBlurRes();
	void CreateResources() override;
private:
	Kyoko::ResourceManualRelease radialBlurResource_;
public:
	RadialBlurData* radialBlurData_;
};