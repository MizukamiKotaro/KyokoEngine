#include "DancingIdolEditor.h"
#include "Camera.h"
#include "TextureManager.h"

DancingIdolEditor::DancingIdolEditor(const std::string& mainName, const std::string& name, uint32_t no)
{
	CreateStageEditor(mainName, name, no);
	firstPosition_ = {};
	idol_ = std::make_unique<PMDModel>("lovemiku");
	idol_->transform_.rotate_.y = 3.14f;
	idol_->transform_.scale_ *= 5;
	SetGlobalVariable();
}

void DancingIdolEditor::SetTime(float time)
{
	idol_->SetTime(time);
}

void DancingIdolEditor::Update(float time) 
{
#ifdef _DEBUG
	UpdateGlobalVariable();
#endif // _DEBUG
	idol_->Update(time);
}

void DancingIdolEditor::Draw(const Camera& camera) 
{
	idol_->Draw(camera);
}

void DancingIdolEditor::SetGlobalVariable()
{
	stageEditor_->AddItem("初期座標", firstPosition_);
	stageEditor_->AddItem("スケール", 2.0f);
	ApplyGlobalVariable();
}

void DancingIdolEditor::ApplyGlobalVariable()
{
	Vector3 prePos = firstPosition_;
	firstPosition_ = stageEditor_->GetVector3Value("初期座標");
	float scale = stageEditor_->GetFloatValue("スケール");
	idol_->transform_.scale_ = { scale ,scale ,scale };
	idol_->transform_.UpdateMatrix();
	if (firstPosition_ != prePos) {
		idol_->transform_.translate_ = firstPosition_;
	}
}
