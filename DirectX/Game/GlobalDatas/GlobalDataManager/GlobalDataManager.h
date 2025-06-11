#pragma once
#include "GlobalVariables/GlobalVariableData.h"
#include "GlobalDatas/GlobalNames/GlobalNames.h"

class GlobalDataManager
{
public:
	enum class ComboTypeNames {
		kCount, // 末尾
	};

	static GlobalDataManager* GetInstance();
	void Initialize();
	void Update();
	void Draw();

private:
	GlobalDataManager() = default;
	~GlobalDataManager() = default;
	GlobalDataManager(const GlobalDataManager& obj) = delete;
	GlobalDataManager& operator=(const GlobalDataManager& obj) = delete;

	void AddTypes();

	const std::string kChunkName = "ComboManager";
	const std::string kTitleBarName = "ComboName";

	std::map<std::string, std::vector<std::string>> types_;
	std::unique_ptr<GlobalVariableData> global_;

	std::unique_ptr<GlobalNames> names_;

	bool isDebug_;
	bool isDefult_;
};
