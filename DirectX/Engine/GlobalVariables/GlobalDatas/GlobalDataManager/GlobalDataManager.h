#pragma once
#include "GlobalVariables/GlobalVariableData.h"
#include "GlobalVariables/GlobalDatas/GlobalNames/GlobalNames.h"
#include "GlobalVariables/GlobalDatas/BaseGlobalData/BaseGlobalData.h"

/// <summary>
/// kyokoデータのマネージャー
/// </summary>
class GlobalDataManager
{
public:
	/// <summary>
	/// エディターでパターンを増やしたいもの
	/// </summary>
	enum class ComboTypeNames {
		kStagePattern, // ステージのパターン
		kBlockPattern, // ブロックの配置パターン
		kComboTypeNamesEnd, // 末尾
	};

	/// <summary>
	/// 事前にパターンを増やしたいもの（ブロックのタイプとか）
	/// </summary>
	enum class SystemComboTypeNames {
		kBlockType, // ブロックのタイプ
		kStampType, // スタンプの面タイプ
		kSystemComboTypeNamesEnd, // 末尾
	};

	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static GlobalDataManager* GetInstance();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// データの取得
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <param name="name">名前</param>
	/// <returns>データ</returns>
	const std::map<int32_t, GlobalVariableData::Item>& GetData(ComboTypeNames type, const std::string& name);

	/// <summary>
	/// GlobalVariableDataの取得
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <param name="name">名前</param>
	/// <returns>GlobalVariableData</returns>
	const GlobalVariableData& GetGlobalData(ComboTypeNames type, const std::string& name);

	/// <summary>
	/// デバッグ中か
	/// </summary>
	/// <returns>デバッグ中か</returns>
	bool IsDebug() const;

private:
	GlobalDataManager() = default;
	~GlobalDataManager() = default;
	GlobalDataManager(const GlobalDataManager& obj) = delete;
	GlobalDataManager& operator=(const GlobalDataManager& obj) = delete;

	/// <summary>
	/// タイプの追加
	/// </summary>
	void AddTypes();
	/// <summary>
	/// データの生成
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <returns>データ</returns>
	BaseGlobalData* CreateData(const std::string& type);

	/// <summary>
	/// エディターで増やしたいタイプの追加
	/// </summary>
	/// <param name="id">id</param>
	/// <param name="type">タイプ</param>
	void AddType(ComboTypeNames id, const std::string& type);
	/// <summary>
	/// 事前に追加するタイプの追加
	/// </summary>
	/// <param name="id">id</param>
	/// <param name="type">タイプ</param>
	/// <param name="name">名前</param>
	void AddSystemType(SystemComboTypeNames id, const std::string& type, const std::string& name);

	/// <summary>
	/// セーブ
	/// </summary>
	/// <param name="data">保存したいデータ</param>
	/// <param name="typeName">タイプ</param>
	/// <param name="name">名前</param>
	void Save(const std::unique_ptr<BaseGlobalData>& data, const std::string& typeName, const std::string& name);
	/// <summary>
	/// データのセット
	/// </summary>
	/// <param name="data">セットされるデータ</param>
	/// <param name="typeName">タイプ</param>
	/// <param name="name">名前</param>
	void SetData(std::unique_ptr<BaseGlobalData>& data, const std::string& typeName, const std::string& name);

	const std::string kChunkName = "ComboName"; // チャンク名
	const std::string kPatternName = "Pattern"; // パターン名
	const std::string kDefault = "デフォルト"; // デフォルト名

	std::map<int32_t, std::string> typeNames_; // idとタイプ
	std::map<std::string, ComboTypeNames> nameTypes_; // 名前とタイプ
	std::unique_ptr<BaseGlobalData> getterData_; // ゲッター用データ
	std::pair<ComboTypeNames, std::string> getterType_; // ゲッターのタイプ

#ifdef _DEBUG
	/// <summary>
	/// エディター用データ
	/// </summary>
	struct EditorData
	{
		std::unique_ptr<BaseGlobalData> data; // データ
		char inputName[128] = ""; // 名前の入力用
		char filterName[128] = ""; // 検索用の名前
		std::string currentName; // 現在の名前
		bool isNewMake = true; // 新規作成か
	};
	std::vector<std::unique_ptr<EditorData>> editorData_; // エディターデータ
#endif // _DEBUG

	std::unique_ptr<GlobalNames> names_; // コンボ名保存用
	bool isDebug_; // デバッグ中か
};
