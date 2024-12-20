#include "ClearScene.h"
#include "Kyoko.h"

ClearScene::ClearScene()
{
	FirstInitialize();

	dome_ = std::make_unique<Dome>();
	stage_ = std::make_unique<Stage>();
	screen_ = std::make_unique<Screen>();

	ui_ = std::make_unique<ClearUI>();

	space_ = std::make_unique<Sprite>("space.png");
	space_->pos_ = { 640.0f,560.0f };
	space_->Update();
	isEnd_ = false;

	se_.Load("SE/select.mp3", "決定音");
}

void ClearScene::Initialize()
{
	ui_->Initialize();
	isEnd_ = false;
}

void ClearScene::Update()
{
	isEnd_ = ui_->IsEnd();

	ui_->Update();

	if ((input_->PressedKey(DIK_RETURN) || input_->PressedGamePadButton(Input::GamePadButton::A)) && isEnd_) {
		// シーン切り替え
		ChangeScene(SELECT);
		se_.Play();
	}
#ifdef _DEBUG
	else if (input_->PressedKey(DIK_SPACE)) {
		// シーン切り替え
		ChangeScene(SELECT);
		se_.Play();
	}
	else if (input_->PressedKey(DIK_S)) {
		ChangeScene(STAGE_EDITOR);
		Audio::AllStop();
	}
#endif // _DEBUG
}

void ClearScene::Draw()
{
	screen_->PreDrawScene();
	ui_->Draw();
	screen_->PostDrawScene();

	Kyoko::Engine::PreDraw();

	dome_->Draw(camera_.get());
	stage_->Draw(camera_.get());
	screen_->Draw(camera_.get());

	if (isEnd_) {
		space_->Draw();
	}

	TransitionDraw();

	Kyoko::Engine::PostDraw();
}


