#pragma once
#include "ComboNameConfig.h"
#include "KyokoGlobalVariables.h"

/// <summary>
/// コンボの名前を管理するクラス
/// </summary>
class GlobalVariableComboNames {
public:
	/// <summary>
	/// インスタンスの取得
	/// </summary>
	/// <returns>インスタンス</returns>
	static GlobalVariableComboNames* GetInstance();
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// コンボの名前の追加
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <param name="comboName">コンボの名前</param>
	void AddComboName(ComboNameType type, const std::string& comboName);
	/// <summary>
	/// 名前の取得
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <returns>名前</returns>
	std::pair<std::string, std::string> GetName(ComboNameType type);

	/// <summary>
	/// コンボタイプの追加
	/// </summary>
	/// <param name="typeName">タイプ名</param>
	void AddComboType(const std::string& typeName);

	/// <summary>
	/// コンボの名前の追加
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <param name="comboName">コンボの名前</param>
	void AddComboName(int32_t type, const std::string& comboName);
	void AddComboName(const std::string& type, const std::string& comboName);
	/// <summary>
	/// 名前の取得
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <returns>名前</returns>
	std::pair<std::string, std::string> GetName(int32_t type);
	/// <summary>
	/// 名前の取得
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <returns>名前</returns>
	std::pair<std::string, std::string> GetSystemName(int32_t type);

	/// <summary>
	/// 事前に追加するコンボタイプ
	/// </summary>
	/// <param name="typeName"></param>
	void AddSystemComboType(const std::string& typeName);

	/// <summary>
	/// コンボの名前の追加
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <param name="comboName">コンボの名前</param>
	void AddSystemComboName(int32_t type, const std::string& comboName);
	void AddSystemComboName(const std::string& type, const std::string& comboName);

private:
	GlobalVariableComboNames() = default;
	~GlobalVariableComboNames() = default;
	GlobalVariableComboNames(const GlobalVariableComboNames& obj) = delete;
	GlobalVariableComboNames& operator=(const GlobalVariableComboNames& obj) = delete;

private:
	Kyoko::GlobalVariables* global_; // グローバル変数を管理するクラス
	const std::unordered_map<std::string, std::vector<std::string>>* comboNameMap_; // コンボの名前のマップ
	std::unordered_map<ComboNameType, std::string> names_; // 名前のマップ
	std::vector<std::string> dnames_; // 動的なコンボの追加
	std::vector<std::string> snames_; // 明示的なコンボの追加
};
