#include "BaseComboData.h"

void BaseComboData::CreateComboDataEditor(const std::string& mainName, const std::string& name)
{
	comboEditor_ = std::make_unique<ComboDataEditor>(mainName, name);
}

void BaseComboData::UpdateGlobalVariable()
{
#ifdef _DEBUG
	if (comboEditor_) {
		if (comboEditor_->IsTreeOpen()) {
			ApplyGlobalVariable();
		}
	}
#endif // _DEBUG
}
