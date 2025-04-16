#pragma once
#include "GameElement/ComboData/BaseComboDataObject/BaseComboDataObject.h"
#include <list>

class Camera;
class InstancingModelManager;
class InstancingGroupData;

/// <summary>
/// コンボデータオブジェクトの基盤
/// </summary>
class ComboDataObjectList : public BaseComboDataObject
{
public:
	/// <summary>
	/// デストラクタ
	/// </summary>
	~ComboDataObjectList() = default;
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize() override;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="deltaTime">デルタタイム</param>
	void Update(float deltaTime = 0) override;
	/// <summary>
	/// タイムのセット
	/// </summary>
	/// <param name="time">タイム</param>
	void SetTime(float time) override;
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void Draw(const Camera& camera) override;
	/// <summary>
	/// ライトの描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void DrawLight(const Camera& camera) override;
	/// <summary>
	/// アウトラインをつけたいものの描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void DrawOutline(const Camera& camera) override;
	/// <summary>
	/// ブルームをかけたいものの描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	void DrawBloom(const Camera& camera) override;

protected:
	/// <summary>
	/// 個別でのコンボエディターの設定
	/// </summary>
	/// <param name="mainName">メインの名前</param>
	/// <param name="name">名前</param>
	/// <param name="treeName">ツリー名</param>
	/// <param name="no">ナンバー</param>
	/// <param name="isMany">沢山配置するか</param>
	void CreateComboEditor(const std::string& mainName, const std::string& name, const std::string& treeName, uint32_t no);
	/// <summary>
	/// グローバル変数の設定
	/// </summary>
	void SetGlobalVariable() override;
	/// <summary>
	/// グローバル変数の適用
	/// </summary>
	void ApplyGlobalVariable() override;

	std::list<std::unique_ptr<BaseComboDataObject>> comboDataObjectList_;
};