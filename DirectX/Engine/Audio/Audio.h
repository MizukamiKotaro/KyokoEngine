#pragma once

#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include <wrl.h>
#include <string>
#include <vector>
#include <memory>
#include <array>

class AudioManager
{
public:

	static const int kSoundVoiceMaxNum = 256;

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

	/// <summary>
	/// WAV音声読み込み
	/// </summary>
	/// <param name="filename">WAVファイル名</param>
	/// <returns>サウンドデータハンドル</returns>
	uint32_t LoadWave(const std::string& filename);

	/// <summary>
	/// 音声再生
	/// </summary>
	/// <param name="soundDataHandle">サウンドデータハンドル</param>
	/// <param name="loopFlag">ループ再生フラグ</param>
	/// <param name="volume">ボリューム</param>
	/// <returns>再生ハンドル</returns>
	uint32_t Play(uint32_t soundDataHandle, bool loopFlag = false, float volume = 1.0f);

	/// <summary>
	/// 音声停止
	/// </summary>
	/// <param name="voiceHandle">再生ハンドル</param>
	void Stop(uint32_t voiceHandle);

	/// <summary>
	/// 音声再生中かどうか
	/// </summary>
	/// <param name="voiceHandle">再生ハンドル</param>
	/// <returns>音声再生中かどうか</returns>
	bool IsPlaying(uint32_t voiceHandle);

	/// <summary>
	/// 音声一時停止
	/// </summary>
	/// <param name="voiceHandle">再生ハンドル</param>
	void Pause(uint32_t voiceHandle);

	/// <summary>
	/// 音声一時停止からの再開
	/// </summary>
	/// <param name="voiceHandle">再生ハンドル</param>
	void ReStart(uint32_t voiceHandle);

	/// <summary>
	/// 音量設定
	/// </summary>
	/// <param name="voiceHandle">再生ハンドル</param>
	/// <param name="volume">ボリューム
	void SetVolume(uint32_t voiceHandle, float volume);

private:
	/// <summary>
	/// サウンドデータの解放
	/// </summary>
	/// <param name="soundData">サウンドデータ</param>
	void Unload(SoundData* soundData);

	void DestroyVoice(uint32_t handle);

	Voice* FindUnusedVoice();

private:

	AudioManager() = default;
	~AudioManager() = default;
	AudioManager(const AudioManager&) = delete;
	const AudioManager& operator=(const AudioManager&) = delete;

	Microsoft::WRL::ComPtr<IXAudio2> xAudio2_;
	IXAudio2MasteringVoice* masterVoice_ = nullptr;

	std::vector<SoundData> soundDatas_;
	//std::vector<std::unique_ptr<Voice>> voices_;
	std::array<std::unique_ptr<Voice>, kSoundVoiceMaxNum> voices_;

	const std::string directoryPath_ = "Resources/Audio/";
};

class Audio
{
public:

	void LoadWave(const std::string& filename) { soundHandle_ = AudioManager::GetInstance()->LoadWave(filename); }

	void Play(bool loopFlag = false, float volume = 1.0f) { voiseHandle_ = AudioManager::GetInstance()->Play(soundHandle_, loopFlag, volume); }

	void Stop() const { AudioManager::GetInstance()->Stop(voiseHandle_); }

	bool IsPlaying() const { return AudioManager::GetInstance()->IsPlaying(voiseHandle_); }

	void Pause() const { AudioManager::GetInstance()->Pause(voiseHandle_); }

	void ReStart() const { AudioManager::GetInstance()->ReStart(voiseHandle_); }

	void SetVolume(float volume) const { AudioManager::GetInstance()->SetVolume(voiseHandle_, volume); }

private:
	uint32_t soundHandle_;
	uint32_t voiseHandle_;
};