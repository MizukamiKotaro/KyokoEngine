#pragma once
#include "GameElement/ComboData/BaseComboData/BaseComboData.h"
class Camera;
class InstancingModelManager;
class InstancingGroupData;

/// <summary>
/// コンボデータオブジェクトの基盤
/// </summary>
class BaseComboDataObject : public BaseComboData
{
public:
	/// <summary>
	/// 共通部分の初期化
	/// </summary>
	static void StaticInitialize();
	/// <summary>
	/// デストラクタ
	/// </summary>
	virtual ~BaseComboDataObject() = default;
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
	virtual void SetTime(float time);
	/// <summary>
	/// 描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	virtual void Draw(const Camera& camera);
	/// <summary>
	/// ライトの描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	virtual void DrawLight(const Camera& camera);
	/// <summary>
	/// アウトラインをつけたいものの描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	virtual void DrawOutline(const Camera& camera);
	/// <summary>
	/// ブルームをかけたいものの描画
	/// </summary>
	/// <param name="camera">カメラ</param>
	virtual void DrawBloom(const Camera& camera);

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
	void SetGlobalVariable() override = 0;
	/// <summary>
	/// グローバル変数の適用
	/// </summary>
	void ApplyGlobalVariable() override = 0;

	static InstancingModelManager* instancingManager_; // インスタンシングマネージャー
	const InstancingGroupData* instancingData_; // インスタンシングデータ
};