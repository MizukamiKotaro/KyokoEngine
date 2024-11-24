#include "LiveMusics.h"
#include "SceneSystem/SceneBase/SceneBase.h"

LiveMusics::LiveMusics()
{
	music_ = std::make_unique<Audio>();
}

void LiveMusics::Initialize() 
{
	if (music_->IsPlaying()) {
		music_->Stop();
	}
	// 読み込み
	switch (SceneBase::GetStageNo())
	{
	case STAGE::SHINING_STAR:
		music_->Load("maou_short_14_shining_star.mp3", "シャイニングスター");
		break;
	default:
		break;
	}
	isMusicStart_ = false;
	isMusicFinish_ = false;
}

void LiveMusics::Update() 
{
	if (!isMusicStart_) {
		// プレイ
		isMusicStart_ = true;
		music_->Play();
	}
	if (!music_->IsPlaying()) {
		isMusicFinish_ = true;
	}
}
