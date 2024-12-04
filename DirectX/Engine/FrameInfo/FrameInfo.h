#pragma once
#include <chrono>

/// <summary>
/// フレーム時間
/// </summary>
class FrameInfo
{
public:
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static FrameInfo* GetInstance();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 毎フレーム行う最後の処理
	/// </summary>
	void BeginUpdate();

	/// <summary>
	/// デルタタイムの取得
	/// </summary>
	/// <returns>デルタタイム</returns>
	float GetDeltaTime() const { return deltaTime_; }
	/// <summary>
	/// フレームレートの取得
	/// </summary>
	/// <returns>フレームレート</returns>
	float GetFramerate() const { return 1.0f / deltaTime_; }

private:
	FrameInfo() = default;
	~FrameInfo() = default;
	FrameInfo(const FrameInfo&) = delete;
	const FrameInfo& operator=(const FrameInfo&) = delete;

private:
	std::chrono::steady_clock::time_point frameStartTime_; // 開始の時間
	float deltaTime_ = 0.0001f; // デルタタイム
};