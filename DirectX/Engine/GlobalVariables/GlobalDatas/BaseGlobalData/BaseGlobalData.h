#pragma once
#include "GlobalVariables/GlobalVariableData.h"

/// <summary>
/// Kyokoデータの基底クラス
/// </summary>
class BaseGlobalData
{
public:
	virtual ~BaseGlobalData() = default;
	/// <summary>
	/// データの作成(設定)
	/// </summary>
	/// <param name="chunk">チャンク名</param>
	/// <param name="group">グループ名</param>
	/// <param name="name">名前</param>
	virtual void CreateData(const std::string& chunk, const std::string& group, const std::string& name) = 0;
	/// <summary>
	/// 更新
	/// </summary>
	virtual void Update();

	/// <summary>
	/// ImGuiの描画
	/// </summary>
	/// <param name="treeName">ツリー名</param>
	/// <param name="isSave">値を更新するか</param>
	void DrawImGui(const std::string& treeName, bool isSave = true);
	/// <summary>
	/// データのセーブ
	/// </summary>
	void Save();
	/// <summary>
	/// データのセット
	/// </summary>
	/// <param name="items">データ</param>
	void SetData(const std::map<int32_t, GlobalVariableData::Item>& items);
	/// <summary>
	/// データの取得
	/// </summary>
	/// <returns>データ</returns>
	const std::map<int32_t, GlobalVariableData::Item>& GetData() const;

	/// <summary>
	/// GlobalVariableDataの取得
	/// </summary>
	/// <returns>GlobalVariableData</returns>
	const GlobalVariableData& GetGlobalData() const;

	/// <summary>
	/// データのセット
	/// </summary>
	/// <param name="data">データ</param>
	void SetData(const GlobalVariableData& data);

protected:
	std::unique_ptr<GlobalVariableData> datas_; // データ
};
