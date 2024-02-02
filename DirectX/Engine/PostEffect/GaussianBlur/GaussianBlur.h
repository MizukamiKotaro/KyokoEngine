#pragma once

#include "BasePostEffect/BasePostEffect.h"

// スプライト
class GaussianBlur : public BasePostEffect
{
public:

	GaussianBlur();

	~GaussianBlur() override;

	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	void Draw(BlendMode blendMode = BlendMode::kBlendModeNormal) override;

private:
	struct GaussianBlurData {
		float pickRange; // 取得する色の幅。
		float stepWidth; // 取得する色の位置変更の幅。0.0f < stepWidth < pickRange
	};

private:

	void CreateGaussianBlurRes();

	void CreateResources() override;

private:

	ComPtr<ID3D12Resource> gaussianBlurResource_;

public:
	GaussianBlurData* gaussianBlurData_;

};

