#pragma once
#include "GlobalVariables/GlobalVariableUser.h"

/// <summary>
/// コンボ名の読み込み保存用クラス
/// </summary>
class GlobalNames 
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="chunk">チャンク名</param>
	/// <param name="group">グループ名</param>
	GlobalNames(const std::string& chunk, const std::string& group);
	/// <summary>
	/// コンボ名の追加
	/// </summary>
	/// <param name="no">id</param>
	/// <param name="type">タイプ</param>
	/// <param name="name">名前</param>
	void AddComboName(int32_t no, const std::string& type, const std::string& name = "デフォルト");
	/// <summary>
	/// プログラムで記述するコンボ名の追加
	/// </summary>
	/// <param name="no">id</param>
	/// <param name="type">タイプ</param>
	/// <param name="name">名前</param>
	void AddSystemComboName(int32_t no, const std::string& type, const std::string& name);
	/// <summary>
	/// コンボ名データのロード
	/// </summary>
	/// <param name="chunk">チャンク名</param>
	/// <param name="group">グループ名</param>
	void LoadNames(const std::string& chunk, const std::string& group);
	/// <summary>
	/// コンボの配列を取得
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <returns>コンボの配列</returns>
	const std::vector<std::string>& GetNames(const std::string& type);

private:
	/// <summary>
	/// コンボ名データのロード
	/// </summary>
	/// <param name="chunk">チャンク名</param>
	/// <param name="group">グループ名</param>
	/// <param name="isSystem">プログラムで記述したタイプか</param>
	void LoadName(const std::string& chunk, const std::string& group, bool isSystem);

	std::unique_ptr<GlobalVariableUser> global_; // グローバルクラス
	std::unique_ptr<GlobalVariableUser> sglobal_; // グローバルクラス
	std::map<std::string, std::vector<std::string>> names_; // コンボ名
};
