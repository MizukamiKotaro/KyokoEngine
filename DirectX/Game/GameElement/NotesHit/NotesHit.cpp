#include "NotesHit.h"
#include "Input.h"
#include "GameElement/Score/Score.h"
#include "GameElement/Notes/Notes.h"

NotesHit::NotesHit(Score* score, NotesList* notesList)
{
	score_ = score;
	input_ = Input::GetInstance();
	notesList_ = notesList;
	se_ = std::make_unique<Audio>();
	se_->Load("SE/se.mp3", "タップ音");
}

void NotesHit::Initialize()
{
	hitEvaluation_ = HitEvaluation::END;
}

void NotesHit::Update(float time)
{
	std::list<std::unique_ptr<Notes>>& notesList = notesList_->GetNotesList();

	for (std::list<std::unique_ptr<Notes>>::iterator i = notesList.begin(); i != notesList.end();) {
		std::unique_ptr<Notes>& notes = *i;
		if (notes->IsDead()) {
			i++;
			continue;
		}

		// ノーツの更新処理
		notes->Update(time);

		// ノーツが時間切れになった場合の処理
		if (time >= notes->GetTime() + kHitTime_[GOOD]) {
			// ミス
			score_->AddMiss();
			hitEvaluation_ = MISS;
			notes->Dead();
		}
		// ヒット判定処理
		else if ((input_->PressedGamePadButton(Input::GamePadButton::LEFT) && LEFT_ARROW == notes->GetType()) ||
			(input_->PressedGamePadButton(Input::GamePadButton::RIGHT) && RIGHT_ARROW == notes->GetType()) ||
			(input_->PressedGamePadButton(Input::GamePadButton::UP) && UP_ARROW == notes->GetType()) ||
			(input_->PressedGamePadButton(Input::GamePadButton::DOWN) && DOWN_ARROW == notes->GetType())) {
			float errorFrame = std::abs(time - notes->GetTime());

			if (errorFrame <= kHitTime_[PERFECT]) {
				// パーフェクト
				score_->AddPerfect();
				hitEvaluation_ = PERFECT;
				se_->Play();
				notes->Dead();
			}
			else if (errorFrame <= kHitTime_[GREAT]) {
				// グレート
				score_->AddGreat();
				hitEvaluation_ = GREAT;
				se_->Play();
				notes->Dead();
			}
			else if (errorFrame <= kHitTime_[GOOD]) {
				// グッド
				score_->AddGood();
				hitEvaluation_ = GOOD;
				se_->Play();
				notes->Dead();
			}
		}

		// 削除処理
		if (notes->IsDead()) {
			i = notesList.erase(i);
		}
		else {
			i++;
		}
	}
}