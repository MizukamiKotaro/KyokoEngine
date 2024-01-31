#pragma once

#include "GraphicsPipelines/GraphicsPipeline/GraphicsPipeline.h"

// スプライト共通部分
class PointLightGraphicsPipline : public GraphicsPipeline
{
public:

	static PointLightGraphicsPipline* GetInstance();

private:
	PointLightGraphicsPipline() = default;
	~PointLightGraphicsPipline() = default;
	PointLightGraphicsPipline(const PointLightGraphicsPipline&) = delete;
	PointLightGraphicsPipline& operator=(const PointLightGraphicsPipline&) = delete;

	void InitializePSO() override;

};

