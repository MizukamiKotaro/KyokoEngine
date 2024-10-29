#include "ObjectEditor.h"
#include "Camera.h"
#include "TextureManager.h"
#include "InstancingModelManager.h"
#include "ModelDataManager.h"

ObjectEditor::ObjectEditor(const std::string& mainName, const std::string& name, const uint32_t& no)
{
	CreateStageEditor(mainName, name, no);
	modelName_ = "boxShine";
	modelData_ = ModelDataManager::GetInstance()->LoadObj("boxShine");

	position_ = {};
	scale_ = { 1.0f,1.0f,1.0f };
	rotate_ = {};
	color_ = { 1.0f,1.0f,1.0f,1.0f };
	isBloom_ = true;
	isOutLine_ = false;
	SetGlobalVariable();
}

void ObjectEditor::Initialize()
{
}

void ObjectEditor::Update(const float& time)
{
#ifdef _DEBUG
	UpdateGlobalVariable();
#endif // _DEBUG
	time;
	AddInstancing();
}

void ObjectEditor::Draw(const Camera& camera)
{
	camera;
}

void ObjectEditor::SetGlobalVariable()
{
	stageEditor_->AddItem("位置", position_);
	stageEditor_->AddItem("スケール", scale_);
	stageEditor_->AddItem("回転", rotate_);
	stageEditor_->AddItem("ブルームするか", isBloom_);
	stageEditor_->AddItem("アウトラインするか", isOutLine_);
	stageEditor_->AddItemColor("色", Vector4{ 1.0f,1.0f,1.0f,1.0f });
	stageEditor_->AddItemCombo("モデル", ComboNameType::kOBJ);
	ApplyGlobalVariable();
}

void ObjectEditor::ApplyGlobalVariable()
{
	position_ = stageEditor_->GetVector3Value("位置");
	scale_ = stageEditor_->GetVector3Value("スケール");
	rotate_ = stageEditor_->GetVector3Value("回転");
	isBloom_ = stageEditor_->GetBoolValue("ブルームするか");
	isOutLine_ = stageEditor_->GetBoolValue("アウトラインするか");
	color_ = stageEditor_->GetColor("色");
	std::string name = modelName_;
	modelName_ = stageEditor_->GetCombo("モデル", ComboNameType::kOBJ);
	if (name != modelName_) {
		modelData_ = ModelDataManager::GetInstance()->LoadObj(modelName_);
	}
}

void ObjectEditor::AddInstancing()
{
	Matrix4x4 matrix = Matrix4x4::MakeAffinMatrix(scale_, rotate_, position_);
	if (!isBloom_ && !isOutLine_) {
		instancingData_ = GetInstancingData("normal");
		instancingManager_->AddBox(instancingData_, InstancingModelData{ matrix, Matrix4x4::MakeIdentity4x4() , color_ });
	}
	if (isOutLine_) {
		instancingData_ = GetInstancingData("outline");
		instancingManager_->AddBox(instancingData_, InstancingModelData{ matrix, Matrix4x4::MakeIdentity4x4() , color_ });
	}
	if (isBloom_) {
		instancingData_ = GetInstancingData("bloom");
		instancingManager_->AddBox(instancingData_, InstancingModelData{ matrix, Matrix4x4::MakeIdentity4x4() , color_ });
	}
}

const InstancingMeshTexData* ObjectEditor::GetInstancingData(const std::string& tag)
{
	return instancingManager_->GetDrawData(InstancingMeshTexData{ tag, modelData_, modelData_->texture,BlendMode::kBlendModeNormal });
}
