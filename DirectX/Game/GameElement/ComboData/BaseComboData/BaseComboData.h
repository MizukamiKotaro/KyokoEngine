#pragma once
#include "Editor/ComboDataEditor/ComboDataEditor.h"

/// <summary>
/// コンボデータの基盤
/// </summary>
class BaseComboData
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseComboData() = default;

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="deltaTime">デルタタイム</param>
	virtual void Update(float deltaTime = 0) = 0;
	
protected:
	/// <summary>
	/// ステージエディターの設定
	/// </summary>
	/// <param name="mainName">メインの名前</param>
	/// <param name="name">名前</param>
	void CreateComboDataEditor(const std::string& mainName, const std::string& name);
	/// <summary>
	/// グローバル変数の更新
	/// </summary>
	void UpdateGlobalVariable();
	/// <summary>
	/// グローバル変数の設定
	/// </summary>
	virtual void SetGlobalVariable() = 0;
	/// <summary>
	/// グローバル変数の適用
	/// </summary>
	virtual void ApplyGlobalVariable() = 0;

	std::unique_ptr<ComboDataEditor> comboEditor_; // コンボエディター
};