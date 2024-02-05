#pragma once

#include "SceneSystem/IScene/IScene.h"
#include "GameElement/Live/Stage/Stage.h"
#include "GameElement/Live/Dome/Dome.h"
#include "GameElement/Live/Screen/Screen.h"
#include "GameElement/ClearUI/ClearUI.h"
#include "Sprite.h"

class ClearScene : public IScene
{
public:
	ClearScene();

	void Initialize() override;
	void Update() override;
	void Draw() override;

private:
	
};
