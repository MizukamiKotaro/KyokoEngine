#include "ComboDataObjectList.h"
#include "InstancingModelManager.h"

void ComboDataObjectList::Initialize()
{
}

void ComboDataObjectList::Update(float deltaTime)
{
	for (std::unique_ptr<BaseComboDataObject>& object : comboDataObjectList_) {
		object->Update(deltaTime);
	}
}

void ComboDataObjectList::SetTime(float time)
{
	for (std::unique_ptr<BaseComboDataObject>& object : comboDataObjectList_) {
		object->SetTime(time);
	}
}

void ComboDataObjectList::Draw(const Camera& camera)
{
	for (std::unique_ptr<BaseComboDataObject>& object : comboDataObjectList_) {
		object->Draw(camera);
	}
}

void ComboDataObjectList::DrawLight(const Camera& camera)
{
	for (std::unique_ptr<BaseComboDataObject>& object : comboDataObjectList_) {
		object->DrawLight(camera);
	}
}

void ComboDataObjectList::DrawOutline(const Camera& camera)
{
	for (std::unique_ptr<BaseComboDataObject>& object : comboDataObjectList_) {
		object->DrawOutline(camera);
	}
}

void ComboDataObjectList::DrawBloom(const Camera& camera)
{
	for (std::unique_ptr<BaseComboDataObject>& object : comboDataObjectList_) {
		object->DrawBloom(camera);
	}
}

void ComboDataObjectList::CreateComboEditor(const std::string& mainName, const std::string& name, const std::string& treeName, uint32_t no)
{
	std::string tree = mainName + std::to_string(no);
	comboEditor_ = std::make_unique<ComboDataEditor>(mainName, name, treeName, tree);
}

void ComboDataObjectList::SetGlobalVariable()
{
	ApplyGlobalVariable();
}

void ComboDataObjectList::ApplyGlobalVariable()
{
}
