#include "GaussianBlur.h"

#include "Engine/Base/DirectXBase/DirectXBase.h"
#include "Engine/Base/Descriptor/DescriptorHeapManager/DescriptorHeapManager.h"
#include "Camera.h"
#include "GraphicsPipelineSystem/PipelineTypeConfig.h"
#include "Descriptor/DescriptorHandles/DescriptorHandles.h"
#include "GraphicsPipelineSystem/GraphicsPiplineManager/GraphicsPiplineManager.h"

Gaussian::Gaussian(const bool& isRender, const bool& isDepth, const Vector2& size)
{
	piplineType_ = PipelineType::GAUSSIAN_BLUR;

	gaussianBlurData_ = nullptr;

	CreatePostEffect(isRender, isDepth, size);
}

Gaussian::~Gaussian()
{
}

void Gaussian::Draw(BlendMode blendMode)
{
	PreDraw();

	psoManager_->SetBlendMode(piplineType_, blendMode);

	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_.GetGPUVirtualAddress());
	commandList_->SetGraphicsRootDescriptorTable(1, srvHandles_->gpuHandle);
	commandList_->SetGraphicsRootConstantBufferView(2, gaussianBlurResource_.GetGPUVirtualAddress());

	//描画!!!!（DrawCall/ドローコール）
	commandList_->DrawInstanced(3, 1, 0, 0);

}

void Gaussian::CreateGaussianBlurRes()
{
	gaussianBlurResource_.CreateResource(sizeof(GaussianBlurData));

	gaussianBlurResource_.Map(reinterpret_cast<void**>(&gaussianBlurData_));

	gaussianBlurData_->width = 9;
	gaussianBlurData_->height = 0;
	gaussianBlurData_->sigma = 2.0f;
}

void Gaussian::CreateResources()
{
	BasePostEffect::CreateResources();

	CreateGaussianBlurRes();
}

GaussianBlur::GaussianBlur(bool isRender, bool isDepth, const Vector2& size)
{
	if (size.x == 0.0f || size.y == 0.0f) {
		gaussian0_ = std::make_unique<Gaussian>(isRender, isDepth);
		gaussian1_ = std::make_unique<Gaussian>(isRender, isDepth);
	}
	else {
		gaussian0_ = std::make_unique<Gaussian>(isRender, isDepth, size);
		gaussian1_ = std::make_unique<Gaussian>(isRender, isDepth, size);
	}
	gaussian1_->gaussianBlurData_->height = 1;
}

void GaussianBlur::Initialize()
{
}

void GaussianBlur::Draw(BlendMode blendMode)
{
	gaussian1_->Draw(blendMode);
}

void GaussianBlur::PreDrawScene()
{
	gaussian0_->PreDrawScene();
}

void GaussianBlur::PostDrawScene()
{
	gaussian0_->PostDrawScene();
	gaussian1_->PreDrawScene();
	gaussian0_->Draw();
	gaussian1_->PostDrawScene();
}

void GaussianBlur::SetSize(int32_t size)
{
	gaussian0_->gaussianBlurData_->width = size;
	gaussian1_->gaussianBlurData_->width = size;
}

void GaussianBlur::SetSigma(float sigma)
{
	gaussian0_->gaussianBlurData_->sigma = sigma;
	gaussian1_->gaussianBlurData_->sigma = sigma;
}
