#include "IStageObject.h"

void IStageObject::Initialize()
{
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

void IStageObject::UpdateGlobalVariable(const uint32_t& no)
{
#ifdef _DEBUG
	if (stageEditor_) {
		if (stageEditor_->IsTreeOpen(no)) {
			ApplyGlobalVariable();
		}
	}
#endif // _DEBUG
	uint32_t a = no; a = 0;
}