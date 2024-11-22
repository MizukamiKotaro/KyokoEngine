#pragma once

#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include <wrl.h>
#include <string>
#include <vector>
#include <memory>
#include <list>
#include <unordered_map>

class SoundData;

/// <summary>
/// Audioのマネージャー
/// 読み込みや再生、停止を行う
/// 読み込んだデータを管理している
/// </summary>
class AudioManager
{
public:
	// ボイス
	struct Voice {
		uint32_t handle = 0u; // ハンドル
		IXAudio2SourceVoice* sourceVoice = nullptr; // ソースボイス
		const SoundData* soundData = nullptr; // サウンドデータ
	};
	
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static AudioManager* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// audioデータの読み込み
	/// </summary>
	/// <param name="filename">ファイルネーム</param>
	/// <returns>サウンドデータ</returns>
	const SoundData* Load(const std::string& filename);

	/// <summary>
	/// 再生
	/// </summary>
	/// <param name="soundData">サウンドデータ</param>
	/// <param name="loopFlag">ループさせるか</param>
	/// <param name="volume">音量</param>
	/// <returns>ボイスハンドル</returns>
	uint32_t Play(const SoundData* soundData, bool loopFlag = false, float volume = 0.7f);
	/// <summary>
	/// 停止
	/// </summary>
	/// <param name="voiceHandle">ボイスハンドル</param>
	/// <param name="soundData">サウンドデータ</param>
	void Stop(const uint32_t& voiceHandle, const SoundData* soundData);
	/// <summary>
	/// 再生中か
	/// </summary>
	/// <param name="voiceHandle">ボイスハンドル</param>
	/// <param name="soundData">サウンドデータ</param>
	/// <returns>再生中か</returns>
	bool IsPlaying(const uint32_t& voiceHandle, const SoundData* soundData);
	/// <summary>
	/// 一時停止
	/// </summary>
	/// <param name="voiceHandle">ボイスハンドル</param>
	/// <param name="soundData">サウンドデータ</param>
	void Pause(const uint32_t& voiceHandle, const SoundData* soundData);
	/// <summary>
	/// 一時停止箇所からの再生
	/// </summary>
	/// <param name="voiceHandle">ボイスハンドル</param>
	/// <param name="soundData">サウンドデータ</param>
	void ReStart(const uint32_t& voiceHandle, const SoundData* soundData);
	/// <summary>
	/// 音量のセット
	/// </summary>
	/// <param name="voiceHandle">ボイスハンドル</param>
	/// <param name="soundData">サウンドデータ</param>
	/// <param name="volume">音量</param>
	void SetVolume(const uint32_t& voiceHandle, const SoundData* soundData, float volume);
	/// <summary>
	/// 全てのボイスの停止
	/// </summary>
	void AllStop();
	/// <summary>
	/// 特定のサウンドデータを使用しているボイスの停止
	/// </summary>
	/// <param name="soundData">サウンドデータ</param>
	void StopSameSounds(const SoundData* soundData);
	/// <summary>
	/// 特定のサウンドデータを使用しているボイスが再生中か
	/// </summary>
	/// <param name="soundData">サウンドデータ</param>
	/// <returns>再生中か</returns>
	bool IsPlayingSameSound(const SoundData* soundData);
	/// <summary>
	/// 特定のサウンドデータを使用しているボイスの音量のセット
	/// </summary>
	/// <param name="soundData">サウンドデータ</param>
	/// <param name="volume">音量</param>
	void SetVolumeSameSound(const SoundData* soundData, float volume);

private:
	/// <summary>
	/// サウンドデータの削除
	/// </summary>
	/// <param name="soundData">サウンドデータ</param>
	void Unload(SoundData* soundData);
	/// <summary>
	/// ボイスの削除
	/// </summary>
	/// <param name="handle">ボイスハンドル</param>
	/// <param name="soundData">サウンドデータ</param>
	void DestroyVoice(const uint32_t& handle, const SoundData* soundData);
	/// <summary>
	/// ボイスの削除
	/// </summary>
	/// <param name="voice">ボイス</param>
	void DestroyVoice(const std::unique_ptr<Voice>& voice);
	/// <summary>
	/// ボイスの削除
	/// </summary>
	/// <param name="soundData">サウンドデータ</param>
	void DestroyVoiceSameSound(const SoundData* soundData);

	/// <summary>
	/// 使用していないボイスの取得
	/// </summary>
	/// <returns>ボイス</returns>
	Voice* FindUnusedVoice();

private:
	AudioManager() = default;
	~AudioManager() = default;
	AudioManager(const AudioManager&) = delete;
	const AudioManager& operator=(const AudioManager&) = delete;

	Microsoft::WRL::ComPtr<IXAudio2> xAudio2_; // xAudio2
	IXAudio2MasteringVoice* masterVoice_ = nullptr; // masterVoice

	std::unordered_map<std::string, std::unique_ptr<SoundData>> soundDataMap_; // サウンドデータのマップ
	std::list<std::unique_ptr<Voice>> voices_; // ボイスのリスト

	const std::string directoryPath_ = "Resources/Audio/"; // ダイレクトリーパス
};