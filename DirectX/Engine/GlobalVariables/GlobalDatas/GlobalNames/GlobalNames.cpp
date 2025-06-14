#include "GlobalNames.h"
#include "Externals/nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

GlobalNames::GlobalNames(const std::string& chunk, const std::string& group)
{
	global_ = std::make_unique<GlobalVariableUser>(chunk, group);
	sglobal_ = std::make_unique<GlobalVariableUser>(chunk, group + "System");
	LoadNames(chunk, group);
}

void GlobalNames::AddComboName(int32_t no, const std::string& type, const std::string& name)
{
	global_->AddComboName(type, name);
	global_->AddItem(name, type, std::to_string(no));
	global_->Save();
	std::vector<std::string>& vec = names_[type];
	if (std::find(vec.begin(), vec.end(), name) == vec.end()) {
		vec.push_back(name);
	}
}

void GlobalNames::AddSystemComboName(int32_t no, const std::string& type, const std::string& name)
{
	sglobal_->AddSystemComboName(type, name);
	sglobal_->AddItem(name, type, std::to_string(no));
	sglobal_->Save();
}

void GlobalNames::LoadNames(const std::string& chunk, const std::string& group)
{
	LoadName(chunk, group, true);
	LoadName(chunk, group, false);
}

const std::vector<std::string>& GlobalNames::GetNames(const std::string& type)
{
	return names_[type];
}

void GlobalNames::LoadName(const std::string& chunk, const std::string& group, bool isSystem)
{
	std::string name = group;
	if (isSystem) {
		name += "System";
	}

	std::string filePath = "KyokoGlobalVariables/" + chunk + "/" + chunk + "_" + name + ".json";
	std::ifstream ifs;
	ifs.open(filePath);
	if (!ifs.is_open()) {
		return;
	}

	nlohmann::json root;
	ifs >> root;
	ifs.close();

	nlohmann::json::iterator itGroup = root.find(name);
	assert(itGroup != root.end());

	for (nlohmann::json::iterator itItem = itGroup->begin(); itItem != itGroup->end(); ++itItem) {
		const nlohmann::json& itemValue = itItem.value();

		if (itemValue.is_object()) {
			for (nlohmann::json::const_iterator itSub = itemValue.begin(); itSub != itemValue.end(); ++itSub) {
				const std::string& subKey = itSub.key();
				const std::string& subValue = itSub.value();
				if (isSystem) {
					sglobal_->AddSystemComboName(subValue, subKey);
				}
				else {
					global_->AddComboName(subValue, subKey);
					std::vector<std::string>& vec = names_[subValue];
					if (std::find(vec.begin(), vec.end(), subKey) == vec.end()) {
						vec.push_back(subKey);
					}
				}
			}
		}
	}
}
