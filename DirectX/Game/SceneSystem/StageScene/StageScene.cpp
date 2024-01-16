#include "StageScene.h"
#include "ImGuiManager/ImGuiManager.h"
#include "Kyoko.h"

StageScene::StageScene()
{
	FirstInit();

	lights_ = std::make_unique<StageLights>();

	puniru_ = std::make_unique<Sprite>("Resources/puniru.png");

	sprite_ = std::make_unique<Sprite>("Resources/white.png");
	sprite_->size_ = { 1280.0f,720.0f };
	sprite_->SetColor({ 0.0f,0.0f,0.0f,1.0f });
	sprite_->Update();

	contrast_ = std::make_unique<Contrast>();

	pointLight_ = std::make_unique<PointLight>();

	slot_ = std::make_unique<Slot>();
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

#ifdef _DEBUG
	ImGui::Begin("PointLight");
	ImGui::DragFloat("距離", &pointLight_->light_->radius, 0.01f);
	ImGui::DragFloat("輝度", &pointLight_->light_->intensity, 0.01f);
	ImGui::DragFloat("減衰率", &pointLight_->light_->decay, 0.01f);
	ImGui::DragFloat3("位置", &pointLight_->light_->position.x, 0.01f);
	ImGui::ColorEdit4("色", &pointLight_->light_->color.x);
	ImGui::End();

#endif // _DEBUG

	slot_->Update(camera_.get());

	lights_->Update();
}

void StageScene::Draw()
{
	contrast_->PreDrawScene();

	sprite_->Draw(*camera_.get());
	//lights_->Draw(camera_.get());
	puniru_->Draw(*camera_.get());

	contrast_->PostDrawScene();

	Kyoko::PreDraw();

	//contrast_->Draw(*camera_.get());

	slot_->Draw(camera_.get());

	//pointLight_->Draw(*camera_.get());
	
	BlackDraw();

	// フレームの終了
	Kyoko::PostDraw();
}

