#include "Score.h"

int Score::kPerfectScore = 200;
int Score::kGreatScore = 100;
int Score::kGoodScore = 50;
int Score::kComboThreshold = 10;

void Score::Reset() {
	for (int i = 0; i < END_PARAMETER; i++) {
		parameters_[i] = 0;
	}
	isFullCom_ = false;
	isAP_ = false;
}

void Score::ComboUpdate() {
	if (parameters_[HIGH_COMBO] < parameters_[COMBO]) {
		parameters_[HIGH_COMBO] = parameters_[COMBO];
	}
}

void Score::SetUpdate(const Score& score) {
	// スコア
	if (parameters_[SCORE] < score.parameters_[SCORE]) {
		parameters_[SCORE] = score.parameters_[SCORE];
	}
	// 最高コンボ
	if (parameters_[HIGH_COMBO] < score.parameters_[HIGH_COMBO]) {
		parameters_[HIGH_COMBO] = score.parameters_[HIGH_COMBO];
	}
	// フルコン
	if (!isFullCom_) {
		isFullCom_ = score.isFullCom_;
	}
	// AP
	if (!isAP_) {
		isAP_ = score.isAP_;
	}
}

void Score::SetScore(const Score& score)
{
	parameters_ = score.parameters_;
}

void Score::AddPerfect()
{
	parameters_[PERFECT]++;
	AddCombo();
	AddScore(kPerfectScore * (parameters_[COMBO] / kComboThreshold + 1));
}

void Score::AddGreat()
{
	parameters_[GREAT]++;
	AddCombo();
	AddScore(kGreatScore * (parameters_[COMBO] / kComboThreshold + 1));
}

void Score::AddGood()
{
	parameters_[GOOD]++;
	ComboReset();
	AddScore(kGoodScore);
}

void Score::AddMiss()
{
	parameters_[MISS]++;
	ComboReset();
}

void Score::UpdateIsFullCombo() {
	// ミスとグッドがなければフルコン
	if (parameters_[MISS] == 0 && parameters_[GOOD] == 0) {
		isFullCom_ = true;
		// グレートが0ならAP
		isAP_ = parameters_[GREAT] == 0;
	} else {
		isFullCom_ = false;
		isAP_ = false;
	}
}

void Score::AddCombo() {
	parameters_[COMBO]++;
	ComboUpdate();
}