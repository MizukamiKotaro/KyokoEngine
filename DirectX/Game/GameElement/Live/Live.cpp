#include "Live.h"
#include "ImGuiManager/ImGuiManager.h"
#include "FrameInfo/FrameInfo.h"

Live::Live(Camera* camera)
{
	camera_ = camera;
	camera_->Initialize();
	dome_ = std::make_unique<Dome>();
	screen_ = std::make_unique<Screen>("Screen", "MainScreen");
	stage_ = std::make_unique<Stage>();
	stageLights_ = std::make_unique<StageLights>();
	multipleScreen_ = std::make_unique<MultipleScreen>("Screen");
	idol_ = std::make_unique<DancingIdol>();
	screenCamera_ = std::make_unique<Camera>();

	dome2_ = std::make_unique<Dome>();
	stage2_ = std::make_unique<Stage>();
	idol2_ = std::make_unique<DancingIdol>();

	screen_->SetGPUHandle(multipleScreen_->GetSRVGPUDescriptorHandle());
}

void Live::Initialize()
{
	camera_->Initialize();
	camera_->transform_.translate_ = { 0.0f,20.0f,-100.0f };
	camera_->transform_.rotate_.x = 0.1f;
	camera_->Update();

	screenCamera_->transform_.translate_ = { 0.0f,6.0f,-40.0f };
	screenCamera_->Update();


	dome_->Initialize();
	screen_->Initialize();
	stage_->Initialize();
	stageLights_->Initialize();
	idol_->Initialize();

	dome2_->Initialize();
	stage2_->Initialize();
	idol2_->Initialize();

	WriteScreen();
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
	idol_->Update(FrameInfo::GetInstance()->GetDeltaTime());

	dome2_->Update();
	stage2_->Update();
	idol2_->Update(FrameInfo::GetInstance()->GetDeltaTime());

	WriteScreen();
}

void Live::Draw()
{
	dome_->Draw(camera_);
	stage_->Draw(camera_);
	screen_->Draw(camera_);
	multipleScreen_->Draw(camera_);
	idol_->Draw(camera_);

	//stageLights_->Draw(camera_);
}

void Live::WriteScreen()
{
	multipleScreen_->PreDrawScene();

	dome2_->Draw(screenCamera_.get());
	stage2_->Draw(screenCamera_.get());
	idol2_->Draw(screenCamera_.get());
	stageLights_->Draw(screenCamera_.get());

	multipleScreen_->PostDrawScene();
}
