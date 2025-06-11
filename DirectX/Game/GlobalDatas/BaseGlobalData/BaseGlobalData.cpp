#include "BaseGlobalData.h"

void BaseGlobalData::Update()
{
}

void BaseGlobalData::Draw()
{
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