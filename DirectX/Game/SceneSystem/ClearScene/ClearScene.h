#pragma once

#include "SceneSystem/SceneBase/SceneBase.h"
#include "GameElement/Live/Stage/Stage.h"
#include "GameElement/Live/Dome/Dome.h"
#include "GameElement/Live/Screen/Screen.h"
#include "GameElement/ClearUI/ClearUI.h"
#include "Sprite.h"
/// <summary>
/// クリアシーン
/// </summary>
class ClearScene : public SceneBase
{
public:
	ClearScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	std::unique_ptr<Dome> dome_;
	std::unique_ptr<Stage> stage_;
	std::unique_ptr<Screen> screen_;
	std::unique_ptr<ClearUI> ui_;
	
	bool isEnd_;

	std::unique_ptr<Sprite> space_;
	
	Audio se_;
};
