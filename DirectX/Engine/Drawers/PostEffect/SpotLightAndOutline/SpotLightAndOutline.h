#pragma once
#include "MemoDepth/MemoDepth.h"
#include "LightDepth/LightDepth.h"
#include <memory>
#include "Bloom/Bloom.h"

class SpotLightAndOutline
{
public:

	SpotLightAndOutline();

	~SpotLightAndOutline();

	void Initialize();

	void Update();

	void Draw(const Camera& camera);

	void PreDrawLight();
	void PostDrawLight();

	void PreDrawOutline();
	void PostDrawOutline();

	void PreDrawObject();
	void PostDrawObject();

	void PreDrawBloom();
	void PostDrawBloom();

private:
	std::unique_ptr<LightDepth> light_;
	std::unique_ptr<MemoDepth> outline_;
	std::unique_ptr<MemoDepth> object_;
	std::unique_ptr<MemoDepth> bloomMemo_;
	std::unique_ptr<Bloom> bloom_;
	std::unique_ptr<PostEffect> bloomTexture_;
};

