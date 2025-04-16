#include "FadeBase.h"

TextureManager* FadeBase::textureManager_;
ModelDataManager* FadeBase::modelDataManager_;
FrameInfo* FadeBase::frameInfo_;

void FadeBase::StaticInitialize()
{
	textureManager_ = TextureManager::GetInstance();
	modelDataManager_ = ModelDataManager::GetInstance();
	frameInfo_ = FrameInfo::GetInstance();
}

bool FadeBase::IsFinishFade()
{
	return transitionTimeCount_ >= transitionTime_;
}

void FadeBase::SetTransitionTime(float time)
{
	transitionTime_ = time;
}

void FadeBase::CreateGlobal(const std::string& name, bool isFadeIn)
{
	if (isFadeIn) {
		global_ = std::make_unique<GlobalVariableUser>("Transition", "FadeIn", name);
	}
	else {
		global_ = std::make_unique<GlobalVariableUser>("Transition", "FadeOut", name);
	}
}
