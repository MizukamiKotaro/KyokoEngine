#pragma once
#include "BasePostEffect/BasePostEffect.h"

class Contrast : public BasePostEffect
{
public:

	Contrast();

	~Contrast() override;

	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	void Draw(BlendMode blendMode = BlendMode::kBlendModeNormal) override;

	struct ContrastData {
		float brightness_;
		float contrast_;
	};
private:


private:
	void CreateContrastRes();
	void CreateResources() override;
private:
	ComPtr<ID3D12Resource> contrastResource_;
public:
	ContrastData* contrastData_;
};