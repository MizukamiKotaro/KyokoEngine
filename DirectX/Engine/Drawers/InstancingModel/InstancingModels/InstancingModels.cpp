#include "InstancingModels.h"
#include "DirectXBase/DirectXBase.h"
#include "Camera.h"
#include <algorithm>
#include "Light/Light.h"
#include "GraphicsPipelineSystem/GraphicsPiplineManager/GraphicsPiplineManager.h"
#include "DescriptorHeapManager/DescriptorHeapManager.h"
#include "DescriptorHeapManager/DescriptorHeap/DescriptorHeap.h"

#include "GraphicsPipelineSystem/PipelineTypeConfig.h"
#include "ILight/ILight.h"
#include "InstancingResourceManager.h"

const PipelineType InstancingModels::pipelineType_ = PipelineType::INSTANCING_MODEL;

InstancingModels::InstancingModels(const InstancingGroupData* modelData)
{
	modelData_ = modelData;

	resourceManager_ = InstancingResourceManager::GetInstance();
	resourceManager_->AddResource(modelData_);

	light_.Initialize();
}

InstancingModels::~InstancingModels()
{
}

void InstancingModels::Draw(const Camera& camera, std::list<InstancingModelData>& blocks, const InstancingGroupData* modelData)
{
	if (modelData_ != modelData) {
		return;
	}
	Draw(camera, blocks);
}

void InstancingModels::Draw(const Camera& camera, std::list<InstancingModelData>& blocks, const std::string& tag)
{
	if (modelData_->tag_ != tag) {
		return;
	}
	Draw(camera, blocks);
}

void InstancingModels::PreDraw()
{
	psoManager_->PreDraw(pipelineType_);
}

void InstancingModels::SetMesh(const InstancingGroupData* modelData)
{
	modelData_ = modelData;
}

void InstancingModels::SetLight(const ILight* light)
{
	light_.SetLight(light);
}

void InstancingModels::Draw(const Camera& camera, std::list<InstancingModelData>& blocks)
{
	PreDraw();

	uint32_t instaceNum = static_cast<uint32_t>(blocks.size());
	instaceNum = std::clamp<uint32_t>(instaceNum, 0, kNumInstance);
	uint32_t index = 0;

	InstancingResourceManager::Resources* resource = resourceManager_->GetResources(modelData_);

	if (int32_t(resource->instancingResources_.size()) <= resource->instancingNum_) {
		resourceManager_->CreateSRV(1, modelData_);
	}

	for (std::list<InstancingModelData>::iterator iter = blocks.begin(); iter != blocks.end(); iter++) {
		if (index >= kNumInstance) {
			break;
		}

		resource->instancingResources_[resource->instancingNum_].instancingData_[index].World = iter->matrix_;
		resource->instancingResources_[resource->instancingNum_].instancingData_[index].WVP = resource->instancingResources_[resource->instancingNum_].instancingData_[index].World * camera.GetViewProjection();
		resource->instancingResources_[resource->instancingNum_].instancingData_[index].uvMatrix = iter->uvMatrix_;
		resource->instancingResources_[resource->instancingNum_].instancingData_[index].color = iter->color_;

		index++;
	}
	psoManager_->SetBlendMode(pipelineType_, modelData_->blendMode_);
	//Spriteの描画。変更に必要なものだけ変更する
	commandList_->IASetVertexBuffers(0, 1, &modelData_->modelData_->mesh.vertexBufferView_); // VBVを設定
	commandList_->IASetIndexBuffer(&modelData_->modelData_->mesh.indexBufferView_);
	//マテリアルCBufferの場所を設定
	commandList_->SetGraphicsRootConstantBufferView(0, resource->materialResource_->GetGPUVirtualAddress());
	//TransformationMatrixCBufferの場所を設定
	//commandList->SetGraphicsRootConstantBufferView(1, instancingResource_->GetGPUVirtualAddress());
	commandList_->SetGraphicsRootDescriptorTable(1, resource->instancingResources_[resource->instancingNum_].srvHandles_->gpuHandle);
	//平行光源CBufferの場所を設定
	commandList_->SetGraphicsRootConstantBufferView(3, light_.GetDirectionalLightGPUVirtualAddress());
	commandList_->SetGraphicsRootDescriptorTable(2, modelData_->texture_->handles_->gpuHandle);
	//描画!!!!（DrawCall/ドローコール）
	//commandList_->DrawInstanced(UINT(modelData_->modelData_->mesh.verteces.size()), instaceNum, 0, 0);
	commandList_->DrawIndexedInstanced(UINT(modelData_->modelData_->mesh.indices.size()), instaceNum, 0, 0, 0);

	resource->instancingNum_++;
}
