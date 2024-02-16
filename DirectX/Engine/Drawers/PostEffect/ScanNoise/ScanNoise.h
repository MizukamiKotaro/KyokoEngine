#pragma once
#include "BasePostEffect/BasePostEffect.h"

class ScanNoise : public BasePostEffect
{
public:
	ScanNoise();

	~ScanNoise() override;

	struct ScanNoiseData {
		float minY; 
		float width;
		float power;
		int32_t isNormal;
	};

	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	void Draw(BlendMode blendMode = BlendMode::kBlendModeNormal) override;
private:
	void CreateScanNoiseRes();
	void CreateResources() override;

private:
	ComPtr<ID3D12Resource> scanNoiseResource_;

	Vector4 color_;
public:
	ScanNoiseData* scanNoiseData_;

};