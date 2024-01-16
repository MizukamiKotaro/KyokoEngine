#include "StageScene.h"
#include "ImGuiManager/ImGuiManager.h"
#include "Kyoko.h"

StageScene::StageScene()
{
	FirstInit();

	lights_ = std::make_unique<StageLights>();

	puniru_ = std::make_unique<Sprite>("Resources/puniru.png");

	contrast_ = std::make_unique<Contrast>();
}

void StageScene::Init()
{
}

void StageScene::Update()
{
	if (input_->PressedKey(DIK_RETURN)) {
		// シーン切り替え
		ChangeScene(CLEAR);
	}

	lights_->Update();
}

void StageScene::Draw()
{
	contrast_->PreDrawScene();


	//lights_->Draw(camera_.get());
	puniru_->Draw(*camera_.get());

	contrast_->PostDrawScene();

	Kyoko::PreDraw();

	contrast_->Draw(*camera_.get());
	
	BlackDraw();

	// フレームの終了
	Kyoko::PostDraw();
}

