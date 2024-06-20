#include "Game.h"
#include "Camera.h"
#include "FrameInfo/FrameInfo.h"
#include "GameElement/HitSystem/HitSystem.h"
#include "GameElement/ScoreManager/ScoreManager.h"

Game::Game(Camera* camera)
{
	input_ = Input::GetInstance();

	camera_ = camera;

	finishCount_ = 0.0f;
	isClear_ = false;

	live_ = std::make_unique<Live>(camera_);

	music_ = std::make_unique<LiveMusics>();
	
	notesList_ = NotesList::GetInstance();
	notesList_->Initialize();

	score_ = std::make_unique<Score>();

	stageUI_ = std::make_unique<StageUI>();
	stageUI_->SetIsMusicFinish(&music_->IsFinish());
	stageUI_->SetScore(score_.get());

	HitSystem::SetScore(score_.get());

	se_.Load("SE/finish.mp3", "ライブ終わりの歓声");
}

void Game::Initialize()
{
	live_->Initialize();
	time_ = 0.0f;
	notesList_->PopCommands();

	score_->Reset();
	finishCount_ = 0.0f;
	isClear_ = false;

	stageUI_->Initialize();

	HitSystem::Initialize();

	isFinish_ = false;
	music_->Initialize();
}

void Game::Update()
{
	music_->Update();
	time_ += FrameInfo::GetInstance()->GetDeltaTime();
	live_->Update(time_);
	HitSystem::Update(time_);

	if (music_->IsFinish()) {
		finishCount_ += FrameInfo::GetInstance()->GetDeltaTime();

		if (!isFinish_) {
			isFinish_ = true;
			se_.Play();
		}

		if (finishCount_ >= 0.75f) {
			isClear_ = true;
			ScoreManager::GetInstance()->SetClearScore(score_.get());
		}
	}
}

void Game::Draw()
{
	live_->Draw();
	notesList_->Draw(camera_);
	stageUI_->Draw();
}


