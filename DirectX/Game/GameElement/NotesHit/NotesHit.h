#pragma once
#include <memory>
#include "Audio.h"

class Input;
class NotesList;
class Score;

/// <summary>
/// ノーツの評価
/// </summary>
enum HitEvaluation {
	PERFECT,
	GREAT,
	GOOD,
	MISS,
	END,
};

/// <summary>
/// ノーツのあたり判定
/// </summary>
class NotesHit {
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="score">スコア</param>
	/// <param name="notesList">ノーツリスト</param>
	NotesHit(Score* score, NotesList* notesList);
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新、ノーツの更新と判定
	/// </summary>
	/// <param name="time">デルタタイム</param>
	void Update(float time);
	/// <summary>
	/// 評価の取得
	/// </summary>
	/// <returns>評価</returns>
	int GetHitEvaluation() const { return hitEvaluation_; }

private:
	Input* input_; // 入力
	NotesList* notesList_; // ノーツリスト
	Score* score_; // スコア
	int hitEvaluation_; // 評価
	const float kHitTime_[3] = { 0.1f, 0.3f, 0.6f }; // 評価毎の猶予時間
	std::unique_ptr<Audio> se_; // SE
};
