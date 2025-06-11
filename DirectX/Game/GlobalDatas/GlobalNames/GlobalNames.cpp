#include "GlobalNames.h"
#include "Externals/nlohmann/json.hpp"
#include <fstream>
#include <sstream>
#include <filesystem>

GlobalNames::GlobalNames(const std::string& chunk, const std::string& group)
{
	global_ = std::make_unique<GlobalVariableUser>(chunk, group);
}

void GlobalNames::AddComboName(const std::string& type, const std::string& name)
{
	global_->AddComboName(type, name);
	global_->AddItem(name, name, type);
	global_->Save();
}

void GlobalNames::LoadNames(const std::string& chunk, const std::string& group)
{
	std::string filePath = "Resources/GlobalVariables/" + chunk + "/" + chunk + "_" + group + ".json";
	std::ifstream ifs;
	ifs.open(filePath);

	if (ifs.fail()) {
		assert(0);
		return;
	}

	nlohmann::json root;
	ifs >> root;
	ifs.close();

	nlohmann::json::iterator itGroup = root.find(group);
	assert(itGroup != root.end());

	for (nlohmann::json::iterator itItem = itGroup->begin(); itItem != itGroup->end(); ++itItem) {
		const std::string& itemKey = itItem.key();
		const nlohmann::json& itemValue = itItem.value();

		if (itemValue.is_object()) {
			for (nlohmann::json::const_iterator itSub = itemValue.begin(); itSub != itemValue.end(); ++itSub) {
				const std::string& subKey = itSub.key();
				global_->AddComboName(itemKey, subKey);
			}
		}
	}
}