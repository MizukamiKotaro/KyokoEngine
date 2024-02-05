#pragma once
#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"
#include <memory>

enum class BlendMode
{
	kBlendModeNone, // ブレンドなし
	kBlendModeNormal, // デフォルト
	kBlendModeAdd, // 加算
	kBlendModeSubtract, // 減算
	kBlendModeMultiply, // 乗算
	kBlendModeScreen, // スクリーン
};

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

	void Initialize();

	void PreDraw();

	void PreDraw(PiplineType type);

	void SetBlendMode(PiplineType type, uint32_t blendMode);

private:
	GraphicsPiplineManager() = default;
	~GraphicsPiplineManager() = default;
	GraphicsPiplineManager(const GraphicsPiplineManager&) = delete;
	GraphicsPiplineManager& operator=(const GraphicsPiplineManager&) = delete;

private:
	std::unique_ptr<GraphicsPipeline> spritePSO_;
	std::unique_ptr<GraphicsPipeline> modelPSO_;
	std::unique_ptr<GraphicsPipeline> particlePSO_;
	std::unique_ptr<GraphicsPipeline> pointLightPSO_;
	std::unique_ptr<GraphicsPipeline> spotLightPSO_;
	std::unique_ptr<GraphicsPipeline> contrastPSO_;
	std::unique_ptr<GraphicsPipeline> highLumiPSO_;
	std::unique_ptr<GraphicsPipeline> blurPSO_;
	std::unique_ptr<GraphicsPipeline> gaussianBlurPSO_;

	PiplineType currentPiplineType_ = PiplineType::SPRITE;
};

