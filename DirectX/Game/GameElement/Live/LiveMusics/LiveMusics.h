#pragma once
#include <memory>

class Audio;
/// <summary>
/// ライブ用楽曲
/// </summary>
class LiveMusics {
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	LiveMusics();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 楽曲がおわったかの取得
	/// </summary>
	/// <returns>楽曲がおわったか</returns>
	const bool& IsFinish() const { return isMusicFinish_; }

private:
	std::unique_ptr<Audio> music_; // ミュージック
	bool isMusicStart_; // スタートしたか
	bool isMusicFinish_; // おわったか
};