#include "TitleScene.h"
#include "Kyoko.h"

TitleScene::TitleScene()
{
	FirstInit();

	dome_ = std::make_unique<Dome>();
	stage_ = std::make_unique<Stage>();
	screen_ = std::make_unique<Screen>();

	title_ = std::make_unique<Sprite>("title.png");
	title_->pos_ = { 630.0f,360.0f };
	title_->size_ *= 2;
	title_->Update();

	space_ = std::make_unique<Sprite>("space.png");
	space_->pos_ = { 640.0f,560.0f };
	space_->Update();

	rainbow_ = std::make_unique<Sprite>("rainbow.png");
	highLumi_ = std::make_unique<HighLumi>();
	post_ = std::make_unique<PostEffect>();
	texcoodY_ = 0.0f;

	se_.LoadWave("SE/select.wav");
}

void TitleScene::Initialize()
{
	
}

void TitleScene::Update()
{
	texcoodY_ += 10.0f;
	if (texcoodY_ >= 720.0f) {
		texcoodY_ -= 720.0f;
	}
	rainbow_->SetTextureTopLeft({ 0.0f,texcoodY_ });

	if (input_->PressedGamePadButton(Input::GamePadButton::A)) {
		// シーン切り替え
		ChangeScene(SELECT);
		se_.Play(false, 0.9f);
	}
}

void TitleScene::Draw()
{
	WrightPostEffect();

	Kyoko::Engine::PreDraw();

	dome_->Draw(camera_.get());
	stage_->Draw(camera_.get());
	screen_->Draw(camera_.get());
	//title_->Draw();

	space_->Draw();

	BlackDraw();

	Kyoko::Engine::PostDraw();
}

void TitleScene::WrightPostEffect()
{
	highLumi_->PreDrawScene();
	title_->Draw();
	highLumi_->PostDrawScene();

	post_->PreDrawScene();
	rainbow_->Draw();
	highLumi_->Draw(BlendMode::kBlendModeMultiply);
	post_->PostDrawScene();

	screen_->PreDrawScene();

	title_->Draw();
	post_->Draw();

	screen_->PostDrawScene();
}

