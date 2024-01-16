#pragma once

#include <memory>
#include "SceneSystem/IScene/IScene.h"
#include "Game/StageLights/StageLights.h"
#include "Sprite.h"
#include "PostEffect/Contrast/Contrast.h"
#include "Light/Light.h"

class StageScene : public IScene
{
public:

	StageScene();

	void Init() override;
	void Update() override;
	void Draw() override;

private:

	std::unique_ptr<StageLights> lights_;

	std::unique_ptr<Sprite> puniru_;

	std::unique_ptr<Contrast> contrast_;

	std::unique_ptr<PointLight> pointLight_;

	std::unique_ptr<Sprite> sprite_;
};
