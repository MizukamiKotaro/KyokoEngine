#include "InstancingModelManager.h"
#include <cassert>
#include "TextureManager/TextureManager.h"
#include "Engine/Base/Descriptor/DescriptorHeapManager/DescriptorHeapManager.h"
#include "Utils/RandomGenerator/RandomGenerator.h"
#include "DirectXBase/DirectXBase.h"
#include "Camera.h"
#include "Light/Light.h"
#include "ModelDataManager.h"
#include "InstancingModels/InstancingResourceManager.h"

InstancingModelManager* InstancingModelManager::GetInstance()
{
	static InstancingModelManager instance;
	return &instance;
}

void InstancingModelManager::FirstInitialize()
{
	plane_ = modelDataManager_->LoadObj("plane");
}

void InstancingModelManager::Draw(const Camera& camera, const InstancingGroupData* modelData)
{
	Instance::PreDraw();
	for (const auto& [model, particleList] : instancingModelMap_) {
		if (particleList->GetSize() == 0) { continue; }
		particleList->Draw(camera, modelData);
	}
}

void InstancingModelManager::Draw(const Camera& camera, const std::string& tag)
{
	Instance::PreDraw();
	for (const auto& [model, particleList] : instancingModelMap_) {
		if (particleList->GetSize() == 0) { continue; }
		particleList->Draw(camera, tag);
	}
}

const InstancingGroupData* InstancingModelManager::GetDrawData(const InstancingGroupData& data)
{
	for (const std::unique_ptr<InstancingGroupData>& dataPtr : drawDatas_) {
		if (dataPtr->modelData_ == data.modelData_ && dataPtr->texture_ == data.texture_ && dataPtr->blendMode_ == data.blendMode_ && dataPtr->tag_ == data.tag_) {
			return dataPtr.get();
		}
	}
	drawDatas_.push_back(std::make_unique<InstancingGroupData>(data));
	return drawDatas_.back().get();
}

const InstancingGroupData* InstancingModelManager::GetDrawData(const std::string& texturePath, const std::string& tag, const BlendMode& blendMode)
{
	const Texture* texture = textureManager_->LoadTexture(texturePath);
	for (const std::unique_ptr<InstancingGroupData>& dataPtr : drawDatas_) {
		if (dataPtr->modelData_ == plane_ && dataPtr->texture_ == texture && dataPtr->blendMode_ == blendMode && dataPtr->tag_ == tag) {
			return dataPtr.get();
		}
	}
	// ないから新しく作成
	drawDatas_.push_back(std::make_unique<InstancingGroupData>(InstancingGroupData{ tag,plane_,texture,blendMode }));
	return drawDatas_.back().get();
}

void InstancingModelManager::AddInstanceTransform(const InstancingGroupData* modelData, InstancingModelData&& model)
{
	if (instancingModelMap_.find(modelData) == instancingModelMap_.end()) {
		// リストがない時に作成
		instancingModelMap_[modelData] = std::make_unique<InstancingModelList>(modelData);
		instancingModelMap_[modelData]->SetModel(modelData);
	}
	instancingModelMap_[modelData]->AddInstanceTransform(std::move(model));
}

void InstancingModelManager::Clear()
{
	for (auto& modelList : instancingModelMap_) {
		modelList.second->Clear();
	}
	InstancingResourceManager::GetInstance()->Clear();
}

void InstancingModelManager::SetLight(const InstancingGroupData* modelData, const BaseLight* light)
{
	instancingModelMap_[modelData]->SetLight(light);
}
