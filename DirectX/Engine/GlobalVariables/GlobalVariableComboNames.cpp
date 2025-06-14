#include "GlobalVariableComboNames.h"

GlobalVariableComboNames* GlobalVariableComboNames::GetInstance()
{
	static GlobalVariableComboNames instance;
	return &instance;
}

void GlobalVariableComboNames::Initialize()
{
	global_ = Kyoko::GlobalVariables::GetInstance();
	comboNameMap_ = global_->GetComboNameMap();

	names_[ComboNameType::kTexture] = "Texture";
	names_[ComboNameType::kOBJ] = "Model";
	names_[ComboNameType::kRigidAnimationModel] = "RigidAnimModel";
	names_[ComboNameType::kSkinningModel] = "SkinningModel";
	names_[ComboNameType::kAudio] = "Audio";
	names_[ComboNameType::kCameraAnimationVMD] = "CameraVMDAnim";
	names_[ComboNameType::kCombo] = "Combo";
}

void GlobalVariableComboNames::AddComboName(ComboNameType type, const std::string& comboName)
{
	global_->AddComboName(names_[type], comboName);
}

std::pair<std::string, std::string> GlobalVariableComboNames::GetName(ComboNameType type)
{
	std::pair<std::string, std::string> name;
	name.first = names_[type];
	name.second = comboNameMap_->find(names_[type])->second[0];
	return name;
}

void GlobalVariableComboNames::AddComboType(const std::string& typeName)
{
	for (const std::string& name : dnames_) {
		if (name == typeName) {
			return;
		}
	}
	AddComboName(ComboNameType::kCombo, typeName);
	dnames_.push_back(typeName);
}

void GlobalVariableComboNames::AddComboName(int32_t type, const std::string& comboName)
{
	global_->AddComboName(dnames_[type], comboName);
}

void GlobalVariableComboNames::AddComboName(const std::string& type, const std::string& comboName)
{
	for (const std::string& name : dnames_) {
		if (name == type) {
			global_->AddComboName(type, comboName);
			return;
		}
	}
	AddComboType(type);
	global_->AddComboName(type, comboName);
}

std::pair<std::string, std::string> GlobalVariableComboNames::GetName(int32_t type)
{
	std::pair<std::string, std::string> name;
	name.first = dnames_[type];
	name.second = comboNameMap_->find(dnames_[type])->second[0];
	return name;
}

void GlobalVariableComboNames::AddSystemComboType(const std::string& typeName)
{
	for (const std::string& name : snames_) {
		if (name == typeName) {
			return;
		}
	}
	AddComboName(ComboNameType::kCombo, typeName);
	snames_.push_back(typeName);
}

void GlobalVariableComboNames::AddSystemComboName(int32_t type, const std::string& comboName)
{
	global_->AddComboName(snames_[type], comboName);
}

void GlobalVariableComboNames::AddSystemComboName(const std::string& type, const std::string& comboName)
{
	for (const std::string& name : snames_) {
		if (name == type) {
			global_->AddComboName(type, comboName);
			return;
		}
	}
	AddSystemComboType(type);
	global_->AddComboName(type, comboName);
}

std::pair<std::string, std::string> GlobalVariableComboNames::GetSystemName(int32_t type)
{
	std::pair<std::string, std::string> name;
	name.first = snames_[type];
	name.second = comboNameMap_->find(snames_[type])->second[0];
	return name;
}