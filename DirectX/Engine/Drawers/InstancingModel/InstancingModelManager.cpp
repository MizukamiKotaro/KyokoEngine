#include "InstancingModelManager.h"
#include <cassert>
#include "TextureManager/TextureManager.h"
#include "Engine/Base/DescriptorHeapManager/DescriptorHeapManager.h"
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

void InstancingModelManager::Draw(const Camera& camera, const InstancingMeshTexData* modelData)
{
	InstancingModels::PreDraw();

	for (const auto& [model, particleList] : instancingModelMap_) {
		if (particleList->GetSize() == 0) { continue; }
		particleList->Draw(camera, modelData);
	}
}

void InstancingModelManager::Draw(const Camera& camera, const std::string& tag)
{
	InstancingModels::PreDraw();

	for (const auto& [model, particleList] : instancingModelMap_) {
		if (particleList->GetSize() == 0) { continue; }
		particleList->Draw(camera, tag);
	}
}

const InstancingMeshTexData* InstancingModelManager::GetDrawData(const InstancingMeshTexData& data)
{
	for (const std::unique_ptr<InstancingMeshTexData>& dataPtr : drawDatas_) {
		if (dataPtr->modelData_ == data.modelData_ && dataPtr->texture_ == data.texture_ && dataPtr->blendMode_ == data.blendMode_ && dataPtr->tag_ == data.tag_) {
			return dataPtr.get();
		}
	}
	drawDatas_.push_back(std::make_unique<InstancingMeshTexData>(data));
	return drawDatas_.back().get();
}

const InstancingMeshTexData* InstancingModelManager::GetDrawData(const std::string& texturePath, const std::string& tag, const BlendMode& blendMode)
{
	const Texture* texture = textureManager_->LoadTexture(texturePath);

	for (const std::unique_ptr<InstancingMeshTexData>& dataPtr : drawDatas_) {
		if (dataPtr->modelData_ == plane_ && dataPtr->texture_ == texture && dataPtr->blendMode_ == blendMode && dataPtr->tag_ == tag) {
			return dataPtr.get();
		}
	}
	drawDatas_.push_back(std::make_unique<InstancingMeshTexData>(InstancingMeshTexData{ tag,plane_,texture,blendMode }));
	return drawDatas_.back().get();
}

InstancingModelData* const InstancingModelManager::AddBox(const InstancingMeshTexData* modelData, InstancingModelData&& model)
{
	if (instancingModelMap_.find(modelData) == instancingModelMap_.end()) {
		instancingModelMap_[modelData] = std::make_unique<InstancingModelList>(modelData);
		instancingModelMap_[modelData]->SetModel(modelData);
	}
	return instancingModelMap_[modelData]->AddModel(std::move(model));
}

void InstancingModelManager::Clear()
{
	for (auto& modelList : instancingModelMap_) {
		modelList.second->Clear();
	}
	InstancingResourceManager::GetInstance()->Clear();
}

void InstancingModelManager::SetLight(const InstancingMeshTexData* modelData, const ILight* light)
{
	instancingModelMap_[modelData]->SetLight(light);
}
