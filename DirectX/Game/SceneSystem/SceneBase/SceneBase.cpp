#include "SceneBase.h"
#include "Ease/Ease.h"
#include "FrameInfo/FrameInfo.h"

// タイトルシーンで初期化
int32_t SceneBase::sceneNo_ = SCENE::TITLE;
int32_t SceneBase::stageNo_ = STAGE::SHINING_STAR;
TextureManager* SceneBase::textureManager_;
ModelDataManager* SceneBase::modelDataManager_;
Input* SceneBase::input_;
FrameInfo* SceneBase::frameInfo_;

SceneBase::~SceneBase(){}

void SceneBase::StaticInitialize()
{
	textureManager_ = TextureManager::GetInstance();
	modelDataManager_ = ModelDataManager::GetInstance();
	input_ = Input::GetInstance();
	frameInfo_ = FrameInfo::GetInstance();
}

void SceneBase::FirstInitialize()
{
	// カメラの初期化
	camera_ = std::make_unique<Camera>();
	camera_->Initialize();
	// 遷移の初期化
	transitionSprite_ = std::make_unique<Sprite>("white.png");
	transitionSprite_->size_ = WindowsInfo::GetInstance()->GetWindowSize();
	transitionSprite_->pos_ = transitionSprite_->size_ * 0.5f;
	transitionSprite_->SetColor(Vector4{ 0.0f,0.0f,0.0f,1.0f });
	transitionSprite_->Update();
}

void SceneBase::FromBlackInitialize()
{
	if (sameScene_) {
		// 同じシーンの時初期化
		sameScene_ = false;
		Initialize();
	}
	// 遷移用に画面を黒くリセット
	transitionTimeCount_ = 0.0f;
	transitionSprite_->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });
}

void SceneBase::FromBlackUpdate()
{
	float time = frameInfo_->GetDeltaTime();
	// 読み込みとかでデルタタイムが大きいときに不自然にならないようにするため
	if (time >= 0.1f) {
		return;
	}
	// 遷移処理
	transitionTimeCount_ += time;
	float alpha = Ease::UseEase(1.0f, 0.0f, transitionTimeCount_, kTransitionTime, Ease::EaseInSine, 2);
	transitionSprite_->SetColor({ 0.0f, 0.0f, 0.0f, alpha });

	// 遷移時間を超えたら値を整えて切り替え
	if (transitionTimeCount_ >= kTransitionTime) {
		transitionSprite_->SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });
		transitionRequest_ = TransitionState::kOperation;
	}
}

void SceneBase::Play()
{
	// リクエスト確認
	if (transitionRequest_) {
		transition_ = transitionRequest_.value();

		switch (transition_)
		{
		case TransitionState::kFromBlack:
			FromBlackInitialize();
			break;
		case TransitionState::kOperation:
			break;
		case TransitionState::kToBlack:
			ToBlackInitialize();
			break;
		default:
			break;
		}

		transitionRequest_ = std::nullopt;
	}

	// 更新
	switch (transition_)
	{
	case TransitionState::kFromBlack:
		FromBlackUpdate();
		break;
	case TransitionState::kOperation:
		// 継承先のシーンの更新処理
		Update();
		break;
	case TransitionState::kToBlack:
		ToBlackUpdate();
		break;
	default:
		break;
	}
}

void SceneBase::ToBlackInitialize()
{
	// 透明になるようにリセット
	transitionTimeCount_ = 0.0f;
	transitionSprite_->SetColor({ 0.0f, 0.0f, 0.0f, 0.0f });
}

void SceneBase::ToBlackUpdate()
{
	// 遷移
	transitionTimeCount_ += frameInfo_->GetDeltaTime();
	float alpha = Ease::UseEase(0.0f, 1.0f, transitionTimeCount_, kTransitionTime, Ease::EaseInSine, 2);
	transitionSprite_->SetColor({ 0.0f, 0.0f, 0.0f, alpha });

	// 遷移時間を超えたら切り替え
	if (transitionTimeCount_ >= kTransitionTime) {
		// 遷移の続きの準備、黒にリセット
		transitionRequest_ = TransitionState::kFromBlack;
		transitionSprite_->SetColor({ 0.0f, 0.0f, 0.0f, 1.0f });

		// シーンの切り替え
		if (sceneNo_ == nextScene_) {
			sameScene_ = true;
		}
		else {
			sceneNo_ = nextScene_;
		}
	}
}

void SceneBase::FirstUpdate()
{
}

void SceneBase::ChangeScene(int32_t sceneNo)
{
	nextScene_ = sceneNo;
	transitionRequest_ = TransitionState::kToBlack;
}

void SceneBase::TransitionDraw() {
	transitionSprite_->Draw(*camera_.get());
}