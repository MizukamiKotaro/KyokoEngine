#include "Audio.h"
#include "AudioManager/AudioManager.h"
#include "VolumeManager/VolumeManager.h"
#include "AudioConfig.h"
#include "SoundData.h"
#include <algorithm>
#include "ImGuiManager/ImGuiManager.h"

AudioManager* Audio::audioManager_ = nullptr;
VolumeManager* Audio::volumeManager_ = nullptr;

void Audio::StaticInitialize()
{
	// インスタンスの取得
	audioManager_ = AudioManager::GetInstance();
	volumeManager_ = VolumeManager::GetInstance();
}

Audio::Audio(const Audio& audio)
{
	// 初期化
	soundData_ = audio.soundData_;
	volume_ = audio.volume_;
	itemName_ = audio.itemName_;

	// グローバル変数の名前の設定
	if (soundData_->type == AudioType::SE) {
		global_ = std::make_unique<GlobalVariableUser>("Audio", "Volume", "SE");
	}
	else if (soundData_->type == AudioType::MUSIC) {
		global_ = std::make_unique<GlobalVariableUser>("Audio", "Volume", "Music");
	}

	// グローバル変数の設定と取得
	global_->AddItem(itemName_ + "のボリューム", volume_);
	SetVolume();
}

void Audio::Load(const std::string& filename, const std::string& itemName, float volume)
{
	// 初期化
	soundData_ = audioManager_->Load(filename);
	volume_ = volume;

	// 名前の設定
	if (itemName == "_") {
		itemName_ = filename;
	}
	else {
		itemName_ = itemName;
	}

	// グローバル変数の名前の設定
	if (soundData_->type == AudioType::SE) {
		global_ = std::make_unique<GlobalVariableUser>("Audio", "Volume", "SE");
	}
	else if (soundData_->type == AudioType::MUSIC) {
		global_ = std::make_unique<GlobalVariableUser>("Audio", "Volume", "Music");
	}

	// グローバル変数の設定と取得
	global_->AddItem(itemName_ + "のボリューム", volume_);
	SetVolume();
#ifdef _DEBUG
	// 音量を調整できるようにするため
	volumeManager_->SetAudio(this);
#endif // _DEBUG
}

void Audio::Play(bool isLoop)
{
#ifdef _DEBUG
	SetVolume();
#endif // _DEBUG

	// 全体の音量と乗算
	float volume = volume_;
	if (soundData_->type == AudioType::SE) {
		volume *= volumeManager_->GetSEVolume();
	}
	else if (soundData_->type == AudioType::MUSIC) {
		volume *= volumeManager_->GetMusicVolume();
	}
	// 再生
	voiceHandle_ = audioManager_->Play(soundData_, isLoop, volume);
}

void Audio::Stop() const
{
	audioManager_->Stop(voiceHandle_, soundData_);
}

bool Audio::IsPlaying() const
{
	return audioManager_->IsPlaying(voiceHandle_, soundData_);
}

void Audio::Pause() const
{
	audioManager_->Pause(voiceHandle_, soundData_);
}

void Audio::ReStart() const
{
	audioManager_->ReStart(voiceHandle_, soundData_);
}

void Audio::AllStop()
{
	audioManager_->AllStop();
}

void Audio::Update()
{
#ifdef _DEBUG
	SetVolume();

	// 音の再生ボタンと停止ボタンの設定
	if (!ImGui::Begin("Audio", nullptr, ImGuiWindowFlags_MenuBar)) {
		ImGui::End();
	}
	else {
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("音量再生")) {
				std::string playButtonName = itemName_ + "の再生";
				if (ImGui::Button(playButtonName.c_str())) {
					// 再生
					audioManager_->StopSameSounds(soundData_);
					Play();
				}
				std::string stopButtonName = itemName_ + "の停止";
				if (ImGui::Button(stopButtonName.c_str())) {
					// 停止
					audioManager_->StopSameSounds(soundData_);
				}
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::End();
	}

#endif // _DEBUG
	if (IsPlaying()) {
		// 再生中の音量の設定
		float volume = volume_;
		if (soundData_->type == AudioType::SE) {
			volume *= volumeManager_->GetSEVolume();
		}
		else if (soundData_->type == AudioType::MUSIC) {
			volume *= volumeManager_->GetMusicVolume();
		}
		audioManager_->SetVolume(voiceHandle_, soundData_, volume);
	}
}

const SoundData* Audio::GetSoundDataPtr() const
{
	return soundData_;
}

void Audio::SetVolume()
{
	volume_ = global_->GetFloatValue(itemName_ + "のボリューム");
	volume_ = std::clamp(volume_, 0.0f, 1.0f);
}
