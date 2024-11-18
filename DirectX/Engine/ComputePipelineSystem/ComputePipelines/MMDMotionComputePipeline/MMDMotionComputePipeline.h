#pragma once
#include "ComputePipelineSystem/ComputePipeline/ComputePipeline.h"

class MMDMotionComputePipeline : public ComputePipeline
{
public:
	MMDMotionComputePipeline();
private:
	void InitializePSO() override;
};