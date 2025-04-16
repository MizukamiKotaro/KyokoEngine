#pragma once
#include "Editor/BaseEditor/BaseEditor.h"

/// <summary>
/// ステージエディター
/// </summary>
class ComboDataEditor : public BaseEditor
{
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
	ComboDataEditor(const std::string& chunkName, const std::string& groupName, const std::string& tree1 = "_", const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_");

	/// <summary>
	/// グループ名のリセット
	/// </summary>
	/// <param name="groupName">グループ名</param>
	void ResetGroupName(const std::string& groupName);
};