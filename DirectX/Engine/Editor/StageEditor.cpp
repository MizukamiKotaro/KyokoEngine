#include "StageEditor.h"
#include "SceneSystem/SceneBase/SceneBase.h"

StageEditor::StageEditor(const std::string& tree1, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5)
{
	preStageNo_ = SceneBase::GetStageNo();
	global_ = std::make_unique<GlobalVariableUser>("StageEditor", "Stage" + std::to_string(preStageNo_), tree1, tree2, tree3, tree4, tree5);
}

StageEditor::StageEditor()
{
	preStageNo_ = SceneBase::GetStageNo();
	global_ = std::make_unique<GlobalVariableUser>("StageEditor", "Stage" + std::to_string(preStageNo_));
}
