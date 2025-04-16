#include "Contrast.h"

#include "Engine/Base/DirectXBase/DirectXBase.h"
#include "Engine/Base/DescriptorHeapManager/DescriptorHeapManager.h"
#include "Camera.h"
#include "GraphicsPipelineSystem/PipelineTypeConfig.h"
#include "DescriptorHeapManager/DescriptorHandles/DescriptorHandles.h"
#include "GraphicsPipelineSystem/GraphicsPiplineManager/GraphicsPiplineManager.h"
#include "ResourceManager/ResourceManager.h"

Contrast::Contrast()
{
	piplineType_ = PipelineType::CONTRAST;

	contrastData_ = nullptr;

	CreatePostEffect();
}

Contrast::~Contrast()
{
	ResourceManager::GetInstance()->AddReleaseResource(std::move(contrastResource_));
}

void Contrast::Draw(BlendMode blendMode)
{

	PreDraw();

	psoManager_->SetBlendMode(piplineType_, blendMode);

	//Spriteの描画。変更に必要なものだけ変更する
	//マテリアルCBufferの場所を設定
	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());

	commandList_->SetGraphicsRootDescriptorTable(1, srvHandles_->gpuHandle);

	commandList_->SetGraphicsRootConstantBufferView(2, contrastResource_->GetGPUVirtualAddress());

	//描画!!!!（DrawCall/ドローコール）
	commandList_->DrawInstanced(3, 1, 0, 0);

}

void Contrast::CreateContrastRes()
{
	contrastResource_ = DirectXBase::CreateBufferResource(sizeof(ContrastData));

	contrastResource_->Map(0, nullptr, reinterpret_cast<void**>(&contrastData_));

	contrastData_->brightness_ = 0.2f;

	contrastData_->contrast_ = 3.0f;
}

void Contrast::CreateResources()
{
	BasePostEffect::CreateResources();

	CreateContrastRes();
}

