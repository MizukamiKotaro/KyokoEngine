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

	highLumi_ = std::make_unique<HighLumi>();

	blur_ = std::make_unique<Blur>();

	gaussianBlur_ = std::make_unique<GaussianBlur>();

	bloom_ = std::make_unique<Bloom>();

	pointLight_ = std::make_unique<PointLight>();

	slot_ = std::make_unique<Slot>();
}

void StageScene::Init()
{
	slot_->Initialize();
	slot_->PostEffectWright(camera_.get());
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

	highLumi_->PreDrawScene();

	contrast_->Draw();
	
	highLumi_->PostDrawScene();

	blur_->PreDrawScene();

	highLumi_->Draw();

	blur_->PostDrawScene();

	gaussianBlur_->PreDrawScene();

	highLumi_->Draw();

	gaussianBlur_->PostDrawScene();

	/*contrast_->PreDrawScene();

	puniru_->Draw(*camera_.get());
	gaussianBlur_->Draw(BlendMode::kBlendModeAdd);

	contrast_->PostDrawScene();*/

	bloom_->PreDrawScene();

	puniru_->Draw(*camera_.get());

	bloom_->PostDrawScene();

	Kyoko::PreDraw();

	//bloom_->Draw();

	contrast_->Draw();

	//blur_->Draw(BlendMode::kBlendModeAdd);
	//contrast_->Draw();
	//puniru_->Draw(*camera_.get());
	//gaussianBlur_->Draw(BlendMode::kBlendModeAdd);

	//slot_->Draw(camera_.get());

	//pointLight_->Draw(*camera_.get());
	
	BlackDraw();

	// フレームの終了
	Kyoko::PostDraw();
}

