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

// シーンenum
enum SCENE { 
	TITLE,        // タイトル
	SELECT,       // セレクト
	STAGE,        // ステージ
	STAGE_EDITOR, // ステージエディター
	CLEAR         // クリア
};

// ステージenum
enum STAGE { 
	SHINING_STAR, // シャイニングスター
	COUNT_STAGE   // 全ステージ数
};

// 遷移state
enum class TransitionState {
	kFromBlack, // 覆われた画面から開ける
	kOperation, // シーン更新
	kToBlack,   // 画面を覆う
};

// シーンの基底クラス
class SceneBase
{
public:
	virtual ~SceneBase();

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
	/// 遷移含めた更新
	/// </summary>
	virtual void Play();
	
	/// <summary>
	/// 静的初期化
	/// </summary>
	static void StaticInitialize();
	/// <summary>
	/// コンストラクタで行う共通部分の初期化
	/// </summary>
	void FirstInitialize();
	/// <summary>
	/// 初期化後１度行う更新
	/// </summary>
	virtual void FirstUpdate();

	/// <summary>
	/// シーンの作成
	/// </summary>
	/// <returns>シーン</returns>
	static int32_t GetSceneNo() { return sceneNo_; }
	/// <summary>
	/// シーンの作成
	/// </summary>
	/// <returns>シーン</returns>
	static int32_t GetStageNo() { return stageNo_; }

	/// <summary>
	/// ステージナンバーのセッター
	/// </summary>
	/// <param name="no">ステージナンバー</param>
	static void SetStageNo(int32_t no) { stageNo_ = no; }
	/// <summary>
	/// シーンナンバーのセッター
	/// </summary>
	/// <param name="no">シーンナンバー</param>
	static void SetSceneNo(int32_t no) { sceneNo_ = no; }


protected:
	/// <summary>
	/// 遷移中、覆われている画面での初期化
	/// </summary>
	virtual void FromBlackInitialize();
	/// <summary>
	/// 覆われた状態から開ける更新
	/// </summary>
	virtual void FromBlackUpdate();
	/// <summary>
	/// 遷移前、遷移のための初期化
	/// </summary>
	virtual void ToBlackInitialize();
	/// <summary>
	/// 開けた状態から覆われる更新
	/// </summary>
	virtual void ToBlackUpdate();

	/// <summary>
	/// シーン切り替え、遷移開始
	/// </summary>
	/// <param name="sceneNo">シーンナンバー</param>
	void ChangeScene(int32_t sceneNo);

	/// <summary>
	/// 遷移の描画
	/// </summary>
	virtual void TransitionDraw();

protected:

	static TextureManager* textureManager_; // テクスチャマネージャー
	static ModelDataManager* modelDataManager_; // モデルデータマネージャー
	static Input* input_; // インプット
	static FrameInfo* frameInfo_; // フレーム情報
	static int32_t sceneNo_; // シーン番号
	static int32_t stageNo_; // ステージ番号

protected:
	std::unique_ptr<Camera> camera_; // カメラ
	std::optional<TransitionState> transitionRequest_ = std::nullopt; // 遷移リクエスト
	TransitionState transition_ = TransitionState::kFromBlack; // 遷移state

	int32_t nextScene_ = 0; // 次のシーン
	float transitionTimeCount_ = 0.0f; // 遷移用の時間
	std::unique_ptr<Sprite> transitionSprite_; // 遷移用スプライト
	const float kTransitionTime = 0.5f; // 遷移時間
	bool sameScene_ = false; // 遷移後同じシーンか
};

