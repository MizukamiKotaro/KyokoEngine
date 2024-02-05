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

	std::unique_ptr<Model> model_;
	std::array<std::unique_ptr<DirectionalLight>, 2> directionals_;
	std::array<std::unique_ptr<SpotLight>, 2> spots_;
	std::array<std::unique_ptr<PointLight>, 2> points_;

	const ModelData* data0_;
	const ModelData* data1_;

	const Texture* hoge0_;
	const Texture* hoge1_;

	bool a = false;
	bool b = false;

	bool ishoge = false;
	bool isAho = false;

	std::array<bool, 2> isSpotDraws_;
	std::array<bool, 2> isPointDraws_;

	std::array<bool, 3> is0_;

	Audio se_;
};

