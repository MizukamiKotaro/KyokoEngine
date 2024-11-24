#pragma once
#include <memory>
#include "GameElement/LiveEditor/LiveEditor.h"
#include "GameElement/Notes/Notes.h"
#include "GameElement/Score/Score.h"
#include "GameElement/StageUI/StageUI.h"
#include "GameElement/Live/LiveMusics/LiveMusics.h"
#include "GameElement/Live/FinishLive/FinishLive.h"
#include "GameElement/NotesHit/NotesHit.h"

class FrameInfo;
class Camera;

/// <summary>
/// ゲーム
/// </summary>
class Game {
public: 
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="camera">カメラ</param>
	Game(Camera* camera);
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();
	/// <summary>
	/// 最初に１度行う更新
	/// </summary>
	void FirstUpdate();
	/// <summary>
	/// クリアしたかの取得
	/// </summary>
	/// <returns>クリアしたか</returns>
	bool GetIsClear() const { return finishLive_->IsClear(); }

private:
	Camera* camera_ = nullptr; // カメラ
	FrameInfo* frameInfo_ = nullptr; // フレーム

	std::unique_ptr<LiveEditor> live_; // ライブ
	std::unique_ptr<Score> score_; // スコア
	std::unique_ptr<StageUI> stageUI_; // ステージUI
	std::unique_ptr<LiveMusics> music_; // ミュージック
	std::unique_ptr<FinishLive> finishLive_; // ライブ終了演出
	std::unique_ptr<NotesList> notesList_; // ノーツリスト
	std::unique_ptr<NotesHit> notesHit_; // ノーツのあたり判定

	float time_; // タイム

};
