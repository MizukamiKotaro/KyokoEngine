#pragma once
#include <memory>
#include "GameElement/Live/Dome/Dome.h"
#include "GameElement/Live/Screen/Screen.h"
#include "GameElement/Live/Stage/Stage.h"
#include "GameElement/Live/StageLights/StageLights.h"
#include "GameElement/Live/MultipleScreen/MultipleScreen.h"

class Camera;

class Live {
public: 

	Live(Camera* camera);

	void Initialize();

	void Update(float time);

	void Draw();

	// スクリーンに書き出す
	void WriteScreen();

private:
	Live() = default;

private:
	
	std::unique_ptr<Dome> dome_;
	std::unique_ptr<Screen> screen_;
	std::unique_ptr<MultipleScreen> multipleScreen_;
	std::unique_ptr<Stage> stage_;
	std::unique_ptr<StageLights> stageLights_;

	Camera* camera_ = nullptr;
};
