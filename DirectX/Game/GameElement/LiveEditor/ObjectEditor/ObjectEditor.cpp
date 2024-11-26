#include "ObjectEditor.h"
#include "Camera.h"
#include "TextureManager.h"
#include "InstancingModelManager.h"
#include "ModelDataManager.h"

ObjectEditor::ObjectEditor(const std::string& mainName, const std::string& name, uint32_t no)
{
	CreateStageEditor(mainName, name, no, true);
	modelName_ = "boxShine";
	modelData_ = ModelDataManager::GetInstance()->LoadObj("boxShine");

	position_ = {};
	scale_ = { 1.0f,1.0f,1.0f };
	rotate_ = {};
	color_ = { 1.0f,1.0f,1.0f,1.0f };
	allScale_ = 1.0f;
	isBloom_ = true;
	isOutLine_ = false;
	isTwin_ = false;
	SetGlobalVariable();
}

void ObjectEditor::Initialize()
{
}

void ObjectEditor::Update(float time)
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
	stageEditor_->AddItem("全スケール", allScale_);
	stageEditor_->AddItem("ブルームするか", isBloom_);
	stageEditor_->AddItem("アウトラインするか", isOutLine_);
	stageEditor_->AddItem("左右対象に作るか", isTwin_);
	stageEditor_->AddItemColor("色", Vector4{ 1.0f,1.0f,1.0f,1.0f });
	stageEditor_->AddItemCombo("モデル", ComboNameType::kOBJ);


	ApplyGlobalVariable();
}

void ObjectEditor::ApplyGlobalVariable()
{
	position_ = stageEditor_->GetVector3Value("位置");
	scale_ = stageEditor_->GetVector3Value("スケール");
	rotate_ = stageEditor_->GetVector3Value("回転");
	allScale_ = stageEditor_->GetFloatValue("全スケール");
	isBloom_ = stageEditor_->GetBoolValue("ブルームするか");
	isOutLine_ = stageEditor_->GetBoolValue("アウトラインするか");
	isTwin_ = stageEditor_->GetBoolValue("左右対象に作るか");
	color_ = stageEditor_->GetColor("色");
	std::string name = modelName_;
	modelName_ = stageEditor_->GetCombo("モデル", ComboNameType::kOBJ);
	if (name != modelName_) {
		modelData_ = ModelDataManager::GetInstance()->LoadObj(modelName_);
	}
}

void ObjectEditor::AddInstancing()
{
	Vector3 scale = scale_ * allScale_;
	Matrix4x4 matrix = Matrix4x4::MakeAffinMatrix(scale, rotate_, position_);
	AddInstancing(matrix);
	if (isTwin_) {
		matrix = Matrix4x4::MakeAffinMatrix(scale, Vector3{ rotate_.x,-rotate_.y,-rotate_.z }, Vector3{ -position_.x,position_.y,position_.z });
		AddInstancing(matrix);
	}
}

void ObjectEditor::AddInstancing(const Matrix4x4& matrix)
{
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

const InstancingGroupData* ObjectEditor::GetInstancingData(const std::string& tag)
{
	return instancingManager_->GetDrawData(InstancingGroupData{ tag, modelData_, modelData_->texture,BlendMode::kBlendModeNormal });
}
