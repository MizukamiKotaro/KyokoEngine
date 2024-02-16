#pragma once
#include <memory>
#include <unordered_map>

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
	std::unordered_map<PipelineType, std::unique_ptr<GraphicsPipeline>> pipelineMap_;

	PipelineType currentPiplineType_;
};