#include "BaseStageObject.h"
#include "InstancingModelManager.h"
#include "SceneSystem/SceneBase/SceneBase.h"

InstancingModelManager* BaseStageObject::instancingManager_ = nullptr;

void BaseStageObject::StaticInitialize()
{
	instancingManager_ = InstancingModelManager::GetInstance();
}

void BaseStageObject::Initialize()
{
}

void BaseStageObject::SetTime(float time)
{
	time;
}

void BaseStageObject::DrawLight(const Camera& camera)
{
	camera;
}

void BaseStageObject::DrawOutline(const Camera& camera)
{
	camera;
}

void BaseStageObject::DrawBloom(const Camera& camera)
{
	camera;
}

void BaseStageObject::CreateStageEditor(const std::string& mainName, const std::string& name, uint32_t no, bool isMany)
{
	if (isMany) {
		std::string tree = mainName + std::to_string(no);
		uint32_t num = no / 10;
		num = num * 10;
		std::string tree1 = mainName + std::to_string(num) + "～" + std::to_string(num + 9);
		stageEditor_ = std::make_unique<StageEditor>(mainName + "の設置", name, tree1, tree);
	}
	else {
		std::string tree = mainName + std::to_string(no);
		stageEditor_ = std::make_unique<StageEditor>(mainName + "の設置", name, tree);
	}
}

void BaseStageObject::CreateStageEditor(const std::string& mainName, const std::string& name, const std::string& treeName, uint32_t no, bool isMany)
{
	if (isMany) {
		std::string tree = mainName + std::to_string(no);
		uint32_t num = no / 10;
		num = num * 10;
		std::string tree1 = mainName + std::to_string(num) + "～" + std::to_string(num + 9);
		stageEditor_ = std::make_unique<StageEditor>(mainName + "の設置", name, treeName, tree1, tree);
	}
	else {
		std::string tree = mainName + std::to_string(no);
		stageEditor_ = std::make_unique<StageEditor>(mainName + "の設置", name, treeName, tree);
	}
}

void BaseStageObject::InitializeEditor()
{
	if (stageEditor_) {
		stageEditor_->Initialize();
	}
}

void BaseStageObject::UpdateGlobalVariable()
{
#ifdef _DEBUG
	if (stageEditor_) {
		if (SceneBase::GetSceneNo() == STAGE_EDITOR) {
			if (stageEditor_->IsTreeOpen()) {
				ApplyGlobalVariable();
			}
		}
	}
#endif // _DEBUG
}
