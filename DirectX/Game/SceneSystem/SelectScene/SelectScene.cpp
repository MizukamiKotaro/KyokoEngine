#include "SelectScene.h"
#include "Kyoko.h"

SelectScene::SelectScene()
{
	FirstInit();


}

void SelectScene::Init()
{

}

void SelectScene::Update()
{
	if (input_->PressedKey(DIK_RETURN)) {
		// シーン切り替え
		stageNo_ = 0;
		ChangeScene(STAGE);
	}
}

void SelectScene::Draw()
{
	Kyoko::PreDraw();

	

	BlackDraw();

	Kyoko::PostDraw();
}

