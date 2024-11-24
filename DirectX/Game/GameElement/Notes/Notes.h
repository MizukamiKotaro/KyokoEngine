#pragma once
#include "Sprite.h"
#include <memory>
#include <list>
#include <sstream>

class Camera;

/// <summary>
/// ノーツタイプ
/// </summary>
enum NotesType {
	LEFT_ARROW,
	RIGHT_ARROW,
	UP_ARROW,
	DOWN_ARROW
};

/// <summary>
/// ノーツ
/// </summary>
class Notes {
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="frame">時間</param>
	/// <param name="type">タイプ</param>
	Notes(float frame, int type);
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="time">デルタタイム</param>
	void Update(float time);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(Camera* camera);

	/// <summary>
	/// ノーツの時間の取得
	/// </summary>
	/// <returns>ノーツの時間</returns>
	float GetTime() const { return time_; }

	/// <summary>
	/// タイプの取得
	/// </summary>
	/// <returns>タイプ</returns>
	int GetType() const { return type_; }

	/// <summary>
	/// 死んだフラグを立てる
	/// </summary>
	void Dead() { isDead_ = true; }

	/// <summary>
	/// 死んでいるかの取得
	/// </summary>
	/// <returns>死んでいるか</returns>
	bool IsDead() const { return isDead_; }

private:
	static const float kSpeed_; // デフォルトのスピード
	static float speed_; // スピード

	std::unique_ptr<Sprite> sprite_; // スプライト
	Vector2 firstPos_; // 初期座標
	float time_ = 0; // 時間
	int type_ = 0; // タイプ
	bool isDead_ = false; // 死亡フラグ

};

/// <summary>
/// ノーツリスト
/// </summary>
class NotesList {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(Camera* camera);
	/// <summary>
	/// ノーツデータの読み込み
	/// </summary>
	void PopCommands();
	/// <summary>
	/// ノーツリストの取得
	/// </summary>
	/// <returns>ノーツリスト</returns>
	std::list<std::unique_ptr<Notes>>& GetNotesList() { return notesList_; }

private:
	/// <summary>
	/// ファイルの読み込み
	/// </summary>
	void LoadPopData();

private:
	std::list<std::unique_ptr<Notes>> notesList_; // ノーツリスト
	std::stringstream notesPopCommands_; // 配置コマンド
	std::unique_ptr<Sprite> lane_; // レーン用スプライト
	std::unique_ptr<Sprite> indication_; // 目印用スプライト

};