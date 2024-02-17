#pragma once
#include "BasePostEffect/BasePostEffect.h"

class NegaPosiInverse : public BasePostEffect
{
public:
	NegaPosiInverse();

	~NegaPosiInverse() override;

	struct NegaPosiInverseData {
		int isNormal;
	};

	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	void Draw(BlendMode blendMode = BlendMode::kBlendModeNormal) override;
private:
	void CreateNegaPosiInverseRes();
	void CreateResources() override;

private:
	ComPtr<ID3D12Resource> negaPosiInverseResource_;
public:
	NegaPosiInverseData* negaPosiInverseData_;

};