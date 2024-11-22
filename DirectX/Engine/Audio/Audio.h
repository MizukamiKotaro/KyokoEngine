#pragma once
#include <stdint.h>
#include <string>
#include <memory>
#include "GlobalVariables/GlobalVariableUser.h"

class AudioManager;
class SoundData;
class VolumeManager;

// 音の読み込みや再生、停止を呼び出すクラス
class Audio
{
public: // gameで使用する関数

	Audio() = default;
	Audio(const Audio& audio);

	/// <summary>
	/// audioデータのロード,タグの設定,音量の設定(ImGuiで後からいじれるようになってる)
	/// </summary>
	/// <param name="filename">"hoge.mp3"で読み込める,Resources/Audio/SE or Musicの中にあれば更に格納しててもok</param>
	/// <param name="itemName">ImGuiに表示する名前,日本語可</param>
	/// <param name="volume">音量</param>
	void Load(const std::string& filename, const std::string& itemName = "_", float volume = 0.7f);
	/// <summary>
	/// 再生
	/// </summary>
	/// <param name="isLoop">ループさせるか</param>
	void Play(bool isLoop = false);
	/// <summary>
	/// 停止
	/// </summary>
	void Stop() const;
	/// <summary>
	/// 再生されているかの取得
	/// </summary>
	/// <returns>再生されているか</returns>
	bool IsPlaying() const;
	/// <summary>
	/// 一時停止
	/// </summary>
	void Pause() const;
	/// <summary>
	/// 一時停止箇所からの再生
	/// </summary>
	void ReStart() const;

	/// <summary>
	/// 全ての再生を停止
	/// </summary>
	static void AllStop();

public: // エンジン内で使用する関数
	static void StaticInitialize();
	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();
	/// <summary>
	/// 名前の取得
	/// </summary>
	/// <returns>名前</returns>
	const std::string& GetItemName() const { return itemName_; }
	/// <summary>
	/// サウンドデータの取得
	/// </summary>
	/// <returns>サウンドデータ</returns>
	const SoundData* GetSoundDataPtr() const;

private:
	/// <summary>
	/// 音量のセット
	/// </summary>
	void SetVolume();

private:
	const SoundData* soundData_; // サウンドデータ
	uint32_t voiceHandle_; // ボイスのハンドル
	float volume_; // 音量
	std::string itemName_; // 名前

	static AudioManager* audioManager_; // 読み込みや再生を行う根幹のクラス
	static VolumeManager* volumeManager_; // 音量を管理するクラス
	
	std::unique_ptr<GlobalVariableUser> global_; // グローバル変数を設定するクラス
	
};