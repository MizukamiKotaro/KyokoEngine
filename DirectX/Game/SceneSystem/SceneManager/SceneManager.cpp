#include "SceneManager.h"
#include "Kyoko.h"
#include "Input.h"
#include "FrameInfo/FrameInfo.h"
#include "Externals/imgui/imgui.h"
#include "GameElement/ScoreManager/ScoreManager.h"

SceneManager::SceneManager()
{
	ScoreManager::GetInstance()->Initialize();


	sceneArr_[TITLE] = std::make_unique<TitleScene>();
	sceneArr_[SELECT] = std::make_unique<SelectScene>();
	sceneArr_[STAGE] = std::make_unique<StageScene>();
	sceneArr_[CLEAR] = std::make_unique<ClearScene>();

	IScene::sceneNo_ = TITLE;
	//IScene::sceneNo_ = STAGE;
	currentSceneNo_ = IScene::sceneNo_;
	preSceneNo_ = currentSceneNo_;
	IScene::stageNo_ = 0;

	sceneArr_[currentSceneNo_]->Initialize();

}

SceneManager::~SceneManager()
{
}

int SceneManager::Run()
{
	// ウィンドウの×ボタンが押されるまでループ
	while (true) {
		// フレームの開始
		if (Kyoko::ProcessMessage() || (Input::GetInstance()->PressedKey(DIK_ESCAPE) && IScene::sceneNo_ == TITLE)) {
			break;
		}

		Kyoko::FirstUpdateInLoop();

		// 更新処理
		preSceneNo_ = currentSceneNo_;
		currentSceneNo_ = sceneArr_[currentSceneNo_]->GetSceneNo();

		if (preSceneNo_ != currentSceneNo_) {
			sceneArr_[currentSceneNo_]->Initialize();
		}

		sceneArr_[currentSceneNo_]->Play();

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
		
		sceneArr_[currentSceneNo_]->Draw();

		// フレームの終了
		//Kyoko::PostDraw();

		FrameInfo::GetInstance()->End();
	}

	return 0;
}
