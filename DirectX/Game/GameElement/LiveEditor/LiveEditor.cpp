#include "LiveEditor.h"
#include "Camera.h"
#include "GameElement/BaseStageObject/StageObjectConfig.h"
#include "GameElement/BaseStageObject/StageObjectFactory/StageObjectFactory.h"
#include "ScreenEditor/ScreenEditor.h"
#include "ParticleManager.h"
#include "InstancingModelManager.h"
#include "ImGuiManager/ImGuiManager.h"
#include "SceneSystem/SceneBase/SceneBase.h"

LiveEditor::LiveEditor(Camera* camera)
{
	BaseStageObject::StaticInitialize();

	camera_ = camera;
	camera_->Initialize();
	
	screenCamera_ = std::make_unique<Camera>();
	lightAndOutline_ = std::make_unique<SpotLightAndOutline>();

	screenManager_ = std::make_unique<MultipleScreenEditor>("スクリーン", "マルチスクリーン", 0);

	// マネージャーの設定
	for (std::unique_ptr<StageObjectManager>& manager : objectManagers_) {
		manager = std::make_unique<StageObjectManager>();
	}
	objectManagers_[ManagerNames::kIdol]->AddType(StageObjectType::IDOL, "アイドル", "メインアイドル");
	objectManagers_[ManagerNames::kLight]->AddType(StageObjectType::SPOTLIGHT, "ライト", "スポットライト");
	objectManagers_[ManagerNames::kLight]->AddType(StageObjectType::TWIN_SPOTLIGHT, "ライト", "ツインスポットライト");
	objectManagers_[ManagerNames::kObject]->AddType(StageObjectType::OBJECT, "オブジェクト", "オブジェクト");
	objectManagers_[ManagerNames::kObject]->AddType(StageObjectType::PEN_LIGHT, "ペンライト", "ペンライト");

	screenMap_ = screenManager_->GetScreenMap();
	lightAndOutlineMap_ = screenManager_->GetOutlineMap();

	instancingManager_ = InstancingModelManager::GetInstance();

	cameraAnim_ = std::make_unique<CameraVMDAnimation>("kisekisaemo");
	cameraAnim_->Initialize();

	debugTime_ = 0.0f;
	preDebugTime_ = 0.0f;

	isDebug_ = false;
}

void LiveEditor::Initialize()
{
	cameraAnim_->Initialize();
	camera_->Initialize();
	camera_->transform_.translate_ = { 0.0f,25.0f,-100.0f };
	camera_->transform_.rotate_.x = 0.1f;
	if (SceneBase::GetSceneNo() == SCENE::STAGE) {
		// ステージジーンの場合
		camera_->transform_.translate_ = cameraAnim_->GetState().position;
		camera_->transform_.rotate_ = cameraAnim_->GetState().rotation;
		isDebug_ = false;
	}
	else {
		isDebug_ = true;
	}
	camera_->Update();

	screenCamera_->transform_.translate_ = { 0.0f,15.0f,-80.0f };
	screenCamera_->Update();

	for (std::unique_ptr<StageObjectManager>& manager : objectManagers_) {
		manager->Initialize();
	}

	debugTime_ = 0.0f;
	preDebugTime_ = 0.0f;
}

void LiveEditor::Update(float time)
{
#ifdef _DEBUG
	// デバッグ
	if (SceneBase::GetSceneNo() == SCENE::STAGE_EDITOR) {
		preDebugTime_ = debugTime_;
		ImGui::Begin("debug");
		ImGui::DragFloat("タイム", &debugTime_, 0.01f, 0.0f);
		if (ImGui::Button("Start")) {
			isDebug_ = false;
			camera_->StopDebug();
		}
		if (ImGui::Button("Stop")) {
			isDebug_ = true;
		}
		ImGui::End();
	}

	if (isDebug_) {
		// デバッグタイムのセット
		cameraAnim_->SetTime(debugTime_);
		cameraAnim_->Update(0.0f);
		camera_->DebugUpdate();
		for (std::unique_ptr<StageObjectManager>& manager : objectManagers_) {
			manager->SetTime(debugTime_);
			manager->Update(0.0f);
		}
	}
	else {
		// 更新
		cameraAnim_->Update(time);
		debugTime_ += time;
		for (std::unique_ptr<StageObjectManager>& manager : objectManagers_) {
			manager->Update(time);
		}
	}

	if (!camera_->GetIsDebug()) {
		camera_->transform_.translate_ = cameraAnim_->GetState().position;
		camera_->transform_.rotate_ = cameraAnim_->GetState().rotation;
	}
	// _DEBUG
#else
	// Release
	cameraAnim_->Update(time);
	camera_->transform_.translate_ = cameraAnim_->GetState().position;
	camera_->transform_.rotate_ = cameraAnim_->GetState().rotation;
	for (std::unique_ptr<StageObjectManager>& manager : objectManagers_) {
		manager->Update(time);
	}
#endif 
	camera_->Update();
	screenManager_->Update(time);

	WriteScreen();
	WriteOutline();
}

void LiveEditor::Draw()
{
	lightAndOutline_->Draw(*camera_);
}

void LiveEditor::WriteScreen()
{
	for (uint32_t i = 0; i < screenManager_->GetScreenNum(); i++) {
		const Camera& camera = (*screenMap_)[i]->GetCamera();
		Draw((*lightAndOutlineMap_)[i], camera);
		// スクリーンに書き込む
		(*screenMap_)[i]->PreDrawScene();
		(*lightAndOutlineMap_)[i]->Draw(camera);
		(*screenMap_)[i]->PostDrawScene();
	}
}

void LiveEditor::WriteOutline()
{
	Draw(lightAndOutline_, *camera_);
}

void LiveEditor::Draw(std::unique_ptr<SpotLightAndOutline>& lightAndOutline, const Camera& camera)
{
	// ブルーム用
	lightAndOutline->PreDrawBloom();
	instancingManager_->Draw(camera, "bloom");
	lightAndOutline->PostDrawBloom();

	// ライト用
	lightAndOutline->PreDrawLight();
	objectManagers_[ManagerNames::kLight]->DrawLight(camera);
	lightAndOutline->PostDrawLight();

	// そのまま用
	lightAndOutline->PreDrawObject();
	screenManager_->Draw(camera);
	instancingManager_->Draw(camera);
	lightAndOutline->PostDrawObject();

	// アウトライン用
	lightAndOutline->PreDrawOutline();
	objectManagers_[ManagerNames::kIdol]->Draw(camera);
	instancingManager_->Draw(camera, "outline");
	lightAndOutline->PostDrawOutline();
}
