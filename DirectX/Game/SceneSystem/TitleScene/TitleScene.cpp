#include "TitleScene.h"
#include "Kyoko.h"
#include "ImGuiManager/ImGuiManager.h"
#include "ImGuiManager/DopeSheet.h"

TitleScene::TitleScene()
{
	FirstInitialize();

	camera_->transform_.translate_ = { 0.0f,6.0f,-70.0f };
	camera_->Update();

	dome_ = std::make_unique<Dome>();
	stage_ = std::make_unique<Stage>();
	screen_ = std::make_unique<Screen>("TitleScreen", "Screen");

	spotLightBox_ = std::make_unique<SpotLightBoxAnimation>("TitleSpotLight1");
	spotLightBox2_ = std::make_unique<SpotLightBoxAnimation>("TitleSpotLight2");

	title_ = std::make_unique<Sprite>("title.png");
	title_->pos_ = { 630.0f,360.0f };
	title_->size_ *= 2;
	title_->Update();

	space_ = std::make_unique<Sprite>("space.png");
	space_->pos_ = { 640.0f,560.0f };
	space_->Update();

	rainbow_ = std::make_unique<Sprite>("rainbow.png");
	texcoodY_ = 0.0f;

	post_ = std::make_unique<PostEffect>();
	highLumi_ = std::make_unique<HighLumi>();

	mosaic_ = std::make_unique<Mosaic>();
	rgbShift_ = std::make_unique<RGBShift>();
	rgbShift_->rgbShiftData_->shift = 0.016f;

	vignette_ = std::make_unique<Vignette>();
	vignette_->color_ = { 0.0f,1.0f,0.2f,1.0f };
	noise_ = std::make_unique<Noise>();
	bloom_ = std::make_unique<Bloom>();
	radial_ = std::make_unique<RadialBlur>();
	radial_->radialBlurData_->width = 0.03f;
	radial_->radialBlurData_->numSamples = 8;

	spotlightAndOutline_ = std::make_unique<SpotLightAndOutline>();

	se_.Load("SE/select.mp3","決定音");
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
		se_.Play();
	}

#ifdef _DEBUG
	ImGuiCommon::DopeSheet();
	// シーン切り替え
	if (input_->PressedKey(DIK_Q)) {
		ChangeScene(STAGE);
		se_.Play();
	}
	else if (input_->PressedKey(DIK_SPACE)) {
		ChangeScene(SELECT);
		se_.Play();
	}
	else if (input_->PressedKey(DIK_S)) {
		ChangeScene(STAGE_EDITOR);
		se_.Play();
	}
#endif // _DEBUG
	screen_->Update();
	spotLightBox_->Update(0.01f);
	spotLightBox2_->Update(-0.01f);
	noise_->Update(0.01f);
	bloom_->Update();
}

void TitleScene::Draw()
{
	WrightPostEffect();

	Kyoko::Engine::PreDraw();
	bloom_->Draw();
	TransitionDraw();
	Kyoko::Engine::PostDraw();
}

void TitleScene::WrightPostEffect()
{
	// ハイルミ書き込み
	highLumi_->PreDrawScene();
	title_->Draw();
	highLumi_->PostDrawScene();
	// 書き込み
	post_->PreDrawScene();
	rainbow_->Draw();
	highLumi_->Draw(BlendMode::kBlendModeMultiply);
	post_->PostDrawScene();
	// モザイク書き込み
	mosaic_->PreDrawScene();
	title_->Draw();
	post_->Draw();
	mosaic_->PostDrawScene();
	// RGBシフト書き込み
	rgbShift_->PreDrawScene();
	mosaic_->Draw();
	rgbShift_->PostDrawScene();
	// ヴィネット書き込み
	vignette_->PreDrawScene();
	noise_->Draw();
	vignette_->PostDrawScene();
	// ラディアルブラー書き込み
	radial_->PreDrawScene();
	rgbShift_->Draw();
	vignette_->Draw();
	radial_->PostDrawScene();
	// スクリーンに書き込み
	screen_->PreDrawScene();
	radial_->Draw();
	screen_->PostDrawScene();

	// ステージ用
	// アウトライン書き込み
	spotlightAndOutline_->PreDrawOutline();
	spotlightAndOutline_->PostDrawOutline();
	// 書き込み
	spotlightAndOutline_->PreDrawObject();
	spotLightBox_->Draw(camera_.get());
	spotLightBox2_->Draw(camera_.get());
	spotlightAndOutline_->PostDrawObject();
	// ライト書き込み
	spotlightAndOutline_->PreDrawLight();
	spotLightBox_->DrawLight(*camera_.get());
	spotLightBox2_->DrawLight(*camera_.get());
	spotlightAndOutline_->PostDrawLight();
	// ブルーム書き込み
	spotlightAndOutline_->PreDrawBloom();
	screen_->Draw(camera_.get());
	dome_->Draw(camera_.get());
	stage_->Draw(camera_.get());
	space_->Draw();
	TransitionDraw();
	spotlightAndOutline_->PostDrawBloom();

	// ブルーム書き込み
	bloom_->PreDrawScene();
	spotlightAndOutline_->Draw(*camera_.get());
	bloom_->PostDrawScene();
}

