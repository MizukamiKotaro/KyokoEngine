#include "StageUI.h"
#include "GameElement/NotesHit/NotesHit.h"
#include "GameElement/Score/Score.h"

StageUI::StageUI()
{
	for (int i = 0; i < 5; i++) {

		if (i < 3) {
			if (i < 2) {
				// コンボ用スプライト
				comboNum_[i] = std::make_unique<Sprite>("scoreNum.png");
				comboNum_[i]->pos_ = { float(i * 64.0f + 160.0f), 300.0f };
				comboNum_[i]->size_ = { 64.0f, 64.0f };
				comboNum_[i]->Update();
			}
			// UI用スプライト
			sp_[i] = std::make_unique<Sprite>("gameScene.png");
			sp_[i]->pos_ = { 400.0f,80.0f * i };
			sp_[i]->size_ = { 256.0f, 64.0f };
			sp_[i]->SetTextureTopLeft({ i * 256.0f, 0.0f });
			sp_[i]->SetTextureSize({ 256.0f, 64.0f });
		}
		// スコア用スプライト
		scoreNum_[i] = std::make_unique<Sprite>("scoreNum.png");
		scoreNum_[i]->pos_ = { float(i * 64.0f + 64.0f), 120.0f };
		scoreNum_[i]->size_ = { 64.0f, 64.0f };
		scoreNum_[i]->Update();
	}

	// 初期値設定
	sp_[0]->pos_ = { 160.0f,50.0f };
	sp_[1]->pos_ = { 160.0f,200.0f };
	sp_[2]->pos_ = { 640.0f,300.0f };
	sp_[0]->Update();
	sp_[1]->Update();
	sp_[2]->Update();

	hitSp_ = std::make_unique<Sprite>("hit.png");
	hitSp_->pos_ = { 160.0f, 400.0f };
	hitSp_->size_ = { 256.0f,64.0f };
	hitSp_->Update();
}

void StageUI::Draw()
{
	// スコア
	int score = score_->GetScore();
	for (int i = 0; i < 5; i++) {
		int num = score * int(pow(10, i)) / 10000;
		score = score % (10000 / int(pow(10, i)));
		if (num > 9) {
			num = 0;
		}
		scoreNum_[i]->SetTextureTopLeft({ float(num * kNumSize), 0.0f });
		scoreNum_[i]->SetTextureSize({ float(kNumSize), float(kNumSize) });
		scoreNum_[i]->Update();
		scoreNum_[i]->Draw();
	}
	sp_[0]->Draw();

	// コンボ
	int combo = score_->GetCombo();
	int k = 0;
	for (int i = 0; i < 2; i++) {
		int num = combo * int(pow(10, i)) / 10;
		combo = combo % (10 / int(pow(10, i)));
		if (num > 9) {
			num = 0;
		}
		if (num != 0) {
			k++;
		}
		if (k != 0) {
			comboNum_[i]->SetTextureTopLeft({ float(num * kNumSize), 0.0f });
			comboNum_[i]->SetTextureSize({ float(kNumSize), float(kNumSize) });
			comboNum_[i]->Update();
			comboNum_[i]->Draw();
		}
	}
	sp_[1]->Draw();

	// 評価
	int hitNum = notesHit_->GetHitEvaluation();
	if (hitNum != HitEvaluation::END) {
		hitSp_->SetTextureTopLeft({ float(hitNum * kHitSizeX_), 0.0f });
		hitSp_->SetTextureSize({ float(kHitSizeX_), float(kHitSizeY_) });
		hitSp_->Update();
		hitSp_->Draw();
	}

	// 終了
	if (*isFinish_) {
		sp_[2]->Draw();
	}
}
