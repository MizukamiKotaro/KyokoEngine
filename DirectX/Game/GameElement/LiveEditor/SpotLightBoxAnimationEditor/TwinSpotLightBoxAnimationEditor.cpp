#include "TwinSpotLightBoxAnimationEditor.h"
#include "Camera.h"
#include "SpotLightBoxAnimationEditor.h"

TwinSpotLightBoxAnimationEditor::TwinSpotLightBoxAnimationEditor(const std::string& mainName, const std::string& name, uint32_t no)
{
	lights_[0] = std::make_unique<SpotLightBoxAnimationEditor>(mainName, name, no);
	lights_[1] = std::make_unique<SpotLightBoxAnimationEditor>();
	SetGlobalVariable();
}

void TwinSpotLightBoxAnimationEditor::SetTime(float time)
{
	lights_[0]->SetTime(time);
	lights_[1]->SetTime(-time);
}

void TwinSpotLightBoxAnimationEditor::Update(float time)
{
#ifdef _DEBUG
	UpdateGlobalVariable();
#endif // _DEBUG
	lights_[0]->Update(time);

	*lights_[1]->spotLights_[0]->light_ = *lights_[0]->spotLights_[0]->light_;
	lights_[1]->spotLights_[0]->light_->direction.x *= -1;
	*lights_[1]->spotLights_[1]->light_ = *lights_[0]->spotLights_[1]->light_;
	lights_[1]->spotLights_[1]->light_->direction.x *= -1;
	lights_[1]->box_->transform_ = lights_[0]->box_->transform_;
	lights_[1]->box_->transform_.translate_.x *= -1;
	lights_[1]->box_->transform_.rotate_.y *= -1;
	lights_[1]->box_->transform_.rotate_.z *= -1;

	lights_[1]->Update(-time);
}

void TwinSpotLightBoxAnimationEditor::Draw(const Camera& camera)
{
	lights_[0]->Draw(camera);
	lights_[1]->Draw(camera);
}

void TwinSpotLightBoxAnimationEditor::DrawLight(const Camera& camera)
{
	lights_[0]->DrawLight(camera);
	lights_[1]->DrawLight(camera);
}

void TwinSpotLightBoxAnimationEditor::SetGlobalVariable()
{
}

void TwinSpotLightBoxAnimationEditor::ApplyGlobalVariable()
{
}
