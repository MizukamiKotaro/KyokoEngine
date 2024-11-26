#pragma once
#include <map>
#include <string>
#include <vector>
#include "ComboNameConfig.h"

class GlobalVariables;

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

private:
	GlobalVariableComboNames() = default;
	~GlobalVariableComboNames() = default;
	GlobalVariableComboNames(const GlobalVariableComboNames& obj) = delete;
	GlobalVariableComboNames& operator=(const GlobalVariableComboNames& obj) = delete;

private:
	GlobalVariables* global_; // グローバル変数を管理するクラス
	const std::map<std::string, std::vector<std::string>>* comboNameMap_; // コンボの名前のマップ
	std::map<ComboNameType, std::string> names_; // 名前のマップ
};
