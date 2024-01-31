#pragma once

#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

// スプライト共通部分
class ModelGraphicsPipline : public GraphicsPipeline
{
public:

	static ModelGraphicsPipline* GetInstance();

private:
	ModelGraphicsPipline() = default;
	~ModelGraphicsPipline() = default;
	ModelGraphicsPipline(const ModelGraphicsPipline&) = delete;
	ModelGraphicsPipline& operator=(const ModelGraphicsPipline&) = delete;

	void InitializePSO() override;

};

