#include "TitleScene.h"
#include "Kyoko.h"

#include "ImGuiManager/ImGuiManager.h"
#include <string>

TitleScene::TitleScene()
{
	FirstInit();

	se_.LoadWave("SE/select.wav");

	model_ = std::make_unique<Model>("Sphere");

	data0_ = ModelDataManager::GetInstance()->LoadObj("Sphere");
	data1_ = ModelDataManager::GetInstance()->LoadObj("Cube");

	hoge0_ = textureManager_->LoadTexture("Resources/Texture/uvChecker.png");
	hoge1_ = textureManager_->LoadTexture("Resources/Texture/rainbow.png");

	for (int i = 0; i < 2; i++) {
		directionals_[i] = std::make_unique<DirectionalLight>();
		spots_[i] = std::make_unique<SpotLight>();
		points_[i] = std::make_unique<PointLight>();

		isSpotDraws_[i] = false;
		isPointDraws_[i] = false;
	}
	for (int i = 0; i < 3; i++) {
		is0_[i] = true;
	}

	model_->SetPointLight(points_[0].get());
	model_->SetDirectionalLight(directionals_[0].get());
	model_->SetSpotLight(spots_[0].get());
	model_->transform_.translate_.y = 1.0f;
	model_->Update();

}

void TitleScene::Initialize()
{
	
}

void TitleScene::Update()
{
	LightsUpdate();

#ifdef _DEBUG
	ImGui::Begin("カメラ");
	ImGui::DragFloat3("位置", &camera_->transform_.translate_.x, 0.01f);
	ImGui::DragFloat3("向き", &camera_->transform_.rotate_.x, 0.01f);
	ImGui::End();

	ImGui::Begin("モデル");
	ImGui::DragFloat3("位置", &model_->transform_.translate_.x, 0.01f);
	ImGui::DragFloat3("向き", &model_->transform_.rotate_.x, 0.01f);
	ImGui::DragFloat3("スケール", &model_->transform_.scale_.x, 0.01f);
	ImGui::Checkbox("モデル切り替え", &a);
	ImGui::Checkbox("テクスチャ切り替え", &b);
	ImGui::End();
#endif // _DEBUG

	if (a && ishoge) {
		model_->SetModelData(data1_);
		ishoge = false;
	}
	else if (!a && !ishoge) {
		model_->SetModelData(data0_);
		ishoge = true;
	}

	if (b && isAho) {
		model_->SetTexture(hoge0_);
		isAho = false;
	}
	else if (!b && !isAho) {
		model_->SetTexture(hoge1_);
		isAho = true;
	}

	model_->Update();
	camera_->Update();

	if (input_->PressedKey(DIK_1) || input_->PressedGamePadButton(Input::GamePadButton::X)) {
		ChangeScene(SELECT);
		se_.Play(false, 0.9f);
	}
	else if (input_->PressedKey(DIK_3) || input_->PressedGamePadButton(Input::GamePadButton::B)) {
		ChangeScene(STAGE);
		se_.Play(false, 0.9f);
	}

}

void TitleScene::Draw()
{
	WrightPostEffect();

	Kyoko::Engine::PreDraw();

	model_->Draw(*camera_.get());

	for (int i = 0; i < 2; i++) {
		if (isSpotDraws_[i]) {
			spots_[i]->Draw(*camera_.get());
		}
		if (isPointDraws_[i]) {
			points_[i]->Draw(*camera_.get());
		}
	}

	BlackDraw();

	Kyoko::Engine::PostDraw();
}

void TitleScene::WrightPostEffect()
{
	
}

void TitleScene::LightsUpdate()
{
#ifdef _DEBUG

	ImGui::Begin("ライト");
	for (int i = 0; i < 2; i++) {
		std::string name = "平行光源" + std::to_string(i);
		if (ImGui::TreeNode(name.c_str())) {
			ImGui::SliderFloat("輝度", &directionals_[i]->light_->intensity, 0.0f, 100.0f);
			ImGui::SliderFloat3("方向", &directionals_[i]->light_->direction.x, -1.0f, 1.0f);
			ImGui::ColorEdit3("色", &directionals_[i]->light_->color.x);
			directionals_[i]->Update();
			ImGui::TreePop();
		}

		name = "点光源" + std::to_string(i);
		if (ImGui::TreeNode(name.c_str())) {
			ImGui::SliderFloat3("位置", &points_[i]->light_->position.x, -50.0f, 50.0f);
			ImGui::SliderFloat("半径", &points_[i]->light_->radius, -50.0f, 50.0f);
			ImGui::SliderFloat("輝度", &points_[i]->light_->intensity, 0.0f, 100.0f);
			ImGui::SliderFloat("減衰率", &points_[i]->light_->decay, 0.0f, 100.0f);
			ImGui::ColorEdit3("色", &points_[i]->light_->color.x);
			ImGui::Checkbox("描画", &isPointDraws_[i]);
			points_[i]->Update();
			ImGui::TreePop();
		}

		name = "スポットライト" + std::to_string(i);
		if (ImGui::TreeNode(name.c_str())) {
			ImGui::SliderFloat3("位置", &spots_[i]->light_->position.x, -50.0f, 50.0f);
			ImGui::SliderFloat3("方向", &spots_[i]->light_->direction.x, -1.0f, 1.0f);
			ImGui::SliderFloat("距離", &spots_[i]->light_->distance, 0.0f, 100.0f);
			ImGui::SliderFloat("輝度", &spots_[i]->light_->intensity, 0.0f, 100.0f);
			ImGui::SliderFloat("減衰率", &spots_[i]->light_->decay, 0.0f, 100.0f);
			ImGui::SliderFloat("角度", &spots_[i]->light_->cosAngle, -1.0f, 1.0f);
			ImGui::SliderFloat("減衰の始まる角度", &spots_[i]->light_->cosFalloffStart, -1.0f, 1.0f);
			ImGui::ColorEdit3("色", &spots_[i]->light_->color.x);
			ImGui::Checkbox("描画", &isSpotDraws_[i]);
			spots_[i]->Update();
			ImGui::TreePop();
		}
	}
	ImGui::Checkbox("平行光源の切り替え", &is0_[0]);
	ImGui::Checkbox("点光源の切り替え", &is0_[1]);
	ImGui::Checkbox("スポットライトの切り替え", &is0_[2]);
	ImGui::End();

	if (is0_[0]) {
		model_->SetDirectionalLight(directionals_[0].get());
	}
	else {
		model_->SetDirectionalLight(directionals_[1].get());
	}

	if (is0_[1]) {
		model_->SetPointLight(points_[0].get());
	}
	else {
		model_->SetPointLight(points_[1].get());
	}

	if (is0_[2]) {
		model_->SetSpotLight(spots_[0].get());
	}
	else {
		model_->SetSpotLight(spots_[1].get());
	}

#endif // _DEBUG
}

