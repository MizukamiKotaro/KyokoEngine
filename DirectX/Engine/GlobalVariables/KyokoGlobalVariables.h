#pragma once
#include <variant>
#include <unordered_map>
#include <string>
#include <vector>
#include "Externals/nlohmann/json.hpp"

class Vector2;
class Vector3;
class Vector4;

namespace Kyoko {
	class GlobalVariables {
	public:
		/// <summary>
		/// インスタンスの取得
		/// </summary>
		/// <returns>インスタンス</returns>
		static GlobalVariables* GetInstance();
		/// <summary>
		/// 初期化
		/// </summary>
		void Initialize();
		/// <summary>
		/// 終了処理
		/// </summary>
		void Finalize();
		/// <summary>
		/// 更新
		/// </summary>
		void Update();
		/// <summary>
		/// チャンクの作成
		/// </summary>
		/// <param name="chunkName">チャンク名</param>
		void CreateChunk(const std::string& chunkName);
		/// <summary>
		/// グループの作成
		/// </summary>
		/// <param name="chunkName">チャンク名</param>
		/// <param name="groupName">グループ名</param>
		void CreateGroup(const std::string& chunkName, const std::string& groupName);

		/// <summary>
		/// アイテムの追加
		/// </summary>
		/// <typeparam name="T">値の型</typeparam>
		/// <param name="chunkName">チャンク名</param>
		/// <param name="groupName">グループ名</param>
		/// <param name="key">キー</param>
		/// <param name="value">値</param>
		/// <param name="tree">ツリー</param>
		template<typename T>
		void AddItem(const std::string& chunkName, const std::string& groupName, const std::string& key, const T& value, const std::vector<std::string>& tree);
		void AddItemColor(const std::string& chunkName, const std::string& groupName, const std::string& key, const Vector4& value, const std::vector<std::string>& tree);
		void AddItemCombo(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::string& type, const std::string& value, const std::vector<std::string>& tree);

		/// <summary>
		/// 要素の削除
		/// </summary>
		/// <param name="chunkName">チャンク名</param>
		/// <param name="groupName">グループ名</param>
		/// <param name="key">キー</param>
		/// <param name="tree">ツリー</param>
		void EraseItem(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree);
		void EraseItemColor(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree);
		void EraseItem(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::string& type, const std::vector<std::string>& tree);

