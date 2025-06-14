#include "BaseGlobalData.h"

void BaseGlobalData::Update()
{
	datas_->Update();
}

void BaseGlobalData::DrawImGui(const std::string& treeName, bool isSave)
{
	datas_->DrawImGui(treeName, isSave);
}

void BaseGlobalData::Save()
{
	datas_->Save();
}

void BaseGlobalData::SetData(const std::map<int32_t, GlobalVariableData::Item>& items)
{
	datas_->SetData(items);
}

const std::map<int32_t, GlobalVariableData::Item>& BaseGlobalData::GetData() const
{
	return datas_->GetData();
}

const GlobalVariableData& BaseGlobalData::GetGlobalData() const
{
	return *datas_;
}

void BaseGlobalData::SetData(const GlobalVariableData& data)
{
	datas_ = std::make_unique<GlobalVariableData>(data);
}
