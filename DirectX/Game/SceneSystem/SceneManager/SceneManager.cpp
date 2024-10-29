#include "SceneManager.h"
#include "Kyoko.h"
#include "Input.h"
#include "FrameInfo/FrameInfo.h"
#include "ImGuiManager/ImGuiManager.h"
#include "GameElement/ScoreManager/ScoreManager.h"
#include "SceneSystem/SceneFactory/SceneFactory.h"

SceneManager::SceneManager()
{
	// スコアの初期化
	ScoreManager::GetInstance()->Initialize();

	// タイトルシーンから
	IScene::SetSceneNo(TITLE);

	// シーンの作成
	sceneFactory_ = std::make_unique<SceneFactory>();
	scene_.reset(sceneFactory_->CreateScene(IScene::GetSceneNo()));


	currentSceneNo_ = IScene::GetSceneNo();
	preSceneNo_ = currentSceneNo_;
	IScene::SetStageNo(0);

	input_ = Input::GetInstance();
	frameInfo_ = FrameInfo::GetInstance();
}

int SceneManager::Run()
{
	scene_->Initialize();

	// ウィンドウの×ボタンが押されるまでループ
	while (true) {
		// フレームの開始
		int32_t sceneNo = IScene::GetSceneNo();
		if (Kyoko::Engine::ProcessMessage() || (input_->PressedKey(DIK_ESCAPE) && sceneNo == TITLE)) {
			break;
		}

		Kyoko::Engine::FirstUpdateInLoop();

		// 更新処理
		preSceneNo_ = currentSceneNo_;
		currentSceneNo_ = sceneNo;

		if (preSceneNo_ != currentSceneNo_) {
			scene_.reset(sceneFactory_->CreateScene(sceneNo));
			scene_->Initialize();
			scene_->FirstUpdate();
		}

		scene_->Play();

#ifdef _DEBUG
		ImGui::Begin("SCENE");
		switch (currentSceneNo_)
		{
		case SCENE::TITLE:
			ImGui::Text("TITLE");
			break;
		case SCENE::SELECT:
			ImGui::Text("SELECT");
			break;
		case SCENE::STAGE:
			ImGui::Text("STAGE");
			break;
		case SCENE::STAGE_EDITOR:
			ImGui::Text("STAGE_EDITOR");
			break;
		case SCENE::CLEAR:
			ImGui::Text("CLEAR");
			break;
		default:
			break;
		}
		ImGui::End();
		ImGui::Begin("フレーム");
		ImGui::Text("フレーム : %4.1f", frameInfo_->GetFramerate());
		ImGui::End();
#endif // _DEBUG
		
		// 描画処理
		scene_->Draw();

		frameInfo_->End();
	}

	scene_.reset();
	sceneFactory_.reset();

	return 0;
}