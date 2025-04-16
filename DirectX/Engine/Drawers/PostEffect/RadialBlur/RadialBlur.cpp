#include "RadialBlur.h"

#include "Engine/Base/DirectXBase/DirectXBase.h"
#include "Engine/Base/DescriptorHeapManager/DescriptorHeapManager.h"
#include "Camera.h"
#include "GraphicsPipelineSystem/PipelineTypeConfig.h"
#include "DescriptorHeapManager/DescriptorHandles/DescriptorHandles.h"
#include "GraphicsPipelineSystem/GraphicsPiplineManager/GraphicsPiplineManager.h"

RadialBlur::RadialBlur()
{
	piplineType_ = PipelineType::RADIAL_BLUR;
	radialBlurData_ = nullptr;
	CreatePostEffect();
}

RadialBlur::~RadialBlur()
{
}

void RadialBlur::Draw(BlendMode blendMode)
{
	materialData_->color = color_;

	PreDraw();

	psoManager_->SetBlendMode(piplineType_, blendMode);

	
	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_.GetGPUVirtualAddress());
	commandList_->SetGraphicsRootDescriptorTable(1, srvHandles_->gpuHandle);
	commandList_->SetGraphicsRootConstantBufferView(2, radialBlurResource_.GetGPUVirtualAddress());

	//描画!!!!（DrawCall/ドローコール）
	commandList_->DrawInstanced(3, 1, 0, 0);

}

void RadialBlur::CreateRadialBlurRes()
{
	radialBlurResource_.CreateResource(sizeof(RadialBlurData));
	radialBlurResource_.Map(reinterpret_cast<void**>(&radialBlurData_));
	radialBlurData_->center = { 0.5f,0.5f };
	radialBlurData_->width = -0.05f;
	radialBlurData_->numSamples = 10;
}

void RadialBlur::CreateResources()
{
	BasePostEffect::CreateResources();

	CreateRadialBlurRes();
}
