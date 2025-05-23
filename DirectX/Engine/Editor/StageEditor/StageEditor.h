#pragma once
#include "Editor/BaseEditor/BaseEditor.h"

/// <summary>
/// ステージエディター
/// </summary>
class StageEditor : public BaseEditor
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="tree1">ツリーの名前1</param>
	/// <param name="tree2">ツリーの名前2</param>
	/// <param name="tree3">ツリーの名前3</param>
	/// <param name="tree4">ツリーの名前4</param>
	/// <param name="tree5">ツリーの名前5</param>
	StageEditor(const std::string& tree1, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_");
	/// <summary>
	/// コンストラクタ、ツリーなし
	/// </summary>
	StageEditor();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// ステージが変更したかの取得
	/// </summary>
	/// <returns>ステージが変更したか</returns>
	bool IsChangedStage();

private:
	int32_t preStageNo_; // 以前のステージ
};