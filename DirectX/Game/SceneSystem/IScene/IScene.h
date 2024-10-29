#pragma once

#include <memory>
#include "TextureManager.h"
#include "ModelDataManager.h"
#include "Input.h"
#include "Audio.h"
#include "Camera.h"
#include "FrameInfo/FrameInfo.h"
#include <optional>
#include "Sprite.h"
#include <memory>

enum SCENE { TITLE, SELECT, STAGE, STAGE_EDITOR, CLEAR };

enum STAGE { SHINING_STAR, COUNT_STAGE };

enum class Transition{
	kFromBlack,
	kOperation,
	kToBlack,
};

// シーンの基底クラス
class IScene
{

public:
	virtual void Initialize() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
	virtual ~IScene();

	// シーン番号のゲッター
	void FirstInit();
	static const int32_t& GetSceneNo() { return sceneNo_; }
	static const int32_t& GetStageNo() { return stageNo_; }

	static void SetStageNo(const int32_t& no) { stageNo_ = no; }
	static void SetSceneNo(const int32_t& no) { sceneNo_ = no; }

	// シーン遷移用
	virtual void FromBlackInitialize();
	virtual void FromBlackUpdate();
	virtual void Play();
	virtual void ToBlackInitialize();
	virtual void ToBlackUpdate();

	virtual void FirstUpdate();

	void ChangeScene(const int32_t& sceneNo);

	virtual void BlackDraw() { black_->Draw(*camera_.get()); }

protected:

	TextureManager* textureManager_ = nullptr;
	ModelDataManager* modelDataManager_ = nullptr;
	Input* input_ = nullptr;
	FrameInfo* frameInfo_ = nullptr;

protected:
	// シーン番号を管理する変数
	static int32_t sceneNo_;
	// ステージ番号を管理する変数
	static int32_t stageNo_;

	std::unique_ptr<Camera> camera_;

	std::optional<Transition> transitionRequest_ = std::nullopt;

	Transition transition_ = Transition::kFromBlack;

private:

	int nextScene_ = 0;

	float transitionTimeCount_ = 0.0f;

	std::unique_ptr<Sprite> black_;
	const float kTransitionTime = 0.5f;

	bool sameScene_ = false;
};

