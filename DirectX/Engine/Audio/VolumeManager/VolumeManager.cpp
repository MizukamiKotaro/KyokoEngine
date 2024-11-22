#include "VolumeManager.h"
#include "Audio.h"
#include "AudioConfig.h"
#include "GlobalVariables/GlobalVariableUser.h"
#include <algorithm>

VolumeManager* VolumeManager::GetInstance()
{
	static VolumeManager instance;
	return &instance;
}

void VolumeManager::Initialize()
{
	// 初期化
	seVolume_ = kDefalutVolume;
	musicVolume_ = kDefalutVolume;

	// グローバル変数の設定
	globalVariables_ = std::make_unique<GlobalVariableUser>("Audio", "Volume", "Master");
	globalVariables_->AddItem("SE全体のボリューム", seVolume_);
	globalVariables_->AddItem("Music全体のボリューム", musicVolume_);

	globalVariables_->AddItemDontTouchImGui("SE全体のプレイヤー設定", seVolumeStage_);
	globalVariables_->AddItemDontTouchImGui("Music全体のプレイヤー設定", musicVolumeStage_);

	// 音量の取得
	seVolume_ = globalVariables_->GetFloatValue("SE全体のボリューム");
	musicVolume_ = globalVariables_->GetFloatValue("Music全体のボリューム");

	ResetVolumeStage();
}

void VolumeManager::Clear()
{
	audioMap_.clear();
}

void VolumeManager::SetAudio(const Audio* audio)
{
	if (audioMap_.find(audio->GetItemName()) == audioMap_.end()) {
		audioMap_[audio->GetItemName()] = std::make_unique<Audio>(*audio);
	}
}

void VolumeManager::Update()
{
#ifdef _DEBUG
	// 音量の取得
	seVolume_ = globalVariables_->GetFloatValue("SE全体のボリューム");
	musicVolume_ = globalVariables_->GetFloatValue("Music全体のボリューム");
	seVolume_ = std::clamp(seVolume_, 0.0f, 1.0f);
	musicVolume_ = std::clamp(musicVolume_, 0.0f, 1.0f);

	for (std::pair<const std::string, std::unique_ptr<Audio>>& audio : audioMap_) {
		audio.second->Update();
	}
#endif // _DEBUG
}

void VolumeManager::ResetDefalutVolumeStage()
{
	seVolumeStage_ = kDefalutVolume;
	musicVolumeStage_ = kDefalutVolume;
}

void VolumeManager::ResetVolumeStage()
{
	seVolumeStage_ = globalVariables_->GetFloatValueDontTouchImGui("SE全体のプレイヤー設定");
	musicVolumeStage_ = globalVariables_->GetFloatValueDontTouchImGui("Music全体のプレイヤー設定");
}

void VolumeManager::SaveVolumeStage(float seVolumeStage, float musicVolumeStage)
{
	seVolumeStage_ = seVolumeStage;
	musicVolumeStage_ = musicVolumeStage;
	globalVariables_->SaveDontTouchImGui("SE全体のプレイヤー設定", seVolumeStage_);
	globalVariables_->SaveDontTouchImGui("Music全体のプレイヤー設定", musicVolumeStage_);
}
