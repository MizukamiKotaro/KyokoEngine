#pragma once
#include "BasePostEffect/BasePostEffect.h"
/// <summary>
/// ハイルミ
/// </summary>
class HighLumi : public BasePostEffect
{
public:
	HighLumi(const Vector2& size = windowSize_, bool isRender = true, bool isDepth = false);
	~HighLumi() override;
	/// <summary>
	/// 描画処理
	/// </summary>
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
	Kyoko::ResourceManualRelease highLumiResource_;
public:
	HighLumiData* highLumiData_;
};