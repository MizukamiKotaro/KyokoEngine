#include "Noise.h"

#include "Engine/Base/DirectXBase/DirectXBase.h"
#include "Engine/Base/Descriptor/DescriptorHeapManager/DescriptorHeapManager.h"
#include "Camera.h"
#include "GraphicsPipelineSystem/PipelineTypeConfig.h"
#include "Descriptor/DescriptorHandles/DescriptorHandles.h"
#include "GraphicsPipelineSystem/GraphicsPiplineManager/GraphicsPiplineManager.h"
#include "WindowsInfo/WindowsInfo.h"

Noise::Noise()
{
	piplineType_ = PipelineType::NOISE;
	noiseData_ = nullptr;
	CreatePostEffect();
	camera = nullptr;
}

Noise::~Noise()
{
}

void Noise::SetCameraPos(const Vector3& pos)
{
	camera = &pos;
	noiseData_->cameraPos = Vector2{ camera->x,camera->y };
}

void Noise::Initialize()
{
	noiseData_->time = 0.0f;
	if (camera) {
		noiseData_->cameraPos = Vector2{ camera->x,camera->y };
	}
}

void Noise::Update(float time)
{
	noiseData_->time += time;
	if (camera) {
		noiseData_->cameraPos = Vector2{ camera->x,camera->y };
	}
}

void Noise::Draw(BlendMode blendMode)
{
	if (noiseData_->density <= 0.0f) {
		noiseData_->density = 0.1f;
	}

	if (noiseData_->moveScale <= 0.0f) {
		noiseData_->moveScale = 0.1f;
	}

	if (blendMode == BlendMode::kBlendModeNormal) {
		noiseData_->isNormal = 1;
	}
	else {
		noiseData_->isNormal = 0;
	}

	materialData_->color = color_;

	PreDraw();

	psoManager_->SetBlendMode(piplineType_, blendMode);

	commandList_->SetGraphicsRootConstantBufferView(0, materialResource_.GetGPUVirtualAddress());
	commandList_->SetGraphicsRootDescriptorTable(1, srvHandles_->gpuHandle);
	commandList_->SetGraphicsRootConstantBufferView(2, noiseResource_.GetGPUVirtualAddress());

	//描画!!!!（DrawCall/ドローコール）
	commandList_->DrawInstanced(3, 1, 0, 0);

}

void Noise::CreateNoiseRes()
{
	noiseResource_.CreateResource(sizeof(NoiseData));

	noiseResource_.Map(reinterpret_cast<void**>(&noiseData_));

	noiseData_->density = 10.0f;
	noiseData_->screenSize = WindowsInfo::GetInstance()->GetWindowSize();
	noiseData_->time = 0.0f;
	noiseData_->lightningColor = { 0.8f,0.8f,0.8f,1.0f };
	noiseData_->waterColor = { 0.3f,1.0f,0.8f,1.0f };
	noiseData_->type = NoiseType::WATER;
	noiseData_->isNormal = 1;
	noiseData_->cameraPos = {};
	noiseData_->moveScale = 2.0f;
}

void Noise::CreateResources()
{
	BasePostEffect::CreateResources();

	CreateNoiseRes();
}
