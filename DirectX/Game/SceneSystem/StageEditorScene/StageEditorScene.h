#pragma once
#include <memory>
#include "SceneSystem/IScene/IScene.h"
#include "GameElement/LiveEditor/LiveEditor.h"

class StageEditorScene : public IScene
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
