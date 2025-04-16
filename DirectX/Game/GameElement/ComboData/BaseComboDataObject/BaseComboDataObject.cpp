#include "BaseComboDataObject.h"
#include "InstancingModelManager.h"

InstancingModelManager* BaseComboDataObject::instancingManager_ = nullptr;

void BaseComboDataObject::StaticInitialize()
{
	instancingManager_ = InstancingModelManager::GetInstance();
}

void BaseComboDataObject::Initialize()
{
}

void BaseComboDataObject::Update(float deltaTime)
{
	deltaTime;
}

void BaseComboDataObject::SetTime(float time)
{
	time;
}

void BaseComboDataObject::Draw(const Camera& camera)
{
	camera;
}

void BaseComboDataObject::DrawLight(const Camera& camera)
{
	camera;
}

void BaseComboDataObject::DrawOutline(const Camera& camera)
{
	camera;
}

void BaseComboDataObject::DrawBloom(const Camera& camera)
{
	camera;
}

void BaseComboDataObject::CreateComboEditor(const std::string& mainName, const std::string& name, const std::string& treeName, uint32_t no)
{
	std::string tree = mainName + std::to_string(no);
	comboEditor_ = std::make_unique<ComboDataEditor>(mainName, name, treeName, tree);
}