		/// <summary>
		/// 値の取得 
		/// </summary>
		/// <param name="chunkName">チャンク名</param>
		/// <param name="groupName">グループ名</param>
		/// <param name="key">キー</param>
		/// <param name="tree">ツリー</param>
		/// <returns>値</returns>
		int32_t GetIntValue(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const;
		float GetFloatValue(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const;
		const Vector2& GetVector2Value(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const;
		const Vector3& GetVector3Value(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const;
		const Vector4& GetVector4Value(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const;
		bool GetBoolValue(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const;
		const std::string& GetStringValue(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const;
		const Vector4& GetColor(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const;
		const std::string& GetCombo(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::string& type, const std::vector<std::string>& tree) const;

		/// <summary>
		/// ImGuiを使わない値の取得
		/// </summary>
		/// <param name="key">キー</param>
		/// <returns>ImGuiを使わない値</returns>
		int32_t GetIntValueDontTouchImGui(const std::string& key) const;
		float GetFloatValueDontTouchImGui(const std::string& key) const;
		const Vector2& GetVector2ValueDontTouchImGui(const std::string& key) const;
		const Vector3& GetVector3ValueDontTouchImGui(const std::string& key) const;
		const Vector4& GetVector4ValueDontTouchImGui(const std::string& key) const;
		bool GetBoolValueDontTouchImGui(const std::string& key) const;
		const std::string& GetStringValueDontTouchImGui(const std::string& key) const;
		const Vector4& GetColorDontTouchImGui(const std::string& key) const;
		const std::string& GetComboValueDontTouchImGui(const std::string& key, const std::string& type) const;

		/// <summary>
		/// 値のセット
		/// </summary>
		/// <typeparam name="T">値の型</typeparam>
		/// <param name="chunkName">チャンク名</param>
		/// <param name="groupName">グループ名</param>
		/// <param name="key">キー</param>
		/// <param name="value">値</param>
		/// <param name="tree">ツリー</param>
		template<typename T>
		void SetVariable(const std::string& chunkName, const std::string& groupName, const std::string& key, const T& value, const std::vector<std::string>& tree);
		void SetColor(const std::string& chunkName, const std::string& groupName, const std::string& key, const Vector4& value, const std::vector<std::string>& tree);
		void SetCombo(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::string& type, const std::string& value, const std::vector<std::string>& tree);

		/// <summary>
		/// 値のセットと保存
		/// </summary>
		/// <typeparam name="T">値の型</typeparam>
		/// <param name="chunkName">チャンク名</param>
		/// <param name="groupName">グループ名</param>
		/// <param name="key">キー</param>
		/// <param name="value">値</param>
		/// <param name="tree">ツリー</param>
		template<typename T>
		void SaveAndSetVariable(const std::string& chunkName, const std::string& groupName, const std::string& key, const T& value, const std::vector<std::string>& tree);
		/// <summary>
		/// ImGuiを使わないアイテムの追加
		/// </summary>
		/// <typeparam name="T">値の型</typeparam>
		/// <param name="key">キー</param>
		/// <param name="value">値</param>
		template<typename T>
		void AddItemDontTouchImGui(const std::string& key, const T& value);
		void AddColorDontTouchImGui(const std::string& key, const Vector4& value);
		void AddComboDontTouchImGui(const std::string& key, const std::string& type, const std::string& value);

		/// <summary>
		/// ImGuiを使わない値のセットと保存
		/// </summary>
		/// <typeparam name="T">値の型</typeparam>
		/// <param name="key">キー</param>
		/// <param name="value">値</param>
		template<typename T>
		void SaveAndSetVariableDontTouchImGui(const std::string& key, const T& value);
		void SaveAndSetColorDontTouchImGui(const std::string& key, const Vector4& value);
		void SaveAndSetComboDontTouchImGui(const std::string& key, const std::string& type, const std::string& value);

		/// <summary>
		/// ツリーが開いているかの取得
		/// </summary>
		/// <param name="chunkName">チャンク名</param>
		/// <param name="groupName">グループ名</param>
		/// <param name="tree">ツリー</param>
		/// <returns>ツリーが開いているか</returns>
		bool IsTreeOpen(const std::string& chunkName, const std::string& groupName, const std::vector<std::string>& tree);
		/// <summary>
		/// ファイルの保存
		/// </summary>
		/// <param name="chunkName">チャンク名</param>
		/// <param name="groupName">グループ名</param>
		/// <param name="isFin">終了処理か</param>
		void SaveFile(const std::string& chunkName, const std::string& groupName, bool isFin = false);
		/// <summary>
		/// 全てのデータの読み込み
		/// </summary>
		void LoadFiles();
		/// <summary>
		/// ファイルの読み込み
		/// </summary>
		/// <param name="chunkName">チャンク名</param>
		/// <param name="groupName">グループ名</param>
		void LoadFile(const std::string& chunkName, const std::string& groupName);
		/// <summary>
		/// コンボ名の追加
		/// </summary>
		/// <param name="key">キー</param>
		/// <param name="comboName">コンボ名</param>
		void AddComboName(const std::string& key, const std::string& comboName);
		/// <summary>
		/// コンボ名のマップの取得
		/// </summary>
		/// <returns>コンボ名のマップ</returns>
		const std::unordered_map<std::string, std::vector<std::string>>* GetComboNameMap() const;

		/// <summary>
		/// コンボの呼び出し
		/// </summary>
		/// <param name="key">キー</param>
		/// <param name="type">タイプ</param>
		/// <param name="ptr">ポインタ</param>
		void DrawImGuiCombo(const std::string& key, const std::string& type, std::string* ptr);

		/// <summary>
		/// 何かがセーブされたか
		/// </summary>
		/// <returns>セーブされたか</returns>
		bool IsSomethingSave() const;

	private:
		GlobalVariables() = default;
		~GlobalVariables() = default;
		GlobalVariables(const GlobalVariables& obj) = delete;
		GlobalVariables& operator=(const GlobalVariables& obj) = delete;

		/// <summary>
		/// アイテム
		/// </summary>
		using Item = std::variant<int32_t, float, Vector2, Vector3, bool, std::string, Vector4>;
		/// <summary>
		/// グループ
		/// </summary>
		using Group = std::unordered_map<std::string, Item>;
		/// <summary>
		/// グループのポインタ版
		/// </summary>
		using GroupPtr = std::unordered_map<std::string, Item*>;
		/// <summary>
		/// チャンク
		/// </summary>
		using Chunk = std::unordered_map<std::string, Group>;
		/// <summary>
		/// 特定のワードの後ろを取得
		/// </summary>
		/// <param name="itemName">全体のワード</param>
		/// <param name="findName">探すワード</param>
		/// <returns>特定のワードの後ろ</returns>
		std::string GetAfterName(const std::string& itemName, const std::string& findName);
		/// <summary>
		/// 値の取得
		/// </summary>
		/// <typeparam name="T">値の型</typeparam>
		/// <param name="chunkName">チャンク名</param>
		/// <param name="groupName">グループ名</param>
		/// <param name="key">キー</param>
		/// <param name="tree">ツリー</param>
		/// <returns>値</returns>
		template<typename T>
		const T& GetValue(const std::string& chunkName, const std::string& groupName, const std::string& key, const std::vector<std::string>& tree) const;
		/// <summary>
		/// ImGuiを使わない値の取得
		/// </summary>
		/// <typeparam name="T">値の型</typeparam>
		/// <param name="key">キー</param>
		/// <returns>ImGuiを使わない値</returns>
		template<typename T>
		const T& GetValueDontTouchImGui(const std::string& key) const;
		/// <summary>
		/// 値のセット
		/// </summary>
		/// <typeparam name="T">値の型</typeparam>
		/// <param name="chunkName">チャンク名</param>
		/// <param name="groupName">グループ名</param>
		/// <param name="key">キー</param>
		/// <param name="value">値</param>
		/// <param name="tree">ツリー</param>
		/// <param name="isAddItem">アイテムを追加するか</param>
		template<typename T>
		void SetValue(const std::string& chunkName, const std::string& groupName, const std::string& key, const T& value, const std::vector<std::string>& tree, bool isAddItem = true);
		/// <summary>
		/// コンボ名のセット
		/// </summary>
		/// <param name="key">キー</param>
		/// <param name="comboName">コンボ名</param>
		void SetComboName(const std::string& key, const std::string& comboName);
		/// <summary>
		/// アイテムからrootに変換
		/// </summary>
		/// <param name="root">root</param>
		/// <param name="item">アイテム</param>
		/// <param name="key">キー</param>
		/// <param name="treeNames">ツリー</param>
		/// <param name="level">レベル</param>
		void ItemToRoot(nlohmann::json& root, Item& item, const std::string& key, const std::vector<std::string>& treeNames, uint32_t level = 0);
		/// <summary>
		/// ツリーの名前の作成
		/// </summary>
		/// <param name="key">キー</param>
		/// <param name="treeNames">ツリー</param>
		/// <param name="level">レベル</param>
		void MakeTreeNames(std::string& key, std::vector<std::string>& treeNames, uint32_t level = 0);
		/// <summary>
		/// rootから値をセット
		/// </summary>
		/// <param name="chunkName">チャンク名</param>
		/// <param name="groupName">グループ名</param>
		/// <param name="itGroup">グループ</param>
		/// <param name="treeNames">ツリー</param>
		/// <param name="level">レベル</param>
		void RootToSetValue(const std::string& chunkName, const std::string& groupName, nlohmann::json::iterator& itGroup, const std::vector<std::string>& treeNames, uint32_t level = 0);
#ifdef _DEBUG
		/// <summary>
		/// ツリーマップの作成
		/// </summary>
		/// <param name="chunkName">チャンク名</param>
		/// <param name="groupName">グループ名</param>
		/// <param name="treeMap">ツリーマップ</param>
		/// <param name="item">アイテム</param>
		/// <param name="itemName">アイテム名</param>
		/// <param name="treeNames">ツリー</param>
		/// <param name="level">レベル</param>
		void MakeTreeMap(const std::string& chunkName, const std::string& groupName,
			std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, std::unordered_map<std::string, GroupPtr>>>>>>& treeMap,
			Item& item, const std::string& itemName, std::vector<std::string>& treeNames, uint32_t level = 0);
		/// <summary>
		/// ImGuiのツリー作成
		/// </summary>
		/// <typeparam name="T">値の型</typeparam>
		/// <param name="tree">ツリー</param>
		/// <param name="chunkName">チャンク名</param>
		/// <param name="groupName">グループ名</param>
		/// <param name="treeName">ツリー</param>
		/// <param name="level">レベル</param>
		template <typename T>
		void DrawTreeImGui(T& tree, const std::string& chunkName, const std::string& groupName, const std::string& treeName, uint32_t level = 1);
		/// <summary>
		/// ImGuiの描画
		/// </summary>
		/// <param name="itemName">アイテム名</param>
		/// <param name="item">アイテム</param>
		/// <param name="debugName">名前</param>
		void PreparationImGui(const std::string& itemName, Item& item, const std::string& debugName);
#endif // _DEBUG

	private:

		std::unordered_map<std::string, Chunk> datas_; // データ
		uint32_t kMaxTreeNum_; // ツリーの最大数
		const std::string kDirectoryPath = "Resources/GlobalVariables/"; // パス
		std::vector<std::string> kTreeName_; // ツリーの名前

		const std::string kZZESC = "zzESC"; // 終了したときの状態を残す時の名前
		const std::string kDontTouchPlayData = "aaDontTouchPlayData"; // ImGuiを使わないプレイヤーデータ
		const std::string kDontTouch = "DontTouch";  // ImGuiを使わないデータ
		const std::string kColorName = "COLOR"; // 色
		const std::string kGlobalCombo = "GlobalCombo"; // グローバルコンボ
		const std::string kComboName = "COMBO"; // コンボ
		const std::string kComboTypeName = "COMTYPE"; // コンボのタイプ
		std::vector<std::string> kUnderBar; // _の配列

#ifdef _DEBUG
		bool isDraw_; // 全体を描画するか
		std::unordered_map<std::string, bool> isDrawTitle_; // ImGuiを表示させるか
		std::unordered_map<std::string, Chunk> isTreeOpen_; // ツリーが開いているか
		char filterName[128] = ""; // コンボの検索用
		std::unordered_map<std::string, Item> tempData_; // 遅延データ
#endif // _DEBUG

		bool isSomethingSave_; // 何かがセーブされたか
		std::unordered_map<std::string, std::vector<std::string>> comboNames_; // コンボの名前
	};

}
