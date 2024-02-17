#pragma once

#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include <wrl.h>
#include <string>
#include <vector>
#include <memory>
#include <list>
#include <unordered_map>

class AudioManager
{
public:
	struct ChunkHeader {
		char id[4];
		int32_t size;
	};

	struct RiffHeader {
		ChunkHeader chunk;
		char type[4];
	};

	struct FormatChunk {
		ChunkHeader chunk;
		WAVEFORMATEX fmt;
	};

	// 音声データ
	struct SoundData {
		// 波形フォーマット
		WAVEFORMATEX wfex;
		// バッファ
		std::vector<BYTE> pBuffer;
		std::string name;
		unsigned int bufferSize;
	};

	struct Voice {
		uint32_t handle = 0u;
		IXAudio2SourceVoice* sourceVoice = nullptr;
	};

	static AudioManager* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	void Update();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	uint32_t LoadWave(const std::string& filename);

	uint32_t Play(uint32_t soundDataHandle, bool loopFlag = false, float volume = 1.0f);

	void Stop(uint32_t voiceHandle);

	bool IsPlaying(uint32_t voiceHandle);

	void Pause(uint32_t voiceHandle);

	void ReStart(uint32_t voiceHandle);

	void SetVolume(uint32_t voiceHandle, float volume);

private:
	void Unload(SoundData* soundData);
	void DestroyVoice(uint32_t handle);
	Voice* FindUnusedVoice();
	SoundData* FindSoundData(uint32_t handle);

private:
	AudioManager() = default;
	~AudioManager() = default;
	AudioManager(const AudioManager&) = delete;
	const AudioManager& operator=(const AudioManager&) = delete;

	Microsoft::WRL::ComPtr<IXAudio2> xAudio2_;
	IXAudio2MasteringVoice* masterVoice_ = nullptr;

	std::unordered_map<uint32_t, std::unique_ptr<SoundData>> soundDataMap_;
	std::list<std::unique_ptr<Voice>> voices_;

	const std::string directoryPath_ = "Resources/Audio/";
};