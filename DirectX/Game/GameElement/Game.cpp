#include "Game.h"
#include "Camera.h"
#include "FrameInfo/FrameInfo.h"
#include "GameElement/HitSystem/HitSystem.h"
#include "GameElement/ScoreManager/ScoreManager.h"

Game::Game(Camera* camera)
{
	input_ = Input::GetInstance();
	camera_ = camera;

	live_ = std::make_unique<Live>(camera_);
	music_ = std::make_unique<LiveMusics>();
	finishLive_ = std::make_unique<FinishLive>();
	
	notesList_ = NotesList::GetInstance();
	notesList_->Initialize();

	score_ = std::make_unique<Score>();

	stageUI_ = std::make_unique<StageUI>();
	stageUI_->SetIsMusicFinish(&music_->IsFinish());
	stageUI_->SetScore(score_.get());

	HitSystem::SetScore(score_.get());
}

void Game::Initialize()
{
	live_->Initialize();
	time_ = 0.0f;
	notesList_->PopCommands();

	score_->Reset();

	stageUI_->Initialize();

	HitSystem::Initialize();

	music_->Initialize();
	finishLive_->Initialize();
}

void Game::Update()
{
	music_->Update();
	float deltaTime = FrameInfo::GetInstance()->GetDeltaTime();
	time_ += deltaTime;
	live_->Update(time_);
	HitSystem::Update(time_);

	if (music_->IsFinish()) {
		finishLive_->Update(deltaTime);
		if (finishLive_->IsClear()) {
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
