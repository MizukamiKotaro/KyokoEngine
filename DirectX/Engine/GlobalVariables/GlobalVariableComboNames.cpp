#include "GlobalVariableComboNames.h"
#include "GlobalVariables.h"

GlobalVariableComboNames* GlobalVariableComboNames::GetInstance()
{
	static GlobalVariableComboNames instance;
	return &instance;
}

void GlobalVariableComboNames::Initialize()
{
	global_ = GlobalVariables::GetInstance();
	comboNameMap_ = global_->GetComboNameMap();

	names_[ComboNameType::kTexture] = "Texture";
	names_[ComboNameType::kOBJ] = "Model";
	names_[ComboNameType::kRigidAnimationModel] = "RigidAnimModel";
	names_[ComboNameType::kSkinningModel] = "SkinningModel";
	names_[ComboNameType::kAudio] = "Audio";
	names_[ComboNameType::kCameraAnimationVMD] = "CameraVMDAnim";
}

void GlobalVariableComboNames::AddComboName(const ComboNameType& type, const std::string& comboName)
{
	global_->AddComboName(names_[type], comboName);
}

std::pair<std::string, std::string> GlobalVariableComboNames::GetName(const ComboNameType& type)
{
	std::pair<std::string, std::string> name;
	name.first = names_[type];
	name.second = comboNameMap_->find(names_[type])->second[0];
	return name;
}
