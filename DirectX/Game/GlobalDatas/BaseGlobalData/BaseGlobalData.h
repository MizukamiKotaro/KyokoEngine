#pragma once
#include "GlobalVariables/GlobalVariableData.h"

class BaseGlobalData
{
public:
	virtual ~BaseGlobalData() = default;
	virtual void CreateData(const std::string& chunk) = 0;
	virtual void Update();
	virtual void Draw();

	void DrawImGui(const std::string& treeName, bool isSave = false);
	void Save();
	void SetData(const std::map<int32_t, GlobalVariableData::Item>& items);
	const std::map<int32_t, GlobalVariableData::Item>& GetData() const;

protected:
	std::unique_ptr<GlobalVariableData> datas_;
};
