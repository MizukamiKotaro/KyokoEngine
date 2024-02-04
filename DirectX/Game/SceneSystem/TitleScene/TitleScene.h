#pragma once

#include "SceneSystem/IScene/IScene.h"
#include "GameElement/Live/Stage/Stage.h"
#include "GameElement/Live/Dome/Dome.h"
#include "GameElement/Live/Screen/Screen.h"
#include "Sprite.h"
#include "PostEffect/HighLumi/HighLumi.h"
#include <array>
#include "DirectionalLight/DirectionalLight.h"
#include "SpotLight/SpotLight.h"
#include "PointLight/PointLight.h"

class TitleScene : public IScene
{
public:
	TitleScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;

	void WrightPostEffect();

private:
	void LightsUpdate();

private:

	std::unique_ptr<HighLumi> highLumi_;
	std::unique_ptr<PostEffect> post_;
	std::unique_ptr<Sprite> rainbow_;
	float texcoodY_;

	std::unique_ptr<Dome> dome_;
	std::unique_ptr<Stage> stage_;
	std::unique_ptr<Screen> screen_;

	std::unique_ptr<Model> model_;
	std::array<std::unique_ptr<DirectionalLight>, 2> directionals_;
	std::array<std::unique_ptr<SpotLight>, 2> spots_;
	std::array<std::unique_ptr<PointLight>, 2> points_;

	std::array<bool, 2> isSpotDraws_;
	std::array<bool, 2> isPointDraws_;

	std::array<bool, 3> is0_;

	std::unique_ptr<Sprite> title_;
	std::unique_ptr<Sprite> space_;

	Audio se_;
};

