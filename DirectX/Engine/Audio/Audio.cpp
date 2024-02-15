#include "Audio.h"
#include "AudioManager/AudioManager.h"

AudioManager* Audio::audioManager_ = nullptr;

void Audio::StaticInitialize()
{
	audioManager_ = AudioManager::GetInstance();
}

void Audio::LoadWave(const std::string& filename)
{
	soundHandle_ = audioManager_->LoadWave(filename);
}

void Audio::Play(float volume, bool isLoop)
{
	voiseHandle_ = audioManager_->Play(soundHandle_, isLoop, volume);
}

void Audio::Stop() const
{
	audioManager_->Stop(voiseHandle_);
}

bool Audio::IsPlaying() const
{
	return audioManager_->IsPlaying(voiseHandle_);
}

void Audio::Pause() const
{
	audioManager_->Pause(voiseHandle_);
}

void Audio::ReStart() const
{
	audioManager_->ReStart(voiseHandle_);
}

void Audio::SetVolume(float volume) const
{
	audioManager_->SetVolume(voiseHandle_, volume);
}