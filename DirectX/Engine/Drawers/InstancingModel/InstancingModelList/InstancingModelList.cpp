#include "InstancingModelList.h"
#include <cassert>
#include "TextureManager/TextureManager.h"
#include "Engine/Base/DescriptorHeapManager/DescriptorHeapManager.h"
#include "Utils/RandomGenerator/RandomGenerator.h"
#include "DirectXBase/DirectXBase.h"
#include "Camera.h"
#include <numbers>
#include <algorithm>
#include "TextureManager.h"
#include "Light/Light.h"
#include "ModelDataManager.h"

InstancingModelList::InstancingModelList(const InstancingGroupData* modelData)
{
	modelsResource_ = std::make_unique<Instance>(modelData);
}

void InstancingModelList::SetLight(const BaseLight* light) {
	modelsResource_->SetLight(light);
}

void InstancingModelList::Draw(const Camera& camera, const InstancingGroupData* modelData)
{
	modelsResource_->Draw(camera, modelList_, modelData);
}

void InstancingModelList::Draw(const Camera& camera, const std::string& tag)
{
	modelsResource_->Draw(camera, modelList_, tag);
}

void InstancingModelList::Clear()
{
	modelList_.clear();
}

void InstancingModelList::AddInstanceTransform(InstancingModelData&& instancingModel)
{
	modelList_.push_back(std::move(instancingModel));
}

uint32_t InstancingModelList::GetSize() const
{
	return static_cast<uint32_t>(modelList_.size());
}

void InstancingModelList::SetModel(const InstancingGroupData* modelData)
{
	modelsResource_->SetMesh(modelData);
}
