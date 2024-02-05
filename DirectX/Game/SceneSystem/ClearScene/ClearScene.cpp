#include "ClearScene.h"
#include "Kyoko.h"

ClearScene::ClearScene()
{
	FirstInit();


}

void ClearScene::Initialize()
{
	
}

void ClearScene::Update()
{
	


	if ((input_->PressedKey(DIK_RETURN) || input_->PressedGamePadButton(Input::GamePadButton::A))) {
		// シーン切り替え
		ChangeScene(SELECT);
		
	}
}

void ClearScene::Draw()
{
	

	Kyoko::Engine::PreDraw();

	

	BlackDraw();

	Kyoko::Engine::PostDraw();
}


