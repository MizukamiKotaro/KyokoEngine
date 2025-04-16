#include "Blur.h"

#include "Engine/Base/DirectXBase/DirectXBase.h"
#include "Engine/Base/DescriptorHeapManager/DescriptorHeapManager.h"
#include "Camera.h"
#include "GraphicsPipelineSystem/PipelineTypeConfig.h"
#include "DescriptorHeapManager/DescriptorHandles/DescriptorHandles.h"
#include "GraphicsPipelineSystem/GraphicsPiplineManager/GraphicsPiplineManager.h"
#include "ResourceManager/ResourceManager.h"

Blur::Blur()
{
	piplineType_ = PipelineType::BLUR;
	blurData_ = nullptr;
	CreatePostEffect();
}

Blur::~Blur()
{
	ResourceManager::GetInstance()->AddReleaseResource(std::move(blurResource_));
}

void Blur::Draw(BlendMode blendMode)
{
	if (blurData_->pickRange <= 0.0f) {
		blurData_->pickRange = 0.01f;
	}
	if (blurData_->stepWidth <= 0.0f) {
		blurData_->stepWidth = 0.001f;
	}

	if (blendMode == BlendMode::kBlendModeNormal) {
		blurData_->isNormal = 1;
	}
	else {
		blurData_->isNormal = 0;
	}

	materialData_->color = color_;

	PreDraw();

	psoManager_->SetBlendMode(piplineType_, blendMode);

	//Spriteの描画。変更に必要なものだけ変更する
	//マテリアルCBufferの場所を設定
	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_->GetGPUVirtualAddress());

	commandList_->SetGraphicsRootDescriptorTable(1, srvHandles_->gpuHandle);

	commandList_->SetGraphicsRootConstantBufferView(2, blurResource_->GetGPUVirtualAddress());

	//描画!!!!（DrawCall/ドローコール）
	commandList_->DrawInstanced(3, 1, 0, 0);

}

void Blur::CreateBlurRes()
{
	blurResource_ = DirectXBase::CreateBufferResource(sizeof(BlurData));

	blurResource_->Map(0, nullptr, reinterpret_cast<void**>(&blurData_));

	blurData_->angle = 0.0f;

	blurData_->pickRange = 0.06f;

	blurData_->stepWidth = 0.005f;

	blurData_->isCenterBlur = 1;

	blurData_->isNormal = 1;
}

void Blur::CreateResources()
{
	BasePostEffect::CreateResources();

	CreateBlurRes();
}
