#pragma once
#include "BasePostEffect/BasePostEffect.h"

class Mosaic : public BasePostEffect
{
public:
	Mosaic();

	~Mosaic() override;

	struct MosaicData {
		float density;
		int isSquare;
		Vector2 screenSize;
		int isNormal;
	};

	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	void Draw(BlendMode blendMode = BlendMode::kBlendModeNormal) override;
private:
	void CreateMosaicRes();
	void CreateResources() override;

private:
	ComPtr<ID3D12Resource> mosaicResource_;

public:
	MosaicData* mosaicData_;

};