#include "StageScene.h"
#include "Kyoko.h"

StageScene::StageScene()
{
	FirstInitialize();
	game_ = std::make_unique<Game>(camera_.get());
}

void StageScene::Initialize()
{
	game_->Initialize();
}

void StageScene::Update()
{
	if (game_->GetIsClear()) {
		// シーン切り替え
		ChangeScene(CLEAR);
		Audio::AllStop();
	}
#ifdef _DEBUG
	// シーン切り替え
	if (input_->PressedKey(DIK_SPACE)) {
		ChangeScene(CLEAR);
		Audio::AllStop();
	}
	else if (input_->PressedKey(DIK_S)) {
		ChangeScene(STAGE_EDITOR);
		Audio::AllStop();
	}
#endif // _DEBUG
	game_->Update();
}

void StageScene::Draw()
{
	Kyoko::Engine::PreDraw();
	game_->Draw();
	TransitionDraw();
	Kyoko::Engine::PostDraw();
}

void StageScene::FirstUpdate()
{
	game_->FirstUpdate();
}

