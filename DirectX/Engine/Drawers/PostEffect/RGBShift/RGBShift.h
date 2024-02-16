#pragma once
#include "BasePostEffect/BasePostEffect.h"

class RGBShift : public BasePostEffect
{
public:
	RGBShift();

	~RGBShift() override;

	struct RGBShiftData {
		float shift; 
		int isNormal;
	};

	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	void Draw(BlendMode blendMode = BlendMode::kBlendModeNormal) override;
private:
	void CreateRGBShiftRes();
	void CreateResources() override;

private:
	ComPtr<ID3D12Resource> rgbShiftResource_;

public:
	RGBShiftData* rgbShiftData_;
};