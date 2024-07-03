#include "StageFloorEditor.h"
#include "Camera.h"
#include "TextureManager.h"

StageFloorEditor::StageFloorEditor(const std::string& mainName, const std::string& name, const uint32_t& no)
{
	model_ = std::make_unique<Model>("ground");
	model_->SetTexture(TextureManager::GetInstance()->LoadTexture("Resources/Texture/white.png"));
	model_->Update();
	model_->UnUsedLight();
	model_->SetColor(Vector4{ 0.1f,0.1f,0.1f,1.0f });
	CreateStageEditor(mainName, name, no);
	SetGlobalVariable();
}

void StageFloorEditor::Initialize()
{
}

void StageFloorEditor::Update(const float& time)
{
#ifdef _DEBUG
	UpdateGlobalVariable();
#endif // _DEBUG
	float a = time;
	a = 0;
}

void StageFloorEditor::Draw(const Camera& camera)
{
	model_->Draw(camera);
}

void StageFloorEditor::SetGlobalVariable()
{
	ApplyGlobalVariable();
}

void StageFloorEditor::ApplyGlobalVariable()
{
}
