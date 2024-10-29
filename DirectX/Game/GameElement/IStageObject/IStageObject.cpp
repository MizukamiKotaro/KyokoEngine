#include "IStageObject.h"
#include "InstancingModelManager.h"
#include "SceneSystem/IScene/IScene.h"

InstancingModelManager* IStageObject::instancingManager_ = nullptr;

void IStageObject::StaticInitialize()
{
	instancingManager_ = InstancingModelManager::GetInstance();
}

void IStageObject::Initialize()
{
}

void IStageObject::SetTime(const float& time)
{
	time;
}

void IStageObject::DrawLight(const Camera& camera)
{
	camera;
}

void IStageObject::DrawOutline(const Camera& camera)
{
	camera;
}

void IStageObject::DrawBloom(const Camera& camera)
{
	camera;
}

void IStageObject::CreateStageEditor(const std::string& mainName, const std::string& name, const uint32_t& no, const bool& isMany)
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

void IStageObject::CreateStageEditor(const std::string& mainName, const std::string& name, const std::string& treeName, const uint32_t& no, const bool& isMany)
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

void IStageObject::InitializeEditor()
{
	if (stageEditor_) {
		stageEditor_->Initialize();
	}
}

void IStageObject::UpdateGlobalVariable()
{
#ifdef _DEBUG
	if (stageEditor_) {
		if (IScene::GetSceneNo() == STAGE_EDITOR) {
			if (stageEditor_->IsTreeOpen()) {
				ApplyGlobalVariable();
			}
		}
	}
#endif // _DEBUG
}
