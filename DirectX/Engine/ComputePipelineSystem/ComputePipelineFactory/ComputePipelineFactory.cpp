#include "ComputePipelineFactory.h"
#include "ComputePipelineSystem/ComputePipelineTypeConfig.h"
#include "ComputePipelineSystem/ComputePipelines/SkinningComputePipeline/SkinningComputePipeline.h"

ComputePipeline* ComputePipelineFactory::CreateComputePipeline(ComputePipelineType pipelineType)
{
	ComputePipeline* pipeline = nullptr;
	switch (pipelineType)
	{
	case ComputePipelineType::SKINNING:
		pipeline = new SkinningComputePipeline();
		break;
	default:
		break;
	}
	return pipeline;
}
