#include "StageObjectManager.h"
#include "Editor/StageEditor.h"
#include "StageObjectConfig.h"
#include "StageObjectFactory/StageObjectFactory.h"
#include "BaseStageObject.h"

void StageObjectManager::AddType(StageObjectType type, const std::string& mainName, const std::string& subName)
{
	bool is = false;
	// 同じ設定があるか
	for (const std::unique_ptr<StageObjectManager::Type>& aType : types_) {
		if (aType->type == type && aType->mainName == mainName && aType->subName == subName) {
			is = true;
			break;
		}
	}
	if (!is) {
		// 設定の追加
		types_.push_back(std::make_unique<StageObjectManager::Type>(0, 0, type, mainName, subName));
		if (!stageEditor_) {
			stageEditor_ = std::make_unique<StageEditor>();
		}
		stageEditor_->AddItem(mainName + "の数", 0, mainName + "の設置", subName);
		types_.back()->num = stageEditor_->GetIntValue(mainName + "の数", mainName + "の設置", subName);
		CreateObjects();
	}
}

void StageObjectManager::Initialize()
{
	if (!stageEditor_) {
		stageEditor_ = std::make_unique<StageEditor>();
	}
	stageEditor_->Initialize();
	ApplyGlobalVariable();
}

void StageObjectManager::Update(float deltaTime)
{
#ifdef _DEBUG
	if (stageEditor_->IsChangedStage()) {
		Initialize();
	}
	ApplyGlobalVariable();
#endif // _DEBUG
	for (std::unique_ptr<BaseStageObject>& object : objects_) {
		object->Update(deltaTime);
	}
}

void StageObjectManager::SetTime(float time)
{
	for (std::unique_ptr<BaseStageObject>& object : objects_) {
		object->SetTime(time);
	}
}

void StageObjectManager::Draw(const Camera& camera) const
{
	for (const std::unique_ptr<BaseStageObject>& object : objects_) {
		object->Draw(camera);
	}
}

void StageObjectManager::DrawLight(const Camera& camera) const
{
	for (const std::unique_ptr<BaseStageObject>& object : objects_) {
		object->DrawLight(camera);
	}
}

void StageObjectManager::DrawOutline(const Camera& camera)
{
	for (const std::unique_ptr<BaseStageObject>& object : objects_) {
		object->DrawOutline(camera);
	}
}

void StageObjectManager::DrawBloom(const Camera& camera)
{
	for (const std::unique_ptr<BaseStageObject>& object : objects_) {
		object->DrawBloom(camera);
	}
}

void StageObjectManager::ApplyGlobalVariable()
{
	bool change = false;
	for (std::unique_ptr<StageObjectManager::Type>& type : types_) {
		type->num = stageEditor_->GetIntValue(type->mainName + "の数", type->mainName + "の設置", type->subName);
		if (type->num != type->preNum) {
			change = true;
			if (type->num < 0) {
				type->num = 0;
				type->preNum = 0;
			}
			else {
				type->preNum = type->num;
			}
		}
	}

	if (change) {
		CreateObjects();
	}
}

void StageObjectManager::CreateObjects()
{
	objects_.clear();
	uint32_t no = 0;
	for (const std::unique_ptr<StageObjectManager::Type>& type : types_) {
		for (uint32_t i = 0; i < type->num; i++) {
			objects_.push_back(nullptr);
			objects_.back().reset(StageObjectFactory::CreateStageObject(type->type, type->mainName, type->subName, no));
			no++;
		}
		no = 0;
	}
}
