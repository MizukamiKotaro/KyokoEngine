#pragma once

#include "PostEffect/PostEffect.h"

// スプライト
class Contrast : public PostEffect
{
public:

	Contrast();

	~Contrast() override;

	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	void Draw(BlendMode blendMode = BlendMode::kBlendModeNormal) override;

private:

	struct ContrastData {
		float brightness_;
		float contrast_;
	};

	void CreateContrastRes();

private:

	ComPtr<ID3D12Resource> contrastResource_;
	
public:
	ContrastData* contrastData_;

};

