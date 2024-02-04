#include "SceneManager.h"

#include "SceneSystem/IScene/IScene.h"
#include "SceneSystem/TitleScene/TitleScene.h"
#include "SceneSystem/StageScene/StageScene.h"
#include "SceneSystem/ClearScene/ClearScene.h"
#include "SceneSystem/SelectScene/SelectScene.h"
#include "Camera.h"

#include "Kyoko.h"
#include "Input.h"
#include "FrameInfo/FrameInfo.h"
#include "Externals/imgui/imgui.h"
#include "GameElement/ScoreManager/ScoreManager.h"
#include "SceneSystem/SceneFactory/SceneFactory.h"

SceneManager::SceneManager()
{
	ScoreManager::GetInstance()->Initialize();

	IScene::sceneNo_ = TITLE;

	sceneFactory_ = std::make_unique<SceneFactory>();

	scene_.reset(sceneFactory_->CreateScene(IScene::sceneNo_));

	//IScene::sceneNo_ = STAGE;
	currentSceneNo_ = IScene::sceneNo_;
	preSceneNo_ = currentSceneNo_;
	IScene::stageNo_ = 0;

	scene_->Initialize();
}

SceneManager::~SceneManager()
{
}

int SceneManager::Run()
{
	// ウィンドウの×ボタンが押されるまでループ
	while (true) {
		// フレームの開始
		if (Kyoko::Engine::ProcessMessage() || (Input::GetInstance()->PressedKey(DIK_ESCAPE) && IScene::sceneNo_ == TITLE)) {
			break;
		}

		Kyoko::Engine::FirstUpdateInLoop();

		// 更新処理
		preSceneNo_ = currentSceneNo_;
		currentSceneNo_ = scene_->GetSceneNo();

		if (preSceneNo_ != currentSceneNo_) {
			scene_.reset(sceneFactory_->CreateScene(IScene::sceneNo_));
			scene_->Initialize();
		}

		scene_->Play();

#ifdef _DEBUG
		ImGui::Begin("SCENE");
		switch (currentSceneNo_)
		{
		case SCENE::SELECT:
			ImGui::Text("SELECT");
			break;
		case SCENE::TITLE:
			ImGui::Text("TITLE");
			break;
		case SCENE::STAGE:
			ImGui::Text("STAGE");
			break;
		case SCENE::CLEAR:
			ImGui::Text("CLEAR");
			break;
		default:
			break;
		}
		ImGui::End();
#endif // _DEBUG

		//Kyoko::PreDraw();

		// 描画処理ここから
		
		scene_->Draw();

		// フレームの終了
		//Kyoko::PostDraw();

		FrameInfo::GetInstance()->End();
	}

	scene_.reset();
	sceneFactory_.reset();

	return 0;
}
