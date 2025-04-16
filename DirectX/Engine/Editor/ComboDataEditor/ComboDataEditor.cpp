#include "ComboDataEditor.h"

ComboDataEditor::ComboDataEditor(const std::string& chunkName, const std::string& groupName, const std::string& tree1, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5)
{
	global_ = std::make_unique<GlobalVariableUser>("ComboDataEditor_" + chunkName, groupName, tree1, tree2, tree3, tree4, tree5);
}

void ComboDataEditor::ResetGroupName(const std::string& groupName)
{
	global_->ResetGroupName(groupName);
}
