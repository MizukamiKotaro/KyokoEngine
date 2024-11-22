#include "StageEditorScene.h"
#include "ImGuiManager/ImGuiManager.h"
#include "Kyoko.h"

StageEditorScene::StageEditorScene()
{
	FirstInitialize();

	liveEditor_ = std::make_unique<LiveEditor>(camera_.get());
}

void StageEditorScene::Initialize()
{
	liveEditor_->Initialize();
}

void StageEditorScene::Update()
{
#ifdef _DEBUG
	if (input_->PressedKey(DIK_SPACE) || input_->PressedKey(DIK_S)) {
		// シーン切り替え
		ChangeScene(STAGE);
	}
	else if (input_->PressedKey(DIK_T)) {
		// シーン切り替え
		ChangeScene(TITLE);
	}
#endif // _DEBUG

	liveEditor_->Update(frameInfo_->GetDeltaTime());
}

void StageEditorScene::Draw()
{
	Kyoko::Engine::PreDraw();

	liveEditor_->Draw();

	TransitionDraw();

	// フレームの終了
	Kyoko::Engine::PostDraw();
}

void StageEditorScene::FirstUpdate()
{
	liveEditor_->Update(0.001f);
}

