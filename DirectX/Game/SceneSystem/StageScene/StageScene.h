#pragma once
#include <memory>
#include "SceneSystem/SceneBase/SceneBase.h"
#include "GameElement/Game.h"
/// <summary>
/// ステージシーン
/// </summary>
class StageScene : public SceneBase
{
public:
	StageScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void FirstUpdate() override;

private:
	std::unique_ptr<Game> game_; // ゲーム
};
