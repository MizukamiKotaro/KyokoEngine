#pragma once
#include <stdint.h>
#include <string>

class AudioManager;
class SoundData;
class GlobalVariables;
class VolumeManager;

class Audio
{
public:
	static void StaticInitialize();

	void LoadWave(const std::string& filename, const std::string& itemName = "_", float volume = 0.7f);

	void Play(bool isLoop = false);

	void Stop() const;

	bool IsPlaying() const;

	void Pause() const;

	void ReStart() const;

	void Update();

private:
	const SoundData* soundData_;
	uint32_t voiceHandle_;
	float volume_;
	std::string itemName_;

	static AudioManager* audioManager_;
	static VolumeManager* volumeManager_;
	static GlobalVariables* globalVariables_;
};