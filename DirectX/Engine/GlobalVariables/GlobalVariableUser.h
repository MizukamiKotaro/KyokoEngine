#pragma once
#include <string>
#include <stdint.h>
#include <vector>
#include "ComboNameConfig.h"

class Vector2;
class Vector3;
class Vector4;
class GlobalVariables;
class GlobalVariableComboNames;

/// <summary>
/// グローバル変数を使いやすくするクラス
/// </summary>
class GlobalVariableUser {
public:
	/// <summary>
	/// 共通部分初期化
	/// </summary>
	static void StaticInitialize();

public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="chunkName">チャンクの名前</param>
	/// <param name="groupName">グループの名前</param>
	/// <param name="tree1">ツリーの名前1</param>
	/// <param name="tree2">ツリーの名前2</param>
	/// <param name="tree3">ツリーの名前3</param>
	/// <param name="tree4">ツリーの名前4</param>
	/// <param name="tree5">ツリーの名前5</param>
	GlobalVariableUser(const std::string& chunkName, const std::string& groupName, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_");
	/// <summary>
	/// グループ名のリセット
	/// </summary>
	/// <param name="groupName">グループ名</param>
	void ResetGroupName(const std::string& groupName);
	/// <summary>
	/// グループの作成
	/// </summary>
	void CreateGroup();
	/// <summary>
	/// コンボの追加
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <param name="comboName">名前</param>
	void AddComboName(ComboNameType type, const std::string& comboName);
	void AddComboName(int32_t type, const std::string& comboName);
	void AddComboName(const std::string& type, const std::string& comboName);

	void AddComboType(const std::string& type);

	/// <summary>
	/// セーブ
	/// </summary>
	void Save() const;

	/// <summary>
	/// アイテムの追加
	/// </summary>
	/// <param name="key">キー</param>
	/// <param name="value">値</param>
	/// <param name="tree1">ツリーの名前1</param>
	/// <param name="tree2">ツリーの名前2</param>
	/// <param name="tree3">ツリーの名前3</param>
	/// <param name="tree4">ツリーの名前4</param>
	/// <param name="tree5">ツリーの名前5</param>
	/// <param name="tree6">ツリーの名前6</param>
	void AddItem(const std::string& key, int32_t value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItem(const std::string& key, float value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItem(const std::string& key, const Vector2& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItem(const std::string& key, const Vector3& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItem(const std::string& key, const Vector4& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItem(const std::string& key, bool value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItem(const std::string& key, const std::string& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");

	void AddItemColor(const std::string& key, const Vector4& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItemCombo(const std::string& key, ComboNameType type, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItemCombo(const std::string& key, int32_t type, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");


	/// <summary>
	/// 値の取得
	/// </summary>
	/// <param name="key">キー</param>
	/// <param name="tree1">ツリーの名前1</param>
	/// <param name="tree2">ツリーの名前2</param>
	/// <param name="tree3">ツリーの名前3</param>
	/// <param name="tree4">ツリーの名前4</param>
	/// <param name="tree5">ツリーの名前5</param>
	/// <param name="tree6">ツリーの名前6</param>
	/// <returns></returns>
	int32_t GetIntValue(const std::string& key, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	float GetFloatValue(const std::string& key, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	const Vector2& GetVector2Value(const std::string& key, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	const Vector3& GetVector3Value(const std::string& key, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	const Vector4& GetVector4Value(const std::string& key, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	bool GetBoolValue(const std::string& key, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	const std::string& GetStringValue(const std::string& key, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;

	const Vector4& GetColor(const std::string& key, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	const std::string& GetCombo(const std::string& key, ComboNameType type, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	const std::string& GetCombo(const std::string& key, int32_t type, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;

	/// <summary>
	/// 値のセット
	/// </summary>
	/// <param name="key">キー</param>
	/// <param name="value">値</param>
	/// <param name="tree1">ツリーの名前1</param>
	/// <param name="tree2">ツリーの名前2</param>
	/// <param name="tree3">ツリーの名前3</param>
	/// <param name="tree4">ツリーの名前4</param>
	/// <param name="tree5">ツリーの名前5</param>
	/// <param name="tree6">ツリーの名前6</param>
	void SetVariable(const std::string& key, int32_t value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void SetVariable(const std::string& key, float value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void SetVariable(const std::string& key, const Vector2& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void SetVariable(const std::string& key, const Vector3& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void SetVariable(const std::string& key, const Vector4& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void SetVariable(const std::string& key, bool value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void SetVariable(const std::string& key, const std::string& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");

	void SetColor(const std::string& key, const Vector4& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void SetCombo(const std::string& key, ComboNameType type, const std::string& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void SetCombo(const std::string& key, int32_t type, const std::string& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");


	/// <summary>
	/// ImGuiを使わないアイテムの追加、プレイヤーがゲーム内で設定できる項目とか
	/// </summary>
	/// <param name="key">キー</param>
	/// <param name="value">値</param>
	void AddItemDontTouchImGui(const std::string& key, int32_t value);
	void AddItemDontTouchImGui(const std::string& key, float value);
	void AddItemDontTouchImGui(const std::string& key, const Vector2& value);
	void AddItemDontTouchImGui(const std::string& key, const Vector3& value);
	void AddItemDontTouchImGui(const std::string& key, const Vector4& value);
	void AddItemDontTouchImGui(const std::string& key, bool value);
	void AddItemDontTouchImGui(const std::string& key, const std::string& value);

	/// <summary>
	/// ImGuiを使わないアイテムの値の取得
	/// </summary>
	/// <param name="key">キー</param>
	/// <returns>ImGuiを使わないアイテムの値</returns>
	int32_t GetIntValueDontTouchImGui(const std::string& key) const;
	float GetFloatValueDontTouchImGui(const std::string& key) const;
	const Vector2& GetVector2ValueDontTouchImGui(const std::string& key) const;
	const Vector3& GetVector3ValueDontTouchImGui(const std::string& key) const;
	const Vector4& GetVector4ValueDontTouchImGui(const std::string& key) const;
	bool GetBoolValueDontTouchImGui(const std::string& key) const;
	const std::string& GetStringValueDontTouchImGui(const std::string& key) const;

	/// <summary>
	/// ImGuiを使わない値のセットと保存
	/// </summary>
	/// <param name="key">キー</param>
	/// <param name="value">値</param>
	void SaveDontTouchImGui(const std::string& key, int32_t value);
	void SaveDontTouchImGui(const std::string& key, float value);
	void SaveDontTouchImGui(const std::string& key, const Vector2& value);
	void SaveDontTouchImGui(const std::string& key, const Vector3& value);
	void SaveDontTouchImGui(const std::string& key, const Vector4& value);
	void SaveDontTouchImGui(const std::string& key, bool value);
	void SaveDontTouchImGui(const std::string& key, const std::string& value);

	/// <summary>
	/// ツリーが開いているかの取得
	/// </summary>
	/// <param name="tree1">ツリーの名前1</param>
	/// <param name="tree2">ツリーの名前2</param>
	/// <param name="tree3">ツリーの名前3</param>
	/// <param name="tree4">ツリーの名前4</param>
	/// <param name="tree5">ツリーの名前5</param>
	/// <param name="tree6">ツリーの名前6</param>
	/// <returns>ツリー</returns>
	/// <returns>ツリーが開いているか</returns>
	bool IsTreeOpen(const std::string& tree1, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	/// <summary>
	/// ツリーが開いているかの取得
	/// </summary>
	/// <param name="treeNo">いくつ目のツリーか</param>
	/// <returns>ツリーが開いているか</returns>
	bool IsTreeOpen(int32_t treeNo);
	/// <summary>
	/// ツリーが開いているかの取得
	/// </summary>
	/// <returns>ツリーが開いているか</returns>
	bool IsTreeOpen() const;
	/// <summary>
	/// チャンク名の取得
	/// </summary>
	/// <returns>チャンク名</returns>
	const std::string& GetChunkName() const { return chunkName_; }

	/// <summary>
	/// コンボの呼び出し
	/// </summary>
	/// <param name="key">キー</param>
	/// <param name="type">タイプ</param>
	/// <param name="ptr">ポインタ</param>
	void DrawImGuiCombo(const std::string& key, const std::string& type, std::string* ptr);
	void DrawImGuiCombo(const std::string& key, ComboNameType type, std::string* ptr);
	void DrawImGuiCombo(const std::string& key, int32_t type, std::string* ptr);

private:
	/// <summary>
	/// ツリーの作成
	/// </summary>
	/// <param name="tree1">ツリーの名前1</param>
	/// <param name="tree2">ツリーの名前2</param>
	/// <param name="tree3">ツリーの名前3</param>
	/// <param name="tree4">ツリーの名前4</param>
	/// <param name="tree5">ツリーの名前5</param>
	/// <param name="tree6">ツリーの名前6</param>
	/// <returns>ツリー</returns>
	std::vector<std::string> CreateTree(const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;

private:
	static GlobalVariables* global_; // グローバル変数を管理するクラス
	static GlobalVariableComboNames* globalCombo_; // コンボの名前を管理するクラス
	std::string chunkName_; // チャンク名
	std::string groupName_; // グループ名
	std::vector<std::string> tree_; // ツリー
};