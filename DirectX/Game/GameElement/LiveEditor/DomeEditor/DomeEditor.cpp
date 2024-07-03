#include "DomeEditor.h"
#include "Camera.h"

DomeEditor::DomeEditor(const std::string& mainName, const std::string& name, const uint32_t& no)
{
	CreateStageEditor(mainName, name, no);
	model_ = std::make_unique<Model>("skydome");
	model_->Update();
	model_->UnUsedLight();
	model_->SetColor(Vector4{ 0.02f,0.02f,0.02f,1.0f });
	SetGlobalVariable();
}

void DomeEditor::Initialize()
{
}

void DomeEditor::Update(const float& time)
{
#ifdef _DEBUG
	UpdateGlobalVariable();
#endif // _DEBUG
	float a = time;
	a = 0;
}

void DomeEditor::Draw(const Camera& camera)
{
	model_->Draw(camera);
}

void DomeEditor::SetGlobalVariable()
{
	stageEditor_->AddItem("スケール", model_->transform_.scale_);
	stageEditor_->AddItem("回転", model_->transform_.rotate_);
	ApplyGlobalVariable();
}

void DomeEditor::ApplyGlobalVariable()
{
	model_->transform_.scale_ = stageEditor_->GetVector3Value("スケール");
	model_->transform_.rotate_ = stageEditor_->GetVector3Value("回転");
	model_->Update();
}
