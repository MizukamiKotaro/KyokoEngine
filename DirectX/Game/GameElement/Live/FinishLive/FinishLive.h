#pragma once
#include <memory>
class Audio;

/// <summary>
/// ライブ終了クラス
/// </summary>
class FinishLive {
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	FinishLive();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="deltaTime">デルタタイム</param>
	void Update(float deltaTime);
	/// <summary>
	/// クリアした
	/// </summary>
	/// <returns>クリアしたか</returns>
	bool IsClear() const { return isClear_; }

private:
	float finishCount_; // タイムカウント
	bool isClear_; // クリアしたか
	bool isFinish_; // 終了したか

	std::unique_ptr<Audio> se_; // SE
};