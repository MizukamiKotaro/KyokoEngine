#pragma once

#include "BasePostEffect/BasePostEffect.h"

// スプライト
class Blur : public BasePostEffect
{
public:

	Blur();

	~Blur() override;

	struct BlurData {
		float angle; // 角度。0だと横ブラー、90だと縦ブラー。
		float pickRange; // 取得する色の幅。
		float stepWidth; // 取得する色の位置変更の幅。0.0f < stepWidth < pickRange
		int32_t isCenterBlur; // 真ん中からブラーか。1=true,0=false;
		int32_t isNormal;
		//float padding[3];

	};

	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	void Draw(BlendMode blendMode = BlendMode::kBlendModeNormal) override;


private:

	void CreateBlurRes();

	void CreateResources() override;

private:

	ComPtr<ID3D12Resource> blurResource_;

public:
	BlurData* blurData_;

	Vector4 color_;

};

