#pragma once

#include <memory>
#include "SceneSystem/IScene/IScene.h"
#include "Sprite.h"
#include "PostEffect/Contrast/Contrast.h"
#include "Light/Light.h"
#include "PostEffect/HighLumi/HighLumi.h"
#include "PostEffect/Blur/Blur.h"
#include "PostEffect/GaussianBlur/GaussianBlur.h"
#include "PostEffect/Bloom/Bloom.h"
#include "PostEffect/PostEffect.h"
#include "GameElement/Game.h"

class StageScene : public IScene
{
public:

	StageScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:

	std::unique_ptr<Game> game_;
};
