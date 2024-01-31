#pragma once

#include "SceneSystem/IScene/IScene.h"
#include "GameElement/Live/Stage/Stage.h"
#include "GameElement/Live/Dome/Dome.h"
#include "GameElement/Live/Screen/Screen.h"
#include "Sprite.h"
#include "PostEffect/HighLumi/HighLumi.h"

class TitleScene : public IScene
{
public:
	TitleScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;

	void WrightPostEffect();

private:

	std::unique_ptr<HighLumi> highLumi_;
	std::unique_ptr<PostEffect> post_;
	std::unique_ptr<Sprite> rainbow_;
	float texcoodY_;

	std::unique_ptr<Dome> dome_;
	std::unique_ptr<Stage> stage_;
	std::unique_ptr<Screen> screen_;


	std::unique_ptr<Sprite> title_;
	std::unique_ptr<Sprite> space_;

	Audio se_;
};

