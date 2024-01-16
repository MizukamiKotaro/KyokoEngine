#include "ClearScene.h"
#include "Kyoko.h"

ClearScene::ClearScene()
{
	FirstInit();

	
}

void ClearScene::Init()
{

}

void ClearScene::Update()
{
	if (input_->PressedKey(DIK_RETURN)) {
		// シーン切り替え
		ChangeScene(SELECT);
	}
}

void ClearScene::Draw()
{
	Kyoko::PreDraw();

	

	BlackDraw();

	Kyoko::PostDraw();
}


