#pragma once

#include <memory>
#include "SceneSystem/IScene/IScene.h"
#include "Game/StageLights/StageLights.h"

class StageScene : public IScene
{
public:

	StageScene();

	void Init() override;
	void Update() override;
	void Draw() override;

private:

	std::unique_ptr<StageLights> lights_;
};
