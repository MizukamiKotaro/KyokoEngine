#include "VolumeManager.h"
#include "Audio.h"
#include "AudioConfig.h"
#include <algorithm>
#include "ImGuiManager/ImGuiManager.h"
#include "Audio/AudioManager/AudioManager.h"
#include "SoundData.h"

VolumeManager* VolumeManager::GetInstance()
{
	static VolumeManager instance;
	return &instance;
}

void VolumeManager::Initialize()
{
	seVolume_ = 0.7f;
	musicVolume_ = 0.7f;

	audioManager_ = AudioManager::GetInstance();

	global_ = std::make_unique<GlobalVariableUser>("Audio", "Volume", "Master");

	global_->AddItem("SE全体のボリューム", seVolume_);
	global_->AddItem("Music全体のボリューム", musicVolume_);

	seVolume_ = global_->GetFloatValue("SE全体のボリューム");
	musicVolume_ = global_->GetFloatValue("Music全体のボリューム");
}

void VolumeManager::Clear()
{
	audioMap_.clear();
}

void VolumeManager::SetAudio(Audio* audio)
{
	if (audioMap_.find(audio->GetItemName()) == audioMap_.end()) {
		audioMap_[audio->GetItemName()] = std::make_unique<Audio>(*audio);
	}
}

void VolumeManager::Update()
{
#ifdef _DEBUG
	seVolume_ = global_->GetFloatValue("SE全体のボリューム");
	musicVolume_ = global_->GetFloatValue("Music全体のボリューム");


	if (!ImGui::Begin("Audio", nullptr, ImGuiWindowFlags_MenuBar)) {
		ImGui::End();
	}
	else {
		if (ImGui::BeginMenuBar()) {
			if (ImGui::BeginMenu("音の再生")) {
				if (ImGui::TreeNode("SE")) {
					for (std::pair<const std::string, std::unique_ptr<Audio>>& audio : audioMap_) {
						if (audio.second->GetSoundDataPtr()->type == AudioType::SE) {
							std::string playButtonName = audio.first + "の再生";
							if (ImGui::Button(playButtonName.c_str())) {
								audioManager_->StopSameSounds(audio.second->GetSoundDataPtr());
								audio.second->Play();
							}
							std::string stopButtonName = audio.first + "の停止";
							if (ImGui::Button(stopButtonName.c_str())) {
								audioManager_->StopSameSounds(audio.second->GetSoundDataPtr());
							}
						}
					}

					ImGui::TreePop();
				}
				if (ImGui::TreeNode("MUSIC")) {
					for (std::pair<const std::string, std::unique_ptr<Audio>>& audio : audioMap_) {
						if (audio.second->GetSoundDataPtr()->type == AudioType::MUSIC) {
							std::string playButtonName = audio.first + "の再生";
							if (ImGui::Button(playButtonName.c_str())) {
								audioManager_->StopSameSounds(audio.second->GetSoundDataPtr());
								audio.second->Play();
							}
							std::string stopButtonName = audio.first + "の停止";
							if (ImGui::Button(stopButtonName.c_str())) {
								audioManager_->StopSameSounds(audio.second->GetSoundDataPtr());
							}
						}
					}

					ImGui::TreePop();
				}


				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::End();
	}

	seVolume_ = std::clamp(seVolume_, 0.0f, 1.0f);
	musicVolume_ = std::clamp(musicVolume_, 0.0f, 1.0f);
	for (std::pair<const std::string, std::unique_ptr<Audio>>& audio : audioMap_) {
		audio.second->Update();
	}
#endif // _DEBUG
}