#pragma once
#include <array>

/// <summary>
/// スコア
/// </summary>
class Score {
public:
	/// <summary>
	/// 評価
	/// </summary>
	enum Parameter {
		SCORE, // スコア
		COMBO, // コンボ
		HIGH_COMBO, // 最高コンボ
		PERFECT, //パーフェクト
		GREAT, // グレート
		GOOD, // グッド
		MISS, // ミス
		END_PARAMETER, // パラメータ数
	};
	/// <summary>
	/// リセット
	/// </summary>
	void Reset();
	/// <summary>
	/// コンボの更新
	/// </summary>
	void ComboUpdate();
	/// <summary>
	/// スコアのセットと更新
	/// </summary>
	/// <param name="score">スコア</param>
	void SetUpdate(const Score& score);
	/// <summary>
	/// スコアのセット
	/// </summary>
	/// <param name="score">スコア</param>
	void SetScore(const Score& score);
	/// <summary>
	/// スコアの加算
	/// </summary>
	/// <param name="score">スコア</param>
	void AddScore(int score) { parameters_[SCORE] += score; }

	/// <summary>
	/// パーフェクトの追加
	/// </summary>
	void AddPerfect();
	/// <summary>
	/// グレートの追加
	/// </summary>
	void AddGreat();
	/// <summary>
	/// グッドの追加
	/// </summary>
	void AddGood();
	/// <summary>
	/// ミスの追加
	/// </summary>
	void AddMiss();
	/// <summary>
	/// コンボの追加
	/// </summary>
	void AddCombo();
	/// <summary>
	/// コンボのリセット
	/// </summary>
	void ComboReset() { parameters_[COMBO] = 0; }

	/// <summary>
	/// フルコンかどうかの更新
	/// </summary>
	void UpdateIsFullCombo();

	/// <summary>
	/// スコアの取得
	/// </summary>
	/// <returns>スコア</returns>
	int GetScore() const { return parameters_[SCORE]; }

	/// <summary>
	/// コンボの取得
	/// </summary>
	/// <returns>コンボ</returns>
	int GetCombo() const { return parameters_[COMBO]; }

	/// <summary>
	/// 最高コンボの取得
	/// </summary>
	/// <returns>最高コンボ</returns>
	int GetHighCombo() const { return parameters_[HIGH_COMBO]; }

	/// <summary>
	/// パーフェクトの取得
	/// </summary>
	/// <returns>パーフェクト</returns>
	int GetPerfect() const { return parameters_[PERFECT]; }

	/// <summary>
	/// グレートの取得
	/// </summary>
	/// <returns>グレート</returns>
	int GetGreat() const { return parameters_[GREAT]; }

	/// <summary>
	/// グッドの取得
	/// </summary>
	/// <returns>グッド</returns>
	int GetGood() const { return parameters_[GOOD]; }

	/// <summary>
	/// ミスの取得
	/// </summary>
	/// <returns>ミス</returns>
	int GetMiss() const { return parameters_[MISS]; }

	/// <summary>
	/// フルコンかどうかの取得
	/// </summary>
	/// <returns>フルコンかどうか</returns>
	bool IsFullCombo() const { return isFullCom_; }

	/// <summary>
	/// APかどうかの取得
	/// </summary>
	/// <returns>APかどうか</returns>
	bool IsAP() const { return isAP_; }

private:
	std::array<int, END_PARAMETER> parameters_; // 評価

	bool isFullCom_ = false; // フルコンか
	bool isAP_ = false; // オールパーフェクトか

	static int kPerfectScore; // パーフェクトの増加スコア
	static int kGreatScore; // グレートの増加スコア
	static int kGoodScore; // グッドの増加スコア
	static int kComboThreshold; // コンボの閾値
};
