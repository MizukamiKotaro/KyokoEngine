#include "Live.h"
#include "Camera.h"
#include "ImGuiManager/ImGuiManager.h"

Live::Live(Camera* camera)
{
	camera_ = camera;
	camera_->Initialize();
	dome_ = std::make_unique<Dome>();
	screen_ = std::make_unique<Screen>("Screen", "MainScreen");
	stage_ = std::make_unique<Stage>();
	stageLights_ = std::make_unique<StageLights>();
	multipleScreen_ = std::make_unique<MultipleScreen>("Screen");

	screen_->SetGPUHandle(multipleScreen_->GetSRVGPUDescriptorHandle());
}

void Live::Initialize()
{
	camera_->Initialize();

	dome_->Initialize();
	screen_->Initialize();
	stage_->Initialize();
	stageLights_->Initialize();
	WriteScreen();
}

void Live::Update(float time)
{
#ifdef _DEBUG
	ImGui::Begin("Camera");
	ImGui::DragFloat3("ポジション", &camera_->transform_.translate_.x, 0.01f);
	ImGui::SliderFloat3("角度", &camera_->transform_.rotate_.x, -3.14f, 3.14f);
	ImGui::End();
#endif // _DEBUG
	camera_->Update();

	dome_->Update();
	screen_->Update();
	stage_->Update();
	stageLights_->Update(time);
	multipleScreen_->Update();

	WriteScreen();
}

void Live::Draw()
{
	dome_->Draw(camera_);
	stage_->Draw(camera_);
	screen_->Draw(camera_);
	multipleScreen_->Draw(camera_);

	stageLights_->Draw(camera_);
}

void Live::WriteScreen()
{
	multipleScreen_->PreDrawScene();

	dome_->Draw(camera_);
	stage_->Draw(camera_);

	multipleScreen_->PostDrawScene();

	/*screen_->PreDrawScene();

	dome_->Draw(camera);
	stage_->Draw(camera);

	screen_->PostDrawScene();*/
}
