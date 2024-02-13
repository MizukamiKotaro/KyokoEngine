#pragma once
#include <stdint.h>
#include <string>

class AudioManager;

class Audio
{
public:

	static void StaticInitialize();

	void LoadWave(const std::string& filename);

	void Play(float volume = 0.5f, bool isLoop = false);

	void Stop() const;

	bool IsPlaying() const;

	void Pause() const;

	void ReStart() const;

	void SetVolume(float volume) const;

private:
	uint32_t soundHandle_;
	uint32_t voiseHandle_;

	static AudioManager* audioManager_;
};