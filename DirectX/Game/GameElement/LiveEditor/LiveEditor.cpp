#include "LiveEditor.h"
#include "Camera.h"
#include "GameElement/IStageObject/StageObjectConfig.h"
#include "GameElement/IStageObject/StageObjectFactory/StageObjectFactory.h"

LiveEditor::LiveEditor(Camera* camera)
{
	camera_ = camera;
	camera_->Initialize();
	
	screenCamera_ = std::make_unique<Camera>();
	outline_ = std::make_unique<Outline>();
	outline2_ = std::make_unique<Outline>();

	screenManager_ = std::make_unique<MultipleScreenEditor>("スクリーン", "マルチスクリーン", 0);
	idolManager_ = std::make_unique<IStageObjectManager>();
	idolManager_->AddType(StageObjectType::IDOL, "アイドル", "メインアイドル");
	lightManager_ = std::make_unique<IStageObjectManager>();
	lightManager_->AddType(StageObjectType::SPOTLIGHT, "ライト", "スポットライト");
	lightManager_->AddType(StageObjectType::TWIN_SPOTLIGHT, "ライト", "ツインスポットライト");
	floor_.reset(StageObjectFactory::CreateStageObject(StageObjectType::FLOOR, "ステージ床", "ステージ床", 0));
	dome_.reset(StageObjectFactory::CreateStageObject(StageObjectType::DOME, "ドーム", "ドーム", 0));
}

void LiveEditor::Initialize()
{
	camera_->Initialize();
	camera_->transform_.translate_ = { 0.0f,20.0f,-100.0f };
	camera_->transform_.rotate_.x = 0.1f;
	camera_->Update();

	screenCamera_->transform_.translate_ = { 0.0f,6.0f,-40.0f };
	screenCamera_->Update();

	lightManager_->Initialize();
	idolManager_->Initialize();
	floor_->Initialize();
	dome_->Initialize();

	WriteScreen();
	WriteScreen();
	WriteOutline();
}

void LiveEditor::Update(const float& time)
{
#ifdef _DEBUG
	/*ImGui::Begin("Camera");
	ImGui::DragFloat3("ポジション", &camera_->transform_.translate_.x, 0.01f);
	ImGui::SliderFloat3("角度", &camera_->transform_.rotate_.x, -3.14f, 3.14f);
	ImGui::End();*/
	
#endif // _DEBUG
	camera_->Update();

	lightManager_->Update(time);
	screenManager_->Update(time);
	idolManager_->Update(time);
	floor_->Update(time);
	dome_->Update(time);

	WriteScreen();
	WriteOutline();
}

void LiveEditor::Draw()
{
	dome_->Draw(*camera_);
	floor_->Draw(*camera_);
	outline_->Draw(*camera_);
	lightManager_->Draw(*camera_);
}

void LiveEditor::WriteScreen()
{
	outline2_->PreDrawScene();
	idolManager_->Draw(*screenCamera_.get());
	outline2_->PostDrawScene();

	screenManager_->PreDrawScene();
	dome_->Draw(*screenCamera_.get());
	floor_->Draw(*screenCamera_.get());
	outline2_->Draw(*screenCamera_.get());
	lightManager_->Draw(*screenCamera_.get());
	screenManager_->PostDrawScene();
}

void LiveEditor::WriteOutline()
{
	outline_->PreDrawScene();
	screenManager_->Draw(*camera_);
	idolManager_->Draw(*camera_);
	outline_->PostDrawScene();
}
