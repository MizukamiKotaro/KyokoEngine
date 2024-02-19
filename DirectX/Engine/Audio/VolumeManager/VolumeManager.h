#pragma once
#include <list>
#include <string>
#include <memory>

class Audio;
enum class AudioType;
class GlobalVariables;

class VolumeManager
{
public:
	static VolumeManager* GetInstance();

	void Initialize();

	void Clear();

	void SetAudio(Audio* audio);

	void Update();

	const float GetSEVolume() const { return seVolume_; }
	const float GetMusicVolume() const { return musicVolume_; }

private:
	VolumeManager() = default;
	~VolumeManager() = default;
	VolumeManager(const VolumeManager&) = delete;
	const VolumeManager& operator=(const VolumeManager&) = delete;

	std::list<std::unique_ptr<Audio>> audioList_;
	GlobalVariables* globalVariables_ = nullptr;
	
	float seVolume_ = 0.7f;
	float musicVolume_ = 0.7f;
};