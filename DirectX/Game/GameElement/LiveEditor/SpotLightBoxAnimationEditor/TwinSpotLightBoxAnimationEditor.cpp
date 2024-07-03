#include "TwinSpotLightBoxAnimationEditor.h"
#include "Camera.h"
#include "SpotLightBoxAnimationEditor.h"

TwinSpotLightBoxAnimationEditor::TwinSpotLightBoxAnimationEditor(const std::string& mainName, const std::string& name, const uint32_t& no)
{
	lights_[0] = std::make_unique<SpotLightBoxAnimationEditor>();
	lights_[1] = std::make_unique<SpotLightBoxAnimationEditor>();
	CreateStageEditor(mainName, name, no, true);
	SetGlobalVariable();
}

void TwinSpotLightBoxAnimationEditor::Update(const float& time)
{
#ifdef _DEBUG
	UpdateGlobalVariable();
#endif // _DEBUG

	*lights_[1]->spotLights_[0]->light_ = *lights_[0]->spotLights_[0]->light_;
	lights_[1]->spotLights_[0]->light_->direction.x *= -1;
	lights_[1]->box_->transform_ = lights_[0]->box_->transform_;
	lights_[1]->box_->transform_.translate_.x *= -1;

	lights_[0]->Update(time);
	lights_[1]->Update(-time);
}

void TwinSpotLightBoxAnimationEditor::Draw(const Camera& camera)
{
	lights_[0]->Draw(camera);
	lights_[1]->Draw(camera);
}

void TwinSpotLightBoxAnimationEditor::SetGlobalVariable()
{
	ApplyGlobalVariable();
}

void TwinSpotLightBoxAnimationEditor::ApplyGlobalVariable()
{
}
