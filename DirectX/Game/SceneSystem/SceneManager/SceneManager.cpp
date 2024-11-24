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

	// 初期化
	SceneBase::StaticInitialize();
	SceneBase::SetSceneNo(SCENE::TITLE);
	currentSceneNo_ = SCENE::TITLE;
	preSceneNo_ = SCENE::TITLE;

	// シーンの作成
	sceneFactory_ = std::make_unique<SceneFactory>();
	scene_.reset(sceneFactory_->CreateScene(SCENE::TITLE));

	input_ = Input::GetInstance();
	frameInfo_ = FrameInfo::GetInstance();
}

int SceneManager::Run()
{
	// 一番最初のタイミングで一度初期化
	scene_->Initialize();

	// ウィンドウの×ボタンが押されるまでループ
	while (true) {
		// ウィンドウが閉じたか、タイトルでescが押されたらループを抜ける
		if (Kyoko::Engine::ProcessMessage() || (input_->PressedKey(DIK_ESCAPE) && currentSceneNo_ == TITLE)) {
			break;
		}
		// エンジンの更新処理
		Kyoko::Engine::FirstUpdateInLoop();

		// 更新処理
		preSceneNo_ = currentSceneNo_;
		currentSceneNo_ = SceneBase::GetSceneNo();
		if (preSceneNo_ != currentSceneNo_) {
			// 新しいシーンの初期化
			scene_.reset(sceneFactory_->CreateScene(currentSceneNo_));
			scene_->Initialize();
			scene_->FirstUpdate();
		}
		scene_->Play();

#ifdef _DEBUG
		// ImGuiで現在のシーン表示
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
		// フレームの表示
		ImGui::Begin("フレーム");
		ImGui::Text("フレーム : %4.1f", frameInfo_->GetFramerate());
		ImGui::End();
#endif // _DEBUG
		
		// 描画処理
		scene_->Draw();

		// フレームの最終処理
		frameInfo_->End();
	}

	// 解放
	scene_.reset();
	sceneFactory_.reset();

	return 0;
}