#pragma once

#include <memory>
#include "TextureManager.h"
#include "ModelDataManager.h"
#include "FrameInfo/FrameInfo.h"
#include <optional>
#include "Sprite.h"
#include "GlobalVariables/GlobalVariableUser.h"

// フェードの基底クラス
class FadeBase
{
public:
	virtual ~FadeBase() = default;

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

	/// <summary>
	/// 遷移が終了したか
	/// </summary>
	/// <returns>遷移が終了したか</returns>
	bool IsFinishFade();

	/// <summary>
	/// 遷移時間のセット
	/// </summary>
	/// <param name="time">時間</param>
	void SetTransitionTime(float time);

protected:
	/// <summary>
	/// グローバル変数クラス作成
	/// </summary>
	/// <param name="name">名前</param>
	/// <param name="isFadeIn">フェードインか</param>
	void CreateGlobal(const std::string& name, bool isFadeIn = true);

protected:
	static TextureManager* textureManager_; // テクスチャマネージャー
	static ModelDataManager* modelDataManager_; // モデルデータマネージャー
	static FrameInfo* frameInfo_; // フレーム情報

protected:
	std::unique_ptr<GlobalVariableUser> global_;
	float transitionTimeCount_ = 0.0f; // 遷移用の時間
	float transitionTime_ = 0.5f; // 遷移時間
};

