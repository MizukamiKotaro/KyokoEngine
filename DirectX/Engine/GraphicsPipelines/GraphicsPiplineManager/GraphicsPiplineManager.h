#pragma once
#include <memory>

class GraphicsPipeline;
enum class PipelineType;

class GraphicsPipelineManager
{
public:

	static GraphicsPipelineManager* GetInstance();

	void Initialize();

	void PreDraw();

	void PreDraw(PipelineType type);

	void SetBlendMode(PipelineType type, uint32_t blendMode);

private:
	GraphicsPipelineManager() = default;
	~GraphicsPipelineManager() = default;
	GraphicsPipelineManager(const GraphicsPipelineManager&) = delete;
	GraphicsPipelineManager& operator=(const GraphicsPipelineManager&) = delete;

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

	PipelineType currentPiplineType_;
};