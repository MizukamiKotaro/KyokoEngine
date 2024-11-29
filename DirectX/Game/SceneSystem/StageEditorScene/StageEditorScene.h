#pragma once
#include <memory>
#include "SceneSystem/SceneBase/SceneBase.h"
#include "GameElement/LiveEditor/LiveEditor.h"
/// <summary>
/// ステージエディターシーン
/// </summary>
class StageEditorScene : public SceneBase
{
public:

	StageEditorScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void FirstUpdate() override;

private:

	std::unique_ptr<LiveEditor> liveEditor_;
};
