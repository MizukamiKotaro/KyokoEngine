#pragma once
#include <list>
#include <string>
#include <memory>
#include <unordered_map>

class Audio;
enum class AudioType;
class GlobalVariableUser;

/// <summary>
/// 音量のマネージャー
/// </summary>
class VolumeManager
{
public:
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static VolumeManager* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// audioマップのクリア
	/// </summary>
	void Clear();

	/// <summary>
	/// audioのセット
	/// </summary>
	/// <param name="audio">audio</param>
	void SetAudio(const Audio* audio);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// SE音量の取得
	/// </summary>
	/// <returns>SE音量</returns>
	float GetSEVolume() const { return seVolume_ * seVolumeStage_; }
	/// <summary>
	/// Music音量の取得
	/// </summary>
	/// <returns>Music音量</returns>
	float GetMusicVolume() const { return musicVolume_ * musicVolumeStage_; }

	/// <summary>
	/// プレイヤー設定用の音量のデフォルトリセット
	/// </summary>
	void ResetDefalutVolumeStage();
	/// <summary>
	/// プレイヤー設定用のSE音量の取得
	/// </summary>
	/// <returns>プレイヤー設定用のSE音量</returns>
	float GetSEVolumeStage() const { return seVolumeStage_; }
	/// <summary>
	/// プレイヤー設定用のMusic音量の取得
	/// </summary>
	/// <returns>プレイヤー設定用のMusic音量</returns>
	float GetMusicVolumeStage() const { return musicVolumeStage_; }

	/// <summary>
	/// プレイヤー設定用のSE音量のセット
	/// </summary>
	/// <param name="volume">volume</param>
	void SetSEVolumeStage(float volume) { seVolumeStage_ = volume; }
	/// <summary>
	/// プレイヤー設定用のMusic音量のセット
	/// </summary>
	/// <param name="volume">volume</param>
	void SetMusicVolumeStage(float volume) { musicVolumeStage_ = volume; }
	/// <summary>
	/// プレイヤー設定用の音量のリセット
	/// </summary>
	void ResetVolumeStage();

	/// <summary>
	/// プレイヤー設定用の音量の保存
	/// </summary>
	/// <param name="seVolumeStage">SEの音量</param>
	/// <param name="musicVolumeStage">Musicの音量</param>
	void SaveVolumeStage(float seVolumeStage, float musicVolumeStage);

private:
	VolumeManager() = default;
	~VolumeManager() = default;
	VolumeManager(const VolumeManager&) = delete;
	const VolumeManager& operator=(const VolumeManager&) = delete;

	std::unordered_map<std::string, std::unique_ptr<Audio>> audioMap_; // audioのマップ
	std::unique_ptr<GlobalVariableUser> globalVariables_; // グローバル変数を設定するクラス
	
	const float kDefalutVolume = 0.7f; // デフォルトの音量
	float seVolume_ = kDefalutVolume; // SEの音量
	float musicVolume_ = kDefalutVolume; // Musicの音量

	float seVolumeStage_ = kDefalutVolume; // プレイヤーが設定用のSEの音量
	float musicVolumeStage_ = kDefalutVolume; // プレイヤーが設定用のMusicの音量
};