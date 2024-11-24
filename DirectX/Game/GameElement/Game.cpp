#include "Game.h"
#include "Camera.h"
#include "FrameInfo/FrameInfo.h"
#include "GameElement/ScoreManager/ScoreManager.h"
#ifdef _DEBUG
#include "ImGuiManager/ImGuiManager.h"
#endif // _DEBUG

Game::Game(Camera* camera)
{
	frameInfo_ = FrameInfo::GetInstance();
	camera_ = camera;

	live_ = std::make_unique<LiveEditor>(camera_);
	music_ = std::make_unique<LiveMusics>();
	finishLive_ = std::make_unique<FinishLive>();
	
	notesList_ = std::make_unique<NotesList>();
	notesList_->Initialize();

	score_ = std::make_unique<Score>();

	notesHit_ = std::make_unique<NotesHit>(score_.get(), notesList_.get());

	stageUI_ = std::make_unique<StageUI>();
	stageUI_->SetIsMusicFinish(&music_->IsFinish());
	stageUI_->SetScore(score_.get());
	stageUI_->SetNotesHit(notesHit_.get());
}

void Game::Initialize()
{
	live_->Initialize();
	time_ = 0.0f;
	notesList_->PopCommands();
	score_->Reset();
	notesHit_->Initialize();
	music_->Initialize();
	finishLive_->Initialize();
}

void Game::Update()
{
	music_->Update();
	float deltaTime = frameInfo_->GetDeltaTime();
	time_ += deltaTime;
	live_->Update(deltaTime);
	notesHit_->Update(time_);
	if (music_->IsFinish()) {
		// 音楽が終了
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

void Game::FirstUpdate()
{
	live_->Update(0.00001f);
}
