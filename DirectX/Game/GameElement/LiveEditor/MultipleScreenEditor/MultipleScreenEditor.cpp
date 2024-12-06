#include "MultipleScreenEditor.h"
#include "Camera.h"
#include "TextureManager.h"
#include "GameElement/LiveEditor/ScreenEditor/ScreenEditor.h"
#include "WindowsInfo/WindowsInfo.h"

MultipleScreenEditor::MultipleScreenEditor(const std::string& mainName, const std::string& name, uint32_t no)
{
	CreateStageEditor(mainName, name, no);
	treeName = std::make_unique<TreeNames>(mainName, name, mainName + std::to_string(no));
	screenNum_ = 1;
	CreateScreen();
	SetGlobalVariable();
}

void MultipleScreenEditor::Update(float time)
{
#ifdef _DEBUG
	UpdateGlobalVariable();
	for (uint32_t i = 0; i < screenNum_; i++) {
		screenMap_[i]->Update(time);
	}
#endif // _DEBUG
	time;
}

void MultipleScreenEditor::Draw(const Camera& camera)
{
	for (uint32_t i = 0; i < screenNum_; i++) {
		screenMap_[i]->Draw(camera);
	}
}

void MultipleScreenEditor::SetGlobalVariable()
{
	stageEditor_->AddItem("スクリーンの数", 1);
	ApplyGlobalVariable();
}

void MultipleScreenEditor::ApplyGlobalVariable()
{
	uint32_t preNum = screenNum_;
	screenNum_ = stageEditor_->GetIntValue("スクリーンの数");
	if (screenNum_ <= 0) {
		screenNum_ = 1;
	}
	if (preNum != screenNum_) {
		CreateScreen();
	}
}

void MultipleScreenEditor::CreateScreen()
{
	Vector2 size = WindowsInfo::GetInstance()->GetWindowSize() * 0.5f;
	for (uint32_t i = 0; i < screenNum_; i++) {
		if (screenMap_.find(i) == screenMap_.end()) {
			// なかったら作る
			screenMap_[i] = std::make_unique<ScreenEditor>(treeName->main, treeName->name, treeName->tree, i);
			if (i == 0) {
				// 1つ目なら作成
				lightAndOutlineMap_[i] = std::make_unique<SpotLightAndOutline>(size);
			}
			else {
				// 同じのを描画するようにハンドルを渡す
				screenMap_[i]->SetGPUHandle(screenMap_[0]->GetGPUHandle());
			}
		}
	}
}
