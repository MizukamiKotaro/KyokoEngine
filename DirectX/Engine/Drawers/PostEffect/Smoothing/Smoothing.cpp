#include "Smoothing.h"
#include "Engine/Base/DirectXBase/DirectXBase.h"
#include "Engine/Base/Descriptor/DescriptorHeapManager/DescriptorHeapManager.h"
#include "Camera.h"
#include "GraphicsPipelineSystem/PipelineTypeConfig.h"
#include "Descriptor/DescriptorHandles/DescriptorHandles.h"
#include "GraphicsPipelineSystem/GraphicsPiplineManager/GraphicsPiplineManager.h"

Smoothing::Smoothing()
{
	piplineType_ = PipelineType::SMOOTHING;
	smoothingData_ = nullptr;
	CreatePostEffect();
}

Smoothing::~Smoothing()
{
}

void Smoothing::Draw(BlendMode blendMode)
{
	materialData_->color = color_;
	PreDraw();
	psoManager_->SetBlendMode(piplineType_, blendMode);
	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_.GetGPUVirtualAddress());
	commandList_->SetGraphicsRootDescriptorTable(1, srvHandles_->gpuHandle);
	commandList_->SetGraphicsRootConstantBufferView(2, smoothingResource_.GetGPUVirtualAddress());
	commandList_->DrawInstanced(3, 1, 0, 0);
}

void Smoothing::CreateSmoothingRes()
{
	smoothingResource_.CreateResource(sizeof(SmoothingData));
	smoothingResource_.Map(reinterpret_cast<void**>(&smoothingData_));
	smoothingData_->height = 9;
	smoothingData_->width = 9;
}

void Smoothing::CreateResources()
{
	BasePostEffect::CreateResources();
	CreateSmoothingRes();
}
