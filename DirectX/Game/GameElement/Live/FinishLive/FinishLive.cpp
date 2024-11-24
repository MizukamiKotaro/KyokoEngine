#include "FinishLive.h"
#include "Audio.h"

FinishLive::FinishLive()
{
	se_ = std::make_unique<Audio>();
	se_->Load("finish.mp3", "ライブ終わりの歓声");
}

void FinishLive::Initialize()
{
	finishCount_ = 0.0f;
	isClear_ = false;
	isFinish_ = false;
}

void FinishLive::Update(float deltaTime)
{
	finishCount_ += deltaTime;
	if (!isFinish_) {
		// 一度SEを鳴らす
		isFinish_ = true;
		se_->Play();
	}
	if (finishCount_ >= 0.75f) {
		isClear_ = true;
	}
}