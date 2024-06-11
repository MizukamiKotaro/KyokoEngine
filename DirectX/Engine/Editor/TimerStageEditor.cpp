#include "TimerStageEditor.h"
#include "SceneSystem/IScene/IScene.h"

TimerStageEditor::TimerStageEditor(const std::string& tree1, const std::string& tree2, const std::string& tree3, const std::string& tree4, const std::string& tree5)
{
	preStageNo_ = IScene::stageNo_;
	global_ = std::make_unique<GlobalVariableUser>("TimerStageEditor", "Stage" + std::to_string(IScene::stageNo_), tree1, tree2, tree3, tree4, tree5);
}