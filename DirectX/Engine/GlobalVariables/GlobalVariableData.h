#pragma once
#include <map>
#include <variant>
#include <memory>
#include "GlobalVariableUser.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

/// <summary>
/// 響子
/// </summary>
namespace Kyoko {
	/// <summary>
	/// enum classからintへの変換
	/// </summary>
	/// <typeparam name="EnumT">enum class</typeparam>
	/// <param name="id">値</param>
	/// <returns>値</returns>
	template<typename EnumT>
	static int32_t EnumToInt(EnumT id) {
		return static_cast<int32_t>(id);
	}
}

class GlobalVariables;

/// <summary>
/// Kyokoのグローバル変数のデータ
/// </summary>
class GlobalVariableData {
public:
	/// <summary>
	/// 更新(ImGuiで変わった値の更新)
	/// </summary>
	void Update();
	/// <summary>
	/// データのセーブ
	/// </summary>
	void Save();
	// アイテム
	using Item = std::variant<int32_t, float, Vector2, Vector3, bool, std::string, Vector4>;
	/// <summary>
	/// データのセット
	/// </summary>
	/// <param name="items"></param>
	void SetData(const std::map<int32_t, Item>& items);
	/// <summary>
	/// データの取得
	/// </summary>
	/// <returns></returns>
	const std::map<int32_t, Item>& GetData() const;

	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="data">データ</param>
	GlobalVariableData(const GlobalVariableData& data);

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
	GlobalVariableData(const std::string& chunkName, const std::string& groupName, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_");
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
	//void AddComboName(ComboNameType type, const std::string& comboName);

	/// <summary>
	/// アイテムの追加
	/// </summary>
	/// <param name="id">id</param>
	/// <param name="key">キー</param>
	/// <param name="value">値</param>
	/// <param name="tree1">ツリーの名前1</param>
	/// <param name="tree2">ツリーの名前2</param>
	/// <param name="tree3">ツリーの名前3</param>
	/// <param name="tree4">ツリーの名前4</param>
	/// <param name="tree5">ツリーの名前5</param>
	/// <param name="tree6">ツリーの名前6</param>
	void AddItem(int32_t id,const std::string& key, int32_t value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItem(int32_t id,const std::string& key, float value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItem(int32_t id,const std::string& key, const Vector2& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItem(int32_t id,const std::string& key, const Vector3& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItem(int32_t id,const std::string& key, const Vector4& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItem(int32_t id,const std::string& key, bool value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItem(int32_t id,const std::string& key, const std::string& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");

	void AddItemColor(int32_t id, const std::string& key, const Vector4& value, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItemCombo(int32_t id, const std::string& key, ComboNameType type, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItemCombo(int32_t id, const std::string& key, int32_t type, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	void AddItemSystemCombo(int32_t id, const std::string& key, int32_t type, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");

	/// <summary>
	/// 値の取得
	/// </summary>
	/// <param name="id">id</param>
	/// <returns>値</returns>
	int32_t GetIntValue(int32_t id);
	float GetFloatValue(int32_t id);
	const Vector2& GetVector2Value(int32_t id);
	const Vector3& GetVector3Value(int32_t id);
	const Vector4& GetVector4Value(int32_t id);
	bool GetBoolValue(int32_t id);
	const std::string& GetStringValue(int32_t id);

	const Vector4& GetColor(int32_t id);
	const std::string& GetCombo(int32_t id);

	/// <summary>
	/// 値のセット
	/// </summary>
	/// <param name="id">id</param>
	/// <param name="value">値</param>
	void SetVariable(int32_t id, int32_t value);
	void SetVariable(int32_t id, float value);
	void SetVariable(int32_t id, const Vector2& value);
	void SetVariable(int32_t id, const Vector3& value);
	void SetVariable(int32_t id, const Vector4& value);
	void SetVariable(int32_t id, bool value);
	void SetVariable(int32_t id, const std::string& value);
	void SetColor(int32_t id, const Vector4& value);
	void SetCombo(int32_t id, const std::string& value);
	void SetSystemCombo(int32_t id, const std::string& value);

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	/// <param name="treeName">ツリー名</param>
	/// <param name="isSave">値を更新するか</param>
	void DrawImGui(const std::string& treeName, bool isSave = false);
	/// <summary>
	/// データの削除
	/// </summary>
	/// <param name="id">削除したいid</param>
	void EraseItem(int32_t id);

	/// <summary>
	/// 値が変化したか
	/// </summary>
	/// <returns>値が変化したか</returns>
	bool IsChange() const;

private:
	/// <summary>
	/// 値の更新
	/// </summary>
	void UpdateValues();
	/// <summary>
	/// 値のセット
	/// </summary>
	void SetGlobals();
	/// <summary>
	/// 名前の保存
	/// </summary>
	void SetNames(int32_t id, ItemStruct itemStruct, const std::string& key, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	/// <summary>
	/// id毎のImGuiの描画
	/// </summary>
	void DrawImGui(int32_t id);
	/// <summary>
	/// ImGuiのツリー毎にまとめる再起関数
	/// </summary>
	void DrawTreeRecursive(const std::map<int32_t, std::pair<ItemStruct, std::pair<std::string, std::vector<std::string>>>>& names_,int32_t level,const std::string& parentPath = "");

	std::map<int32_t, Item> values_; // 値
	std::unique_ptr<GlobalVariableUser> global_; // グローバル変数クラス
	bool isChange_; // 値が変化したか

	std::map<int32_t, std::pair<ItemStruct, std::pair<std::string, std::vector<std::string>>>> names_; // 名前
#ifdef _DEBUG
	std::map<int32_t, ComboNameType> comboTypes_; // コンボのタイプ
	std::map<int32_t, int32_t> comboIDs_; // コンボのid
	std::map<int32_t, int32_t> debugInt_; // 入力中の値
#endif // _DEBUG
};
