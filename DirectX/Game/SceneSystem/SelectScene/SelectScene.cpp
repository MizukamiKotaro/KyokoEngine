#include "SelectScene.h"
#include "Kyoko.h"
#include "ImGuiManager/ImGuiManager.h"

SelectScene::SelectScene()
{
	FirstInit();

	se_.LoadWave("SE/select.wav");

	sp_ = std::make_unique<Sprite>("uvChecker.png");
	pa_ = std::make_unique<Particle>("circle.png");

	tex0 = textureManager_->LoadTexture("Resources/Texture/uvChecker.png");
	tex1 = textureManager_->LoadTexture("Resources/Texture/white.png");
}

void SelectScene::Initialize()
{

}

void SelectScene::Update()
{
	if (input_->PressedKey(DIK_2) || input_->PressedGamePadButton(Input::GamePadButton::Y)) {
		ChangeScene(TITLE);
		se_.Play(false, 0.9f);
	}
	else if (input_->PressedKey(DIK_3) || input_->PressedGamePadButton(Input::GamePadButton::B)) {
		ChangeScene(STAGE);
		se_.Play(false, 0.9f);
	}

#ifdef _DEBUG
	
	ImGui::Begin("スプライト");
	ImGui::DragFloat2("位置", &sp_->pos_.x, 0.01f);
	ImGui::DragFloat2("サイズ", &sp_->size_.x, 0.01f);
	ImGui::DragFloat("回転", &sp_->rotate_, 0.01f);
	ImGui::SliderFloat2("テクスチャの左上の座標", &l.x, 0.0f, 1.0f);
	ImGui::SliderFloat2("テクスチャの幅", &s.x, 0.0f, 1.0f);
	ImGui::Checkbox("左右切り替え", &x);
	ImGui::Checkbox("上下切り替え", &y);
	ImGui::Checkbox("テクスチャ切り替え", &is1);
	ImGui::ColorEdit4("色", &c.x);
	ImGui::End();


	ImGui::Begin("パーティクル");
	ImGui::DragFloat3("位置", &pa_->emitter.pos.x, 0.01f);
	ImGui::DragFloat3("AABBの最小", &pa_->emitter.min.x, 0.01f);
	ImGui::DragFloat3("AABBの最大", &pa_->emitter.max.x, 0.01f);
	ImGui::SliderInt("一回に生成する数", &pa_->emitter.generateParticleNum_, 0, 10);
	ImGui::SliderFloat("生成の間隔", &pa_->emitter.generateCoolTime_, 0.0f, 5.0f);
	ImGui::End();

#endif // _DEBUG

	sp_->SetColor(c);
	sp_->SetIsFlipX(x);
	sp_->SetIsFlipY(y);
	sp_->SetTextureSize(s);
	sp_->SetTextureTopLeft(l);

	if (is1 && !a) {
		sp_->SetTexture(tex1);
		a = true;
	}
	else if (!is1 && a) {
		a = false;
		sp_->SetTexture(tex0);
	}

	sp_->Update();
	pa_->Update();
}

void SelectScene::Draw()
{
	
	Kyoko::Engine::PreDraw();

	sp_->Draw();

	pa_->Draw(*camera_.get(),BlendMode::kBlendModeAdd);

	BlackDraw();

	Kyoko::Engine::PostDraw();
}

