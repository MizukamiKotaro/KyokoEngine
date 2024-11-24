#pragma once

#include "GameElement/Score/Score.h"
#include "SceneSystem/SceneBase/SceneBase.h"
#include <array>
#include <memory>

/// <summary>
/// スコアマネージャー
/// </summary>
class ScoreManager
{
public:
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static ScoreManager* GetInstance();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// スコアの更新
	/// </summary>
	void UpdateMemory();
	/// <summary>
	/// スコアのセット
	/// </summary>
	/// <param name="score">スコア</param>
	void SetClearScore(Score* score) { clearScore_->SetScore(*score); }
	/// <summary>
	/// クリア時のスコアの取得
	/// </summary>
	/// <returns>スコア</returns>
	Score* GetClearScore() { return clearScore_.get(); }
	/// <summary>
	/// 全てのスコアの取得
	/// </summary>
	/// <returns>全てのスコア</returns>
	std::array<std::unique_ptr<Score>, STAGE::COUNT_STAGE>* GetMemoryScores() { return &memoryScores_; }

private:
	ScoreManager() = default;
	~ScoreManager() = default;
	ScoreManager(const ScoreManager&) = delete;
	ScoreManager& operator=(const ScoreManager&) = delete;

private:
	std::array<std::unique_ptr<Score>, STAGE::COUNT_STAGE> memoryScores_; // 全スコア
	std::unique_ptr<Score> clearScore_; // クリア時のスコア
};