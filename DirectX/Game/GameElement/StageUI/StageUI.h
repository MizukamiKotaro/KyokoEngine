#pragma once
#include "Sprite.h"
#include <array>
#include <memory>

class NotesHit;
class Score;

/// <summary>
/// ステージのUI
/// </summary>
class StageUI 
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	StageUI();
	/// <summary>
	/// ノーツの判定の取得
	/// </summary>
	/// <param name="notesHit">ノーツ判定</param>
	void SetNotesHit(const NotesHit* notesHit) { notesHit_ = notesHit; }
	/// <summary>
	/// スコアのセット
	/// </summary>
	/// <param name="score">スコア</param>
	void SetScore(const Score* score) { score_ = score; }
	/// <summary>
	/// 楽曲の終了フラグのセット
	/// </summary>
	/// <param name="isFinish">楽曲の終了フラグ</param>
	void SetIsMusicFinish(const bool* isFinish) { isFinish_ = isFinish; }
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private:
	const Score* score_ = nullptr; // スコア
	const NotesHit* notesHit_ = nullptr; // ノーツ判定
	const bool* isFinish_ = nullptr; // 終了

	const int kNumSize = 64; // 数字テクスチャのサイズ
	std::array<std::unique_ptr<Sprite>, 2> comboNum_; // コンボ数表示用スプライト

	std::unique_ptr<Sprite> hitSp_; // 評価表示用スプライト
	const int kHitSizeX_ = 256; // 評価テクスチャの横幅
	const int kHitSizeY_ = 64; // 評価テクスチャの縦幅
	std::array<std::unique_ptr<Sprite>, 3> sp_; // UI表示用スプライト
	std::array<std::unique_ptr<Sprite>, 5> scoreNum_; // スコア表示用スプライト

};
