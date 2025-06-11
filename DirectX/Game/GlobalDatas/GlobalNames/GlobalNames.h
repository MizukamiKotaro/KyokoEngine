#pragma once
#include "GlobalVariables/GlobalVariableData.h"

class GlobalNames 
{
public:
	GlobalNames(const std::string& chunk, const std::string& group);
	void AddComboName(const std::string& type, const std::string& name);
	void LoadNames(const std::string& chunk, const std::string& group);

private:
	std::unique_ptr<GlobalVariableUser> global_;
};
