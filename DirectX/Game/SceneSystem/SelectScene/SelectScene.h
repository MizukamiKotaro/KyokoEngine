#pragma once

#include "SceneSystem/SceneBase/SceneBase.h"
#include "GameElement/Live/Stage/Stage.h"
#include "GameElement/Live/Dome/Dome.h"
#include "GameElement/Live/Screen/Screen.h"
#include "GameElement/Live/LiveMusics/LiveMusics.h"
#include "Sprite.h"
#include <array>
/// <summary>
/// セレクトシーン
/// </summary>
class SelectScene : public SceneBase
{
public:
	SelectScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;

private:

	std::unique_ptr<Dome> dome_; // ドーム
	std::unique_ptr<Stage> stage_; // ステージ
	std::unique_ptr<Screen> screen_; // スクリーン

	std::array<std::unique_ptr<Sprite>, COUNT_STAGE> musicSprites_; // スプライト
	std::unique_ptr<Sprite> space_; // スペース

	std::unique_ptr<Audio> se_; // SE
	std::unique_ptr<LiveMusics> music_; // MUSIC
};

