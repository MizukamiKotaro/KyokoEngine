#include "BaseGlobalData.h"

void BaseGlobalData::Update()
{
	data_->Update();
}

void BaseGlobalData::DrawImGui(const std::string& treeName, bool isSave)
{
	data_->DrawImGui(treeName, isSave);
}

void BaseGlobalData::Save()
{
	data_->Save();
}

void BaseGlobalData::SetData(const std::map<int32_t, GlobalVariableData::Item>& items)
{
	data_->SetData(items);
}

const std::map<int32_t, GlobalVariableData::Item>& BaseGlobalData::GetData() const
{
	return data_->GetData();
}

const GlobalVariableData& BaseGlobalData::GetGlobalData() const
{
	return *data_;
}

void BaseGlobalData::SetData(const GlobalVariableData& data)
{
	data_ = std::make_unique<GlobalVariableData>(data);
}
