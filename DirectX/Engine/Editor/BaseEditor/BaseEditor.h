#pragma once
#include "GlobalVariables/GlobalVariableUser.h"
#include <memory>
/// <summary>
/// エディターの基盤
/// </summary>
class BaseEditor {
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseEditor() = default;
	/// <summary>
	/// コンボの追加
	/// </summary>
	/// <param name="type">タイプ</param>
	/// <param name="comboName">名前</param>
	virtual void AddComboName(ComboNameType type, const std::string& comboName);

	/// <summary>
	/// アイテムの追加
	/// </summary>
	/// <param name="key">キー</param>
	/// <param name="value">値</param>
	/// <param name="tree2">ツリーの名前2</param>
	/// <param name="tree3">ツリーの名前3</param>
	/// <param name="tree4">ツリーの名前4</param>
	/// <param name="tree5">ツリーの名前5</param>
	/// <param name="tree6">ツリーの名前6</param>
	virtual void AddItem(const std::string& key, int32_t value, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	virtual void AddItem(const std::string& key, float value, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	virtual void AddItem(const std::string& key, const Vector2& value, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	virtual void AddItem(const std::string& key, const Vector3& value, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	virtual void AddItem(const std::string& key, const Vector4& value, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	virtual void AddItem(const std::string& key, bool value, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	virtual void AddItem(const std::string& key, const std::string& value, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");

	virtual void AddItemColor(const std::string& key, const Vector4& value, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	virtual void AddItemCombo(const std::string& key, ComboNameType type, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	virtual void AddItemCombo(const std::string& key, const std::string& type, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");

	/// <summary>
	/// 値の取得
	/// </summary>
	/// <param name="key">キー</param>
	/// <param name="tree2">ツリーの名前2</param>
	/// <param name="tree3">ツリーの名前3</param>
	/// <param name="tree4">ツリーの名前4</param>
	/// <param name="tree5">ツリーの名前5</param>
	/// <param name="tree6">ツリーの名前6</param>
	/// <returns>値</returns>
	virtual int32_t GetIntValue(const std::string& key, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	virtual float GetFloatValue(const std::string& key, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	virtual const Vector2& GetVector2Value(const std::string& key, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	virtual const Vector3& GetVector3Value(const std::string& key, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	virtual const Vector4& GetVector4Value(const std::string& key, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	virtual bool GetBoolValue(const std::string& key, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	virtual const std::string& GetStringValue(const std::string& key, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;

	virtual const Vector4& GetColor(const std::string& key, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	virtual const std::string& GetCombo(const std::string& key, ComboNameType type, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;
	virtual const std::string& GetCombo(const std::string& key, const std::string& type, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_") const;

	/// <summary>
	/// 値のセット
	/// </summary>
	/// <param name="key">キー</param>
	/// <param name="tree2">ツリーの名前2</param>
	/// <param name="tree3">ツリーの名前3</param>
	/// <param name="tree4">ツリーの名前4</param>
	/// <param name="tree5">ツリーの名前5</param>
	/// <param name="tree6">ツリーの名前6</param>
	virtual void SetVariable(const std::string& key, int32_t value, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	virtual void SetVariable(const std::string& key, float value, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	virtual void SetVariable(const std::string& key, const Vector2& value, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	virtual void SetVariable(const std::string& key, const Vector3& value, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	virtual void SetVariable(const std::string& key, const Vector4& value, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	virtual void SetVariable(const std::string& key, bool value, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	virtual void SetVariable(const std::string& key, const std::string& value, const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");

	/// <summary>
	/// ツリーが開いているかの取得
	/// </summary>
	/// <param name="tree2">ツリーの名前2</param>
	/// <param name="tree3">ツリーの名前3</param>
	/// <param name="tree4">ツリーの名前4</param>
	/// <param name="tree5">ツリーの名前5</param>
	/// <param name="tree6">ツリーの名前6</param>
	/// <returnsツリーが開いているか></returns>
	virtual bool IsTreeOpen(const std::string& tree2 = "_", const std::string& tree3 = "_", const std::string& tree4 = "_", const std::string& tree5 = "_", const std::string& tree6 = "_");
	/// <summary>
	/// ツリーが開いているかの取得
	/// </summary>
	/// <param name="treeNo">いくつ目のツリーか</param>
	/// <returns>ツリーが開いているか</returns>
	virtual bool IsTreeOpen(int treeNo);
protected:
	std::unique_ptr<GlobalVariableUser> global_; // グローバル変数を使用しやすくするクラス
};