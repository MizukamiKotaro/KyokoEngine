#include "StageScene.h"
#include "ImGuiManager/ImGuiManager.h"
#include "Kyoko.h"

StageScene::StageScene()
{
	FirstInit();

	model_ = std::make_unique<Model>("plane");
	model_->SetTexture(TextureManager::GetInstance()->LoadTexture("Resources/Texture/white.png"));
	model_->transform_.translate_ = { 0.0f,0.0f,0.0f };
	model_->transform_.scale_ = { 3.2f * 1.4f,1.8f * 1.4f,1.0f };
	model_->transform_.rotate_.y = 3.14f;
	model_->Update();
	model_->UnUsedLight();
	model_->SetColor(Vector4{ 1.0f,1.0f,1.0f,1.0f });

	sprite_ = std::make_unique<Sprite>("rainbow.png");
	back_ = std::make_unique<Sprite>("white.png");
	back_->size_ = { 1280.0f,720.0f };
	back_->SetColor({ 0.0f,0.0f,0.0f,1.0f });
	back_->Update();

	title_ = std::make_unique<Sprite>("title.png");

	post_ = std::make_unique<PostEffect>();
	highLumi_ = std::make_unique<HighLumi>();
	gaussian_ = std::make_unique<GaussianBlur>();
	blur_ = std::make_unique<Blur>();

	post2_ = std::make_unique<PostEffect>();

	model_->SetSRVGPUDescriptorHandle_(post_->GetSRVGPUDescriptorHandle());

	se_.LoadWave("SE/select.wav");
}

void StageScene::Initialize()
{
	
	post_->PreDrawScene();

	back_->Draw();
	title_->Draw();

	post_->PostDrawScene();

}

void StageScene::Update()
{
	if (input_->PressedKey(DIK_1) || input_->PressedGamePadButton(Input::GamePadButton::X)) {
		ChangeScene(SELECT);
		se_.Play(false, 0.9f);
	}
	else if (input_->PressedKey(DIK_2) || input_->PressedGamePadButton(Input::GamePadButton::Y)) {
		ChangeScene(TITLE);
		se_.Play(false, 0.9f);
	}

	

	hogeY_ += 20.0f;
	if (hogeY_ >= 720.0f) {
		sprite_->SetTextureTopLeft({ 0.0f,hogeY_ });
	}

#ifdef _DEBUG

	bool a;
	if (blur_->blurData_->isCenterBlur == 1) {
		a = true;
	}
	else {
		a = false;
	}


	ImGui::Begin("モデル");
	ImGui::DragFloat3("スケール", &model_->transform_.scale_.x, 0.01f);
	ImGui::DragFloat3("向き", &model_->transform_.rotate_.x, 0.01f);
	ImGui::DragFloat3("位置", &model_->transform_.translate_.x, 0.01f);
	ImGui::End();
	model_->Update();

	ImGui::Begin("ポストエフェクト");
	if (ImGui::TreeNode("ブラー")) {
		ImGui::Checkbox("ブラーをかけるか", &isBlur_);
		ImGui::Checkbox("真ん中からブラーか", &a);
		ImGui::SliderFloat("角度", &blur_->blurData_->angle, -180.0f, 180.0f);
		ImGui::ColorEdit3("色", &blur_->color_.x);
		ImGui::TreePop();

		if (a) {
			blur_->blurData_->isCenterBlur = 1;
		}
		else {
			blur_->blurData_->isCenterBlur = 0;
		}
	}
	if (ImGui::TreeNode("ガウシアンブラー")) {
		ImGui::Checkbox("ガウシアンブラーをかけるか", &isGaussianBlur_);
		ImGui::TreePop();
	}

	bool b;
	if (highLumi_->highLumiData_->isToWhite == 1) {
		b = true;
	}
	else {
		b = false;
	}
	if (ImGui::TreeNode("ハイルミ")) {
		ImGui::Checkbox("切り抜くか", &isHoge_);
		ImGui::TreePop();
		if (b) {
			highLumi_->highLumiData_->isToWhite = 1;
		}
		else {
			highLumi_->highLumiData_->isToWhite = 0;
		}

		if (highLumi_->highLumiData_->min >= highLumi_->highLumiData_->max) {
			if (highLumi_->highLumiData_->max != 0.0f) {
				highLumi_->highLumiData_->min = highLumi_->highLumiData_->max - 0.01f;
			}
			else {
				highLumi_->highLumiData_->max = 0.01f;
			}
		}
	}

	ImGui::End();

#endif // _DEBUG
}

void StageScene::Draw()
{
	if (isHoge_) {
		highLumi_->PreDrawScene();
		title_->Draw();
		highLumi_->PostDrawScene();

		if (isHoge_) {
			post2_->PreDrawScene();
			sprite_->Draw();
			highLumi_->Draw(BlendMode::kBlendModeMultiply);
			post2_->PostDrawScene();
		}
	}
	if (isBlur_) {
		blur_->PreDrawScene();
		if (isHoge_) {
			post2_->Draw();
		}
		else {
			back_->Draw();
			title_->Draw();
		}
		blur_->PostDrawScene();
	}
	if (isGaussianBlur_) {
		gaussian_->PreDrawScene();
		
		if (isHoge_) {
			post2_->Draw();
		}
		else {
			title_->Draw();
		}

		gaussian_->PostDrawScene();
	}

	if (isBlur_ || isHoge_ || isGaussianBlur_) {
		post_->PreDrawScene();

		if (isHoge_) {
			back_->Draw();
			post2_->Draw();
		}
		else {
			title_->Draw();
		}
		
		if (isBlur_) {
			blur_->Draw(BlendMode::kBlendModeAdd);
		}

		if (isGaussianBlur_) {
			gaussian_->Draw(BlendMode::kBlendModeAdd);
		}

		post_->PostDrawScene();
	}
	else {
		post_->PreDrawScene();

		back_->Draw();
		title_->Draw();

		post_->PostDrawScene();
	}

	Kyoko::Engine::PreDraw();

	model_->Draw(*camera_.get());

	BlackDraw();

	// フレームの終了
	Kyoko::Engine::PostDraw();
}

