#include "MultipleScreenEditor.h"
#include "Camera.h"
#include "TextureManager.h"
#include "GameElement/LiveEditor/ScreenEditor/ScreenEditor.h"

MultipleScreenEditor::MultipleScreenEditor(const std::string& mainName, const std::string& name, const uint32_t& no)
{
	screenSprite_ = std::make_unique<Sprite>("screen.png");
	screenSprite_->pos_ = { 640.0f,360.0f };
	screenSprite_->Update();

	postEffect_ = std::make_unique<PostEffect>();
	postEffect1_ = std::make_unique<PostEffect>();
	bloom_ = std::make_unique<Bloom>();

	CreateStageEditor(mainName, name, no);
	treeName = std::make_unique<TreeNames>(mainName, name, mainName + std::to_string(no));
	screenNum_ = 1;
	CreateScreen();
	SetGlobalVariable();
}

void MultipleScreenEditor::Update(const float& time)
{
#ifdef _DEBUG
	UpdateGlobalVariable();
	for (uint32_t i = 0; i < screenNum_; i++) {
		screenMap_[i]->Update(time);
	}
#endif // _DEBUG
	float a = time; a = 0;
}

void MultipleScreenEditor::Draw(const Camera& camera)
{
	for (uint32_t i = 0; i < screenNum_; i++) {
		screenMap_[i]->Draw(camera);
	}
}

void MultipleScreenEditor::PreDrawScene()
{
	//bloom_->PreDrawScene();
	postEffect1_->PreDrawScene();
}

void MultipleScreenEditor::PostDrawScene()
{
	//bloom_->PostDrawScene();
	postEffect1_->PostDrawScene();

	postEffect_->PreDrawScene();

	//bloom_->Draw();
	postEffect1_->Draw();
	screenSprite_->Draw(BlendMode::kBlendModeMultiply);

	postEffect_->PostDrawScene();
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
	for (uint32_t i = 0; i < screenNum_; i++) {
		if (screenMap_.find(i) == screenMap_.end()) {
			screenMap_[i] = std::make_unique<ScreenEditor>(treeName->main, treeName->name, treeName->tree, i);
			screenMap_[i]->SetGPUHandle(postEffect_->GetSRVGPUDescriptorHandle());
		}
	}
}