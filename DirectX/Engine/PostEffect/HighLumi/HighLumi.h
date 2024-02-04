#pragma once

#include "BasePostEffect/BasePostEffect.h"

// スプライト
class HighLumi : public BasePostEffect
{
public:

	HighLumi();

	~HighLumi() override;

	void Draw(BlendMode blendMode = BlendMode::kBlendModeNormal) override;

	struct HighLumiData {
		float min;
		float max;
		int isToWhite;
	};

private:
	void CreateHighLumiRes();

	void CreateResources() override;

private:
	ComPtr<ID3D12Resource> highLumiResource_;

public:
	HighLumiData* highLumiData_;

};

