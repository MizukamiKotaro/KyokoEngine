#include "StageScene.h"
#include "ImGuiManager/ImGuiManager.h"
#include "Kyoko.h"

StageScene::StageScene()
{
	FirstInit();

	lights_ = std::make_unique<StageLights>();
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

	Kyoko::PreDraw();


	lights_->Draw(camera_.get());
	
	BlackDraw();

	// フレームの終了
	Kyoko::PostDraw();
}

