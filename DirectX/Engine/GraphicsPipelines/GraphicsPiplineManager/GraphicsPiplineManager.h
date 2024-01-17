#pragma once

#include <wrl.h>
#include <dxcapi.h>
#pragma comment(lib, "dxcompiler.lib")
#include <string>
#include <d3d12.h>
#include <array>
#include "GraphicsPipelines/ModelGraphicsPipline/ModelGraphicsPipline.h"
#include "GraphicsPipelines/ParticleGraphicsPipeline/ParticleGraphicsPipeline.h"
#include "GraphicsPipelines/SpriteGraphicsPipeline/SpriteGraphicsPipeline.h"
#include "GraphicsPipelines/PointLightGraphicsPipline/PointLightGraphicsPipline.h"
#include "GraphicsPipelines/SpotLightGraphicsPipline/SpotLightGraphicsPipline.h"
#include "GraphicsPipelines/ContrastGraphicsPipeline/ContrastGraphicsPipeline.h"
#include "GraphicsPipelines/HighLumiGraphicsPipeline/HighLumiGraphicsPipeline.h"
#include "GraphicsPipelines/BlurGraphicsPipeline/BlurGraphicsPipeline.h"
#include "GraphicsPipelines/GaussianBlurGraphicsPipeline/GaussianBlurGraphicsPipeline.h"

enum class BlendMode
{
	kBlendModeNone, // ブレンドなし
	kBlendModeNormal, // デフォルト
	kBlendModeAdd, // 加算
	kBlendModeSubtract, // 減算
	kBlendModeMultiply, // 乗算
	kBlendModeScreen, // スクリーン
};

// スプライト共通部分
class GraphicsPiplineManager
{
public:

	enum class PiplineType {
		SPRITE,
		MODEL,
		PARTICLE,
		POINT_LIGHT,
		SPOT_LIGHT,
		CONTRAST,
		HIGH_LUMI,
		BLUR,
		GAUSSIAN_BLUR,
		COUNT_PIPLINE_TYPE,
	};

	static GraphicsPiplineManager* GetInstance();

	// namespace省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

	void Init();

	void PreDraw();

	void PreDraw(PiplineType type);

	void SetBlendMode(PiplineType type, uint32_t blendMode);

private:

private:
	GraphicsPiplineManager() = default;
	~GraphicsPiplineManager() = default;
	GraphicsPiplineManager(const GraphicsPiplineManager&) = delete;
	GraphicsPiplineManager& operator=(const GraphicsPiplineManager&) = delete;

private:

	SpriteGraphicsPipeline* spritePSO_ = nullptr;
	ModelGraphicsPipline* modelPSO_ = nullptr;
	ParticleGraphicsPipeline* particlePSO_ = nullptr;
	PointLightGraphicsPipline* pointLightPSO_ = nullptr;
	SpotLightGraphicsPipline* spotLightPSO_ = nullptr;
	ContrastGraphicsPipeline* contrastPSO_ = nullptr;
	HighLumiGraphicsPipeline* highLumiPSO_ = nullptr;
	BlurGraphicsPipeline* blurPSO_ = nullptr;
	GaussianBlurGraphicsPipeline* gaussianBlurPSO_ = nullptr;

	PiplineType currentPiplineType_ = PiplineType::SPRITE;

};

