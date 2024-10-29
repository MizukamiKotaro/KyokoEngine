#pragma once
#include <map>
#include <string>
#include <vector>
#include "ComboNameConfig.h"

class GlobalVariables;

class GlobalVariableComboNames {
public:
	
	static GlobalVariableComboNames* GetInstance();
	void Initialize();

	void AddComboName(const ComboNameType& type, const std::string& comboName);
	std::pair<std::string, std::string> GetName(const ComboNameType& type);

private:
	GlobalVariableComboNames() = default;
	~GlobalVariableComboNames() = default;
	GlobalVariableComboNames(const GlobalVariableComboNames& obj) = delete;
	GlobalVariableComboNames& operator=(const GlobalVariableComboNames& obj) = delete;

private:
	GlobalVariables* global_;
	const std::map<std::string, std::vector<std::string>>* comboNameMap_;
	std::map<ComboNameType, std::string> names_;
};
