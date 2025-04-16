#pragma once

#include <memory>
#include "TextureManager.h"
#include "ModelDataManager.h"
#include "FrameInfo/FrameInfo.h"
#include <optional>
#include "Sprite.h"
#include "GlobalVariables/GlobalVariableUser.h"

// 遷移state
enum class TransitionState {
	kFadeOut, // 覆われた画面から開ける
	kOperation, // シーン更新
	kFadeIn,   // 画面を覆う
};

// 遷移の基底クラス
class TransitionBase
{
public:
	virtual ~TransitionBase() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw() = 0;
	
	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();

protected:
	/// <summary>
	/// 遷移中、覆われている画面での初期化
	/// </summary>
	virtual void FadeInInitialize() = 0;
	/// <summary>
	/// 覆われた状態から開ける更新
	/// </summary>
	virtual void FadeInUpdate() = 0;
	/// <summary>
	/// 遷移前、遷移のための初期化
	/// </summary>
	virtual void FadeOutInitialize() = 0;
	/// <summary>
	/// 開けた状態から覆われる更新
	/// </summary>
	virtual void FadeOutUpdate() = 0;



protected:
	static TextureManager* textureManager_; // テクスチャマネージャー
	static ModelDataManager* modelDataManager_; // モデルデータマネージャー
	static FrameInfo* frameInfo_; // フレーム情報

protected:
	std::optional<TransitionState> transitionRequest_ = std::nullopt; // 遷移リクエスト
	TransitionState transition_ = TransitionState::kFadeOut; // 遷移state

	std::unique_ptr<GlobalVariableUser> global_; // グローバル変数

	float transitionTimeCount_ = 0.0f; // 遷移用の時間
	float transitionTime_ = 0.5f; // 遷移時間
};

