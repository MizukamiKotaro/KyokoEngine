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

class StageScene : public IScene
{
public:

	StageScene();

	void Init() override;
	void Update() override;
	void Draw() override;

private:

	std::unique_ptr<Sprite> puniru_;

	std::unique_ptr<Contrast> contrast_;

	std::unique_ptr<HighLumi> highLumi_;

	std::unique_ptr<Blur> blur_;

	std::unique_ptr<Blur> blur2_;

	std::unique_ptr<PostEffect> post_;

	std::unique_ptr<GaussianBlur> gaussianBlur_;

	std::unique_ptr<Bloom> bloom_;

	std::unique_ptr<PointLight> pointLight_;

	std::unique_ptr<Sprite> sprite_;
};
