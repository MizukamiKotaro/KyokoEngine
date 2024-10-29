#pragma once
#include <memory>
#include "SceneSystem/IScene/IScene.h"
#include "GameElement/Game.h"

class StageScene : public IScene
{
public:

	StageScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;
	void FirstUpdate() override;

private:

	std::unique_ptr<Game> game_;
};
