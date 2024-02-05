#include "SceneManager.h"

#include "Kyoko.h"
#include "Input.h"
#include "FrameInfo/FrameInfo.h"
#include "ImGuiManager/ImGuiManager.h"
#include "GameElement/ScoreManager/ScoreManager.h"
#include "SceneSystem/SceneFactory/SceneFactory.h"

SceneManager::SceneManager()
{
	ScoreManager::GetInstance()->Initialize();

	IScene::sceneNo_ = SELECT;

	sceneFactory_ = std::make_unique<SceneFactory>();

	scene_.reset(sceneFactory_->CreateScene(IScene::sceneNo_));

	currentSceneNo_ = IScene::sceneNo_;
	preSceneNo_ = currentSceneNo_;
	IScene::stageNo_ = 0;

	scene_->Initialize();

	inputManager_ = Input::GetInstance();
}

int SceneManager::Run()
{
	// ウィンドウの×ボタンが押されるまでループ
	while (true) {
		// フレームの開始
		if (Kyoko::Engine::ProcessMessage() || (inputManager_->PressedKey(DIK_ESCAPE) && IScene::sceneNo_ == TITLE)) {
			break;
		}

		Kyoko::Engine::FirstUpdateInLoop();

		// 更新処理
		preSceneNo_ = currentSceneNo_;
		currentSceneNo_ = IScene::sceneNo_;

		if (preSceneNo_ != currentSceneNo_) {
			scene_.reset(sceneFactory_->CreateScene(IScene::sceneNo_));
			scene_->Initialize();
		}

		scene_->Play();

#ifdef _DEBUG
		ImGui::Begin("シーン切り替え");
		ImGui::Text("スプライトとパーティクル ： キーボードの1 or ゲームパッドのX");
		ImGui::Text("モデルとライト ： キーボードの2 or ゲームパッドのY");
		ImGui::Text("ポストエフェクト ： キーボードの3 or ゲームパッドのB");
		ImGui::End();
#endif // _DEBUG
		
		scene_->Draw();

		FrameInfo::GetInstance()->End();
	}

	scene_.reset();
	sceneFactory_.reset();

	return 0;
}