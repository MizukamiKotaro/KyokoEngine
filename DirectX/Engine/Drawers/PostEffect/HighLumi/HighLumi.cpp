#include "HighLumi.h"

#include "Engine/Base/DirectXBase/DirectXBase.h"
#include "Engine/Base/DescriptorHeapManager/DescriptorHeapManager.h"
#include "Camera.h"
#include "GraphicsPipelineSystem/PipelineTypeConfig.h"
#include "DescriptorHeapManager/DescriptorHandles/DescriptorHandles.h"
#include "GraphicsPipelineSystem/GraphicsPiplineManager/GraphicsPiplineManager.h"
#include "ResourceManager/ResourceManager.h"

HighLumi::HighLumi(const Vector2& size, bool isRender, bool isDepth)
{
	piplineType_ = PipelineType::HIGH_LUMI;
	CreatePostEffect(isRender, isDepth, size);
}

HighLumi::~HighLumi()
{
	ResourceManager::GetInstance()->AddResource(std::move(highLumiResource_));
}

void HighLumi::Draw(BlendMode blendMode)
{
	PreDraw();

	psoManager_->SetBlendMode(piplineType_, blendMode);

	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());
	commandList_->SetGraphicsRootDescriptorTable(1, srvHandles_->gpuHandle);
	commandList_->SetGraphicsRootConstantBufferView(2, highLumiResource_->GetGPUVirtualAddress());

	//描画!!!!（DrawCall/ドローコール）
	commandList_->DrawInstanced(3, 1, 0, 0);
}

void HighLumi::CreateHighLumiRes()
{
	highLumiResource_ = DirectXBase::CreateBufferResource(sizeof(HighLumiData));

	highLumiResource_->Map(0, nullptr, reinterpret_cast<void**>(&highLumiData_));

	highLumiData_->min = 0.6f;

	highLumiData_->max = 0.9f;

	highLumiData_->isToWhite = 0;
}

void HighLumi::CreateResources()
{
	BasePostEffect::CreateResources();

	CreateHighLumiRes();
}

