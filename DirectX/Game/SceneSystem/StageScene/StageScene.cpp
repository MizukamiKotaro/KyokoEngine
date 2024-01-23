#include "StageScene.h"
#include "ImGuiManager/ImGuiManager.h"
#include "Kyoko.h"

StageScene::StageScene()
{
	FirstInit();

	lights_ = std::make_unique<StageLights>();

	puniru_ = std::make_unique<Sprite>("puniru.png");

	sprite_ = std::make_unique<Sprite>("white.png");
	sprite_->size_ = { 1280.0f,720.0f };
	sprite_->SetColor({ 0.0f,0.0f,0.0f,1.0f });
	sprite_->Update();

	contrast_ = std::make_unique<Contrast>();

	highLumi_ = std::make_unique<HighLumi>();

	blur_ = std::make_unique<Blur>();
	blur2_ = std::make_unique<Blur>();

	post_ = std::make_unique<PostEffect>();

	gaussianBlur_ = std::make_unique<GaussianBlur>();

	bloom_ = std::make_unique<Bloom>();

	pointLight_ = std::make_unique<PointLight>();
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

	lights_->Update();
}

void StageScene::Draw()
{
	contrast_->PreDrawScene();

	puniru_->Draw(*camera_.get());

	contrast_->PostDrawScene();

	highLumi_->PreDrawScene();

	contrast_->Draw();
	
	highLumi_->PostDrawScene();

	blur_->PreDrawScene();

	highLumi_->Draw();
	//contrast_->Draw();
	blur_->PostDrawScene();

	blur2_->PreDrawScene();

	//highLumi_->Draw();
	contrast_->Draw();
	blur2_->PostDrawScene();

	gaussianBlur_->PreDrawScene();

	highLumi_->Draw();

	gaussianBlur_->PostDrawScene();

	bloom_->PreDrawScene();

	puniru_->Draw(*camera_.get());

	bloom_->PostDrawScene();


	Kyoko::PreDraw();

	//bloom_->Draw();
	
	/*sprite_->Draw();

	contrast_->Draw();

	blur_->color_ = { 0.3f,0.5f,1.0f,1.0f };
	blur_->blurData_->angle = 20.0f;
	blur_->blurData_->isCenterBlur = 0;
	blur_->Draw(BlendMode::kBlendModeAdd);

	blur2_->color_.x = 0.0f;
	blur2_->blurData_->angle = 90.0f;
	blur2_->pos_.x = -300.0f;
	blur2_->Update();
	blur2_->Draw();*/

	BlackDraw();

	// フレームの終了
	Kyoko::PostDraw();
}

