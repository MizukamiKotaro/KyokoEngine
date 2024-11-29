#include "PenLightEditor.h"
#include "Camera.h"
#include "InstancingModelManager.h"

const int kSpotNum = 2;

PenLightEditor::PenLightEditor(const std::string& mainName, const std::string& name, uint32_t no)
{
	box_ = std::make_unique<RigidAnimationModel>("penLight");
	isTwin_ = true;
	distance_ = 7.0f;
	num_ = 10;
	color_ = { 1.0f,1.0f,1.0f,1.0f };
	angle_ = {};
	length_ = 50.0f;
	y_ = -1.5f;
	n_ = 1;
	scale_ = { 5.0f,5.0f,5.0f };
	
	CreateStageEditor(mainName, name, no, true);
	SetGlobalVariable();
	MakeInstancingData();
}

void PenLightEditor::SetTime(float time)
{
	box_->SetTime(time);
}

void PenLightEditor::Update(float time)
{
#ifdef _DEBUG
	UpdateGlobalVariable();
#endif // _DEBUG
	box_->Update(time);
	AddInstancing();
}

void PenLightEditor::Draw(const Camera& camera)
{
	box_->Draw(camera);
}

void PenLightEditor::SetGlobalVariable()
{
	stageEditor_->AddItem("向き", angle_.y);
	stageEditor_->AddItem("幅", distance_);
	stageEditor_->AddItem("距離", length_);
	stageEditor_->AddItem("高さ", y_);
	stageEditor_->AddItem("数", num_);
	stageEditor_->AddItem("横の数", n_);
	stageEditor_->AddItemColor("色", color_);

	ApplyGlobalVariable();
}

void PenLightEditor::ApplyGlobalVariable()
{
	num_ = stageEditor_->GetIntValue("数");
	n_ = stageEditor_->GetIntValue("横の数");
	color_ = stageEditor_->GetColor("色");
	distance_ = stageEditor_->GetFloatValue("幅");
	angle_.y = stageEditor_->GetFloatValue("向き");
	length_ = stageEditor_->GetFloatValue("距離");
	y_ = stageEditor_->GetFloatValue("高さ");
}

void PenLightEditor::MakeInstancingData()
{
	instancingData_ = instancingManager_->GetDrawData(InstancingGroupData{ "bloom", &box_->GetModelData(), box_->GetModelData().texture,BlendMode::kBlendModeNormal });
}

void PenLightEditor::AddInstancing()
{
	float length = length_;
	Vector3 pos;
	Vector3 angle = {};
	for (int32_t n = 0; n < n_; n++) {
		angle.y += angle_.y;
		length = length_;
		for (int32_t i = 0; i < num_; i++) {
			pos.x = length * std::sinf(angle.y);
			pos.y = y_;
			pos.z = -length * std::cosf(angle.y);
			Matrix4x4 mat = Matrix4x4::MakeAffinMatrix(scale_, angle, pos);
			Matrix4x4 matrix = box_->GetAnimTransform().matrix_ * mat;
			instancingManager_->AddInstanceTransform(instancingData_, InstancingModelData{ matrix, Matrix4x4::MakeIdentity4x4() , color_ });
			length += distance_;
		}
	}
}
