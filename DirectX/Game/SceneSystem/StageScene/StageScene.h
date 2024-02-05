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

	std::unique_ptr<Model> model_;
	std::unique_ptr<Sprite> sprite_;

	std::unique_ptr<Sprite> back_;
	float hogeY_ = 0.0f;

	Audio se_;

	std::unique_ptr<Sprite> title_;

	std::unique_ptr<PostEffect> post_;
	std::unique_ptr<PostEffect> post2_;
	std::unique_ptr<HighLumi> highLumi_;
	std::unique_ptr<GaussianBlur> gaussian_;
	std::unique_ptr<Blur> blur_;

	Vector4 titleColor_ = { 1.0f,1.0f,1.0f,1.0f };
	bool isBlur_ = false;
	bool isGaussianBlur_ = false;
	bool isHighLumi_ = false;
	bool isHoge_ = false;
};
